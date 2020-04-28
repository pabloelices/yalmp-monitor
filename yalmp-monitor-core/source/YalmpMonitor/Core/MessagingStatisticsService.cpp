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

#include "YalmpMonitor/Core/MessagingStatisticsService.hpp"

#include "YalmpMonitor/Core/Internals/MessagingStatisticsWorker.hpp"

#include "YalmpMonitor/Core/MessagingService.hpp"

namespace YalmpMonitor::Core
{
  MessagingStatisticsService::MessagingStatisticsService(const MessagingService& messagingService, QObject* parent)
    : QObject {parent}
    , mWorkerThread {new QThread {this}}
    , mMessagingStatisticsWorker {new MessagingStatisticsWorker}
  {
    mMessagingStatisticsWorker->moveToThread(mWorkerThread);

    // QThread -> MessagingStatisticsWorker.

    connect(mWorkerThread, &QThread::finished, mMessagingStatisticsWorker, &QObject::deleteLater);

    // MessagingService -> MessagingStatisticsWorker.

    connect(&messagingService, &MessagingService::started, mMessagingStatisticsWorker,
            &MessagingStatisticsWorker::start);

    connect(&messagingService, &MessagingService::packetAccepted, mMessagingStatisticsWorker,
            &MessagingStatisticsWorker::onPacketAccepted);

    connect(&messagingService, &MessagingService::packetRejected, mMessagingStatisticsWorker,
            &MessagingStatisticsWorker::onPacketRejected);

    connect(&messagingService, &MessagingService::errored, mMessagingStatisticsWorker,
            &MessagingStatisticsWorker::stop);

    connect(&messagingService, &MessagingService::stopped, mMessagingStatisticsWorker,
            &MessagingStatisticsWorker::stop);

    // MessagingStatisticsWorker -> MessagingStatisticsService.

    connect(mMessagingStatisticsWorker, &MessagingStatisticsWorker::packetsPerSecondUpdated, this,
            &MessagingStatisticsService::packetsPerSecondUpdated);

    connect(mMessagingStatisticsWorker, &MessagingStatisticsWorker::bytesPerSecondUpdated, this,
            &MessagingStatisticsService::bytesPerSecondUpdated);

    connect(mMessagingStatisticsWorker, &MessagingStatisticsWorker::rejectedPacketsUpdated, this,
            &MessagingStatisticsService::rejectedPacketsUpdated);

    mWorkerThread->start();
  }

  MessagingStatisticsService::~MessagingStatisticsService()
  {
    mWorkerThread->quit();
    mWorkerThread->wait();
  }
}
