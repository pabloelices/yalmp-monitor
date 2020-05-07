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

#include "YalmpMonitor/Core/YalmpPacket.hpp"

#include "YalmpMonitor/Core/Internals/YalmpChecksum.hpp"

using YalmpMonitor::Core::Internals::YalmpChecksum;

namespace YalmpMonitor::Core
{
  YalmpPacket::YalmpPacket(quint8 startFlag, quint8 messageId, const QByteArray& payload, quint8 checksum)
    : mStartFlag {startFlag}
    , mMessageId {messageId}
    , mPayloadLength {static_cast<quint8>(payload.count())}
    , mPayload {payload}
    , mChecksum {checksum}
  {
    Q_ASSERT(payload.count() < 256);
  }

  YalmpPacket::YalmpPacket(quint8 startFlag, quint8 messageId, const QByteArray& payload)
    : YalmpPacket(startFlag, messageId, payload, YalmpChecksum::computeChecksum(messageId, payload))
  {
  }

  YalmpPacket::YalmpPacket() : YalmpPacket(0x4E, 0x00, QByteArray {})
  {
  }

  quint8 YalmpPacket::startFlag() const
  {
    return mStartFlag;
  }

  quint8 YalmpPacket::messageId() const
  {
    return mMessageId;
  }

  quint8 YalmpPacket::payloadLength() const
  {
    return mPayloadLength;
  }

  const QByteArray& YalmpPacket::payload() const
  {
    return mPayload;
  }

  quint8 YalmpPacket::checksum() const
  {
    return mChecksum;
  }

  bool operator==(const YalmpPacket& lhs, const YalmpPacket& rhs)
  {
    return lhs.startFlag() == rhs.startFlag() && lhs.messageId() == rhs.messageId() && lhs.payload() == rhs.payload();
  }
}
