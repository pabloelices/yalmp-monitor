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

#include "YalmpMonitor/Core/MessagingService.hpp"

#include "YalmpMonitor/Core/Internals/MessagingWorker.hpp"

namespace YalmpMonitor::Core
{
  using YalmpMonitor::Core::Internals::MessagingWorker;

  MessagingService::MessagingService(QObject* parent)
    : QObject {parent}
    , mWorkerThread {new QThread {this}}
    , mMessagingWorker {new MessagingWorker}
    , mIsRunning {false}
  {
    mMessagingWorker->moveToThread(mWorkerThread);

    connect(mWorkerThread, &QThread::finished, mMessagingWorker, &QObject::deleteLater);

    connect(this, &MessagingService::start, mMessagingWorker, &MessagingWorker::start);
    connect(this, &MessagingService::stop, mMessagingWorker, &MessagingWorker::stop);

    connect(mMessagingWorker, &MessagingWorker::started, this, &MessagingService::onMessagingWorkerStarted);
    connect(mMessagingWorker, &MessagingWorker::packetAccepted, this, &MessagingService::packetAccepted);
    connect(mMessagingWorker, &MessagingWorker::packetRejected, this, &MessagingService::packetRejected);
    connect(mMessagingWorker, &MessagingWorker::errored, this, &MessagingService::onMessagingWorkerErrored);
    connect(mMessagingWorker, &MessagingWorker::stopped, this, &MessagingService::onMessagingWorkerStopped);

    mWorkerThread->start();
  }

  MessagingService::~MessagingService()
  {
    mWorkerThread->quit();
    mWorkerThread->wait();
  }

  bool MessagingService::isRunning() const
  {
    return mIsRunning;
  }

  void MessagingService::onMessagingWorkerStarted()
  {
    mIsRunning = true;

    emit started();
  }

  void MessagingService::onMessagingWorkerErrored(const QString& errorMessage)
  {
    mIsRunning = false;

    emit errored(errorMessage);
  }

  void MessagingService::onMessagingWorkerStopped()
  {
    mIsRunning = false;

    emit stopped();
  }
}
