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

#ifndef YALMP_MONITOR_CORE_INTERNALS_GLOBAL_H
#define YALMP_MONITOR_CORE_INTERNALS_GLOBAL_H

#pragma once

#include <QtCore/qglobal.h>

#if defined(YALMP_MONITOR_CORE_LIBRARY)
#  define YALMP_MONITOR_CORE_EXPORT Q_DECL_EXPORT
#else
#  define YALMP_MONITOR_CORE_EXPORT Q_DECL_IMPORT
#endif

#endif // YALMP_MONITOR_CORE_INTERNALS_GLOBAL_H
