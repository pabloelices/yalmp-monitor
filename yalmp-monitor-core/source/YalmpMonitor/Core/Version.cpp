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

#include "YalmpMonitor/Core/Version.hpp"

namespace YalmpMonitor::Core
{
  quint8 Version::Major()
  {
    return YALMP_MONITOR_CORE_VERSION_MAJOR;
  }

  quint8 Version::Minor()
  {
    return YALMP_MONITOR_CORE_VERSION_MINOR;
  }

  quint8 Version::Patch()
  {
    return YALMP_MONITOR_CORE_VERSION_PATCH;
  }

  QString Version::Tag()
  {
    static const QString major {QString::number(Major())};
    static const QString minor {QString::number(Minor())};
    static const QString patch {QString::number(Patch())};

    static const QString tag {QStringLiteral("%1.%2.%3").arg(major, minor, patch)};

    return tag;
  }

  bool Version::IsExactly(quint8 major, quint8 minor, quint8 patch)
  {
    const quint8& currentMajor {Major()};
    const quint8& currentMinor {Minor()};
    const quint8& currentPatch {Patch()};

    const quint8& providedMajor {major};
    const quint8& providedMinor {minor};
    const quint8& providedPatch {patch};

    return currentMajor == providedMajor && currentMinor == providedMinor && currentPatch == providedPatch;
  }

  bool Version::IsAtLeast(quint8 major, quint8 minor, quint8 patch)
  {
    const quint8& currentMajor {Major()};
    const quint8& currentMinor {Minor()};
    const quint8& currentPatch {Patch()};

    const quint8& providedMajor {major};
    const quint8& providedMinor {minor};
    const quint8& providedPatch {patch};

    if (currentMajor > providedMajor) return true;
    if (currentMajor < providedMajor) return false;

    // Here currentMajor == providedMajor holds.

    if (currentMinor > providedMinor) return true;
    if (currentMinor < providedMinor) return false;

    // Here currentMinor == providedMinor holds.

    if (currentPatch > providedPatch) return true;
    if (currentPatch < providedPatch) return false;

    // Here currentPatch == providedPatch holds.

    return true;
  }
}
