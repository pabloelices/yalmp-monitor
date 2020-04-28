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

#ifndef YALMP_MONITOR_CORE_MESSAGING_SERVICE_HPP
#define YALMP_MONITOR_CORE_MESSAGING_SERVICE_HPP

#pragma once

#include "YalmpMonitor/Core/Internals/Global.h"

#include <QObject>
#include <QThread>

namespace YalmpMonitor::Core::Internals
{
  class MessagingWorker;
}

namespace YalmpMonitor::Core
{
  using YalmpMonitor::Core::Internals::MessagingWorker;

  class YalmpPacket;

  class YALMP_MONITOR_CORE_EXPORT MessagingService final : public QObject
  {
    Q_OBJECT

  public:
    explicit MessagingService(QObject* parent = nullptr);
    ~MessagingService();
    bool isRunning() const;
  private slots:
    void onMessagingWorkerStarted();
    void onMessagingWorkerErrored(const QString& errorMessage);
    void onMessagingWorkerStopped();
  signals:
    void start(const QString& portName, qint32 baudRate);
    void stop();
    void started();
    void packetAccepted(const YalmpPacket& acceptedPacket);
    void packetRejected(const YalmpPacket& parsedPacket, quint8 computedChecksum);
    void errored(const QString& errorMessage);
    void stopped();

  private:
    QThread*         mWorkerThread;
    MessagingWorker* mMessagingWorker;
    bool             mIsRunning;
  };
}

#endif // YALMP_MONITOR_CORE_MESSAGING_SERVICE_HPP
