////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                    //
// YALMP Monitor <https://github.com/pabloelices/yalmp-monitor>                                                       //
// Copyright (C) 2020  Pablo Daniel Gómez Elices                                                                      //
//                                                                                                                    //
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public  //
// License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any     //
// later version.                                                                                                     //
//                                                                                                                    //
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied //
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more      //
// details.                                                                                                           //
//                                                                                                                    //
// You should have received a copy of the GNU General Public License along with this program.  If not, see            //
// <http://www.gnu.org/licenses/>.                                                                                    //
//                                                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "YalmpMonitor/Core/Internals/YalmpPacketParser.hpp"

#include "YalmpMonitor/Core/Internals/YalmpChecksum.hpp"

#include "YalmpMonitor/Core/YalmpPacket.hpp"

namespace YalmpMonitor::Core::Internals
{
  static const quint8 MAX_PAYLOAD_SIZE {255};

  YalmpPacketParser::YalmpPacketParser(QObject* parent)
    : QObject {parent}
    , mState {State::AWAITING_START_FLAG}
    , mReceivedStartFlag {0x00}
    , mReceivedMessageId {0x00}
    , mReceivedPayloadLength {0x00}
    , mReceivedPayload {QByteArray {}}
    , mReceivedChecksum {0x00}
  {
    mReceivedPayload.reserve(MAX_PAYLOAD_SIZE);
  }

  void YalmpPacketParser::parse(const QByteArray& bytes)
  {
    for (int i = 0; i < bytes.length(); i++)
    {
      const quint8 byte = static_cast<quint8>(bytes.at(i));

      switch (mState)
      {
        case State::AWAITING_START_FLAG:

          if (byte == 0x4E)
          {
            mReceivedStartFlag = byte;

            mState = State::AWAITING_MESSAGE_ID;

            mReceivedPayload.clear();
          }

          break;

        case State::AWAITING_MESSAGE_ID:

          mReceivedMessageId = byte;

          mState = State::AWAITING_PAYLOAD_LENGTH;

          break;

        case State::AWAITING_PAYLOAD_LENGTH:

          mReceivedPayloadLength = byte;

          if (mReceivedPayloadLength == 0x00)
          {
            mState = State::AWAITING_CHECKSUM;
          }
          else
          {
            mState = State::AWAITING_PAYLOAD;
          }

          break;

        case State::AWAITING_PAYLOAD:

          mReceivedPayload.append(byte);

          if (static_cast<quint8>(mReceivedPayload.size()) == mReceivedPayloadLength)
          {
            mState = State::AWAITING_CHECKSUM;
          }

          break;

        case State::AWAITING_CHECKSUM:

          mReceivedChecksum = byte;

          YalmpPacket parsedPacket {mReceivedStartFlag, mReceivedMessageId, mReceivedPayload, mReceivedChecksum};

          quint8 computedChecksum {YalmpChecksum::computeChecksum(mReceivedMessageId, mReceivedPayload)};

          if (mReceivedChecksum == computedChecksum)
          {
            emit packetAccepted(parsedPacket);
          }
          else
          {
            emit packetRejected(parsedPacket, computedChecksum);
          }

          mState = State::AWAITING_START_FLAG;

          break;
      }
    }
  }

  void YalmpPacketParser::reset()
  {
    mState = State::AWAITING_START_FLAG;
  }
}
