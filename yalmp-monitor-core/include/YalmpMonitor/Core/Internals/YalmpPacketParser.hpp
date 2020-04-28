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

#ifndef YALMP_MONITOR_CORE_INTERNALS_YALMP_PACKET_PARSER_HPP
#define YALMP_MONITOR_CORE_INTERNALS_YALMP_PACKET_PARSER_HPP

#pragma once

#include "YalmpMonitor/Core/Internals/Global.h"

#include <QObject>

namespace YalmpMonitor::Core
{
  class YalmpPacket;
}

namespace YalmpMonitor::Core::Internals
{
  class YALMP_MONITOR_CORE_EXPORT YalmpPacketParser final : public QObject
  {
    Q_OBJECT

  public:
    explicit YalmpPacketParser(QObject* parent = nullptr);
  public slots:
    void parse(const QByteArray& bytes);
    void reset();
  signals:
    void packetAccepted(const YalmpPacket& acceptedPacket);
    void packetRejected(const YalmpPacket& parsedPacket, quint8 computedChecksum);

  private:
    enum class State
    {
      AWAITING_START_FLAG,
      AWAITING_MESSAGE_ID,
      AWAITING_PAYLOAD_LENGTH,
      AWAITING_PAYLOAD,
      AWAITING_CHECKSUM
    };

    State      mState;
    quint8     mReceivedStartFlag;
    quint8     mReceivedMessageId;
    quint8     mReceivedPayloadLength;
    QByteArray mReceivedPayload;
    quint8     mReceivedChecksum;
  };
}

#endif // YALMP_MONITOR_CORE_INTERNALS_YALMP_PACKET_PARSER_HPP
