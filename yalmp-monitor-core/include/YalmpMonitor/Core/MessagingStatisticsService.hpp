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

#ifndef YALMP_MONITOR_CORE_MESSAGING_STATISTICS_SERVICE_HPP
#define YALMP_MONITOR_CORE_MESSAGING_STATISTICS_SERVICE_HPP

#pragma once

#include "YalmpMonitor/Core/Internals/Global.h"

#include <QObject>
#include <QThread>

namespace YalmpMonitor::Core::Internals
{
  class MessagingStatisticsWorker;
}

namespace YalmpMonitor::Core
{
  using YalmpMonitor::Core::Internals::MessagingStatisticsWorker;

  class MessagingService;

  class YALMP_MONITOR_CORE_EXPORT MessagingStatisticsService final : public QObject
  {
    Q_OBJECT

  public:
    explicit MessagingStatisticsService(const MessagingService& messagingService, QObject* parent = nullptr);
    ~MessagingStatisticsService();
  signals:
    void packetsPerSecondUpdated(quint64 packetsPerSecond);
    void bytesPerSecondUpdated(quint64 bytesPerSecond);
    void rejectedPacketsUpdated(quint64 rejectedPackets);

  private:
    QThread*                   mWorkerThread;
    MessagingStatisticsWorker* mMessagingStatisticsWorker;
  };
}

#endif // YALMP_MONITOR_CORE_MESSAGING_STATISTICS_SERVICE_HPP
