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

#include "YalmpMonitor/Core/Internals/MessagingWorker.hpp"

#include "YalmpMonitor/Core/Internals/YalmpPacketParser.hpp"

namespace YalmpMonitor::Core::Internals
{
  static const quint16 MAX_PACKET_SIZE {259};

  MessagingWorker::MessagingWorker()
    : QObject {nullptr}
    , mSerialPort {new QSerialPort {this}}
    , mYalmpPacketParser {new YalmpPacketParser {this}}
  {
    mSerialPort->setReadBufferSize(MAX_PACKET_SIZE);

    // _serialPort -> this

    connect(mSerialPort, &QSerialPort::readyRead, this, &MessagingWorker::onSerialPortReadyRead);
    connect(mSerialPort, &QSerialPort::errorOccurred, this, &MessagingWorker::onSerialPortError);

    // _frameParser -> this

    connect(mYalmpPacketParser, &YalmpPacketParser::packetAccepted, this, &MessagingWorker::packetAccepted);
    connect(mYalmpPacketParser, &YalmpPacketParser::packetRejected, this, &MessagingWorker::packetRejected);
  }

  void MessagingWorker::start(const QString& portName, qint32 baudRate)
  {
    if (!mSerialPort->isOpen())
    {
      mSerialPort->setPortName(portName);
      mSerialPort->setBaudRate(baudRate);

      const bool opened {mSerialPort->open(QIODevice::ReadOnly)};

      if (opened)
      {
        mSerialPort->clear(QSerialPort::Direction::Input);

        emit started();
      }
    }
  }

  void MessagingWorker::stop()
  {
    if (mSerialPort->isOpen())
    {
      mSerialPort->close();

      mYalmpPacketParser->reset();

      emit stopped();
    }
  }

  void MessagingWorker::onSerialPortReadyRead()
  {
    mYalmpPacketParser->parse(mSerialPort->readAll());
  }

  void MessagingWorker::onSerialPortError(QSerialPort::SerialPortError error)
  {
    if (error != QSerialPort::SerialPortError::NoError)
    {
      switch (error)
      {
        case QSerialPort::SerialPortError::DeviceNotFoundError:

          emit errored(QStringLiteral("Device %1 not found.").arg(mSerialPort->portName()));

          break;

        case QSerialPort::SerialPortError::PermissionError:
        case QSerialPort::SerialPortError::OpenError:

          emit errored(QStringLiteral("The device %1 is already opened or the user does not have the right permissions "
                                      "to open it.")
                         .arg(mSerialPort->portName()));

          break;

        case QSerialPort::SerialPortError::ReadError:
        case QSerialPort::SerialPortError::ResourceError:

          emit errored(QStringLiteral("Device %1 unavailable.").arg(mSerialPort->portName()));

          break;

        case QSerialPort::SerialPortError::UnknownError:

          emit errored(QStringLiteral("Unknown error."));

          break;

        default:

          emit errored(QStringLiteral("Internal error."));

          break;
      }
    }

    stop();
  }
}
