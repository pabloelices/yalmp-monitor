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

#ifndef YALMP_MONITOR_CORE_VERSION_HPP
#define YALMP_MONITOR_CORE_VERSION_HPP

#pragma once

#include "YalmpMonitor/Core/Internals/Global.h"

#include <QString>

#define YALMP_MONITOR_CORE_VERSION_MAJOR 0U
#define YALMP_MONITOR_CORE_VERSION_MINOR 1U
#define YALMP_MONITOR_CORE_VERSION_PATCH 1U

namespace YalmpMonitor::Core
{
  class YALMP_MONITOR_CORE_EXPORT Version final
  {
  public:
    static quint8  Major();
    static quint8  Minor();
    static quint8  Patch();
    static QString Tag();
    static bool    IsExactly(quint8 major, quint8 minor, quint8 patch);
    static bool    IsAtLeast(quint8 major, quint8 minor, quint8 patch);

  private:
    Version();
  };
}

#endif // YALMP_MONITOR_CORE_VERSION_HPP
