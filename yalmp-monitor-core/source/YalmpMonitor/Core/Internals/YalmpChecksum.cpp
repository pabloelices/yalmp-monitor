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

#include "YalmpMonitor/Core/Internals/YalmpChecksum.hpp"

namespace YalmpMonitor::Core::Internals
{
  quint8 YalmpChecksum::computeChecksum(quint8 messageId, const QByteArray& payload)
  {
    Q_ASSERT(payload.count() < 256);

    quint8 checksum {messageId};

    checksum += static_cast<quint8>(payload.count());

    for (int i = 0; i < payload.count(); i++)
    {
      checksum += static_cast<quint8>(payload.at(i));
    }

    checksum = ~checksum;

    return checksum;
  }
}
