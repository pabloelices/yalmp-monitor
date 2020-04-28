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

#include "YalmpMonitor/Core/Internals/MessagingStatisticsWorker.hpp"

#include "YalmpMonitor/Core/YalmpPacket.hpp"

namespace YalmpMonitor::Core::Internals
{
  MessagingStatisticsWorker::MessagingStatisticsWorker(QObject* parent)
    : QObject {parent}
    , mTimer {new QTimer {this}}
    , mAcceptedPacketsInASecond {0}
    , mReceivedBytesInASecond {0}
    , mRejectedPackets {0}
  {
    mTimer->setTimerType(Qt::PreciseTimer);
    mTimer->setInterval(1000);

    connect(mTimer, &QTimer::timeout, this, &MessagingStatisticsWorker::onTimerTimeout);
  }

  void MessagingStatisticsWorker::start()
  {
    mAcceptedPacketsInASecond = 0;
    mReceivedBytesInASecond   = 0;
    mRejectedPackets          = 0;

    emit packetsPerSecondUpdated(mAcceptedPacketsInASecond);
    emit bytesPerSecondUpdated(mReceivedBytesInASecond);
    emit rejectedPacketsUpdated(mRejectedPackets);

    mTimer->start();
  }

  void MessagingStatisticsWorker::onPacketAccepted(const YalmpPacket& acceptedPacket)
  {
    if (mTimer->isActive())
    {
      mAcceptedPacketsInASecond++;

      mReceivedBytesInASecond += acceptedPacket.payloadLength();
    }
  }

  void MessagingStatisticsWorker::onPacketRejected(const YalmpPacket& parsedPacket, quint8 computedChecksum)
  {
    Q_UNUSED(parsedPacket)
    Q_UNUSED(computedChecksum)

    if (mTimer->isActive())
    {
      mRejectedPackets++;
    }
  }

  void MessagingStatisticsWorker::stop()
  {
    mTimer->stop();

    mAcceptedPacketsInASecond = 0;
    mReceivedBytesInASecond   = 0;
    mRejectedPackets          = 0;

    emit packetsPerSecondUpdated(mAcceptedPacketsInASecond);
    emit bytesPerSecondUpdated(mReceivedBytesInASecond);
    emit rejectedPacketsUpdated(mRejectedPackets);
  }

  void MessagingStatisticsWorker::onTimerTimeout()
  {
    emit packetsPerSecondUpdated(mAcceptedPacketsInASecond);
    emit bytesPerSecondUpdated(mReceivedBytesInASecond);
    emit rejectedPacketsUpdated(mRejectedPackets);

    mAcceptedPacketsInASecond = 0;
    mReceivedBytesInASecond   = 0;
  }
}
