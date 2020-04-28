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

#ifndef YALMP_MONITOR_CORE_YALMP_PACKET_HPP
#define YALMP_MONITOR_CORE_YALMP_PACKET_HPP

#pragma once

#include "YalmpMonitor/Core/Internals/Global.h"

#include <QByteArray>
#include <QMetaType>

namespace YalmpMonitor::Core
{
  class YALMP_MONITOR_CORE_EXPORT YalmpPacket final
  {
  public:
    YalmpPacket(quint8 startFlag, quint8 messageId, const QByteArray& payload, quint8 checksum);
    YalmpPacket(quint8 startFlag, quint8 messageId, const QByteArray& payload);
    YalmpPacket();

    quint8            startFlag() const;
    quint8            messageId() const;
    quint8            payloadLength() const;
    const QByteArray& payload() const;
    quint8            checksum() const;

  private:
    quint8     mStartFlag;
    quint8     mMessageId;
    quint8     mPayloadLength;
    QByteArray mPayload;
    quint8     mChecksum;
  };

  bool operator==(const YalmpPacket& lhs, const YalmpPacket& rhs);
}

Q_DECLARE_METATYPE(YalmpMonitor::Core::YalmpPacket)

#endif // YALMP_MONITOR_CORE_YALMP_PACKET_HPP
