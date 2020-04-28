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

#include <QtTest>

#include <YalmpMonitor/Core/Internals/YalmpPacketParser.hpp>

#include <YalmpMonitor/Core/YalmpPacket.hpp>

#include <memory>

using YalmpMonitor::Core::Internals::YalmpPacketParser;

using YalmpMonitor::Core::YalmpPacket;

class TestYalmpPacketParser : public QObject
{
  Q_OBJECT

public:
  TestYalmpPacketParser();

private:
  std::unique_ptr<YalmpPacketParser> mYalmpPacketParser;

private slots:
  void initTestCase();
  void TestPacket1();
  void TestPacket2();
  void TestPacket3();
  void cleanupTestCase();
};

TestYalmpPacketParser::TestYalmpPacketParser() : mYalmpPacketParser {std::make_unique<YalmpPacketParser>(this)}

{
}

void TestYalmpPacketParser::initTestCase()
{
  qRegisterMetaType<YalmpPacket>("YalmpPacket");
}

void TestYalmpPacketParser::TestPacket1()
{
  // 4E | 00 | 00 | FF
  // SF | ID | PL | CS

  QByteArray bytes;

  bytes.resize(4);

  bytes[0] = 0x4E;
  bytes[1] = 0x00;
  bytes[2] = 0x00;
  bytes[3] = 0xFF;

  QSignalSpy spy {mYalmpPacketParser.get(), &YalmpPacketParser::packetAccepted};

  QBENCHMARK
  {
    mYalmpPacketParser->parse(bytes);

    QCOMPARE(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();

    YalmpPacket packet {arguments.at(0).value<YalmpPacket>()};

    QCOMPARE(packet.startFlag(), 0x4E);
    QCOMPARE(packet.messageId(), 0x00);
    QCOMPARE(packet.payloadLength(), 0x00);
    QCOMPARE(packet.payload(), QByteArray {});
    QCOMPARE(packet.checksum(), 0xFF);
  }
}

void TestYalmpPacketParser::TestPacket2()
{
  // 4E | 7F | 05 | 48 65 6C 6C 6F | 87
  // SF | ID | PL |        P       | CS
  //    |    |    |  H  e  l  l  o |

  QByteArray bytes;

  bytes.resize(9);

  bytes[0] = 0x4E;
  bytes[1] = 0x7F;
  bytes[2] = 0x05;
  bytes[3] = 0x48;
  bytes[4] = 0x65;
  bytes[5] = 0x6C;
  bytes[6] = 0x6C;
  bytes[7] = 0x6F;
  bytes[8] = 0x87;

  QSignalSpy spy {mYalmpPacketParser.get(), &YalmpPacketParser::packetAccepted};

  QBENCHMARK
  {
    mYalmpPacketParser->parse(bytes);

    QCOMPARE(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();

    YalmpPacket packet {arguments.at(0).value<YalmpPacket>()};

    QCOMPARE(packet.startFlag(), 0x4E);
    QCOMPARE(packet.messageId(), 0x7F);
    QCOMPARE(packet.payloadLength(), 0x05);
    QCOMPARE(packet.payload(), QByteArray {"Hello"});
    QCOMPARE(packet.checksum(), 0x87);
  }
}

void TestYalmpPacketParser::TestPacket3()
{
  // 4E | FF | 05 | 30 2E 31 2E 30 | 0E
  // SF | ID | PL |        P       | CS
  //    |    |    |  0  .  1  .  0 |

  QByteArray bytes;

  bytes.resize(9);

  bytes[0] = 0x4E;
  bytes[1] = 0xFF;
  bytes[2] = 0x05;
  bytes[3] = 0x30;
  bytes[4] = 0x2E;
  bytes[5] = 0x31;
  bytes[6] = 0x2E;
  bytes[7] = 0x30;
  bytes[8] = 0x0E;

  QSignalSpy spy {mYalmpPacketParser.get(), &YalmpPacketParser::packetAccepted};

  QBENCHMARK
  {
    mYalmpPacketParser->parse(bytes);

    QCOMPARE(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();

    YalmpPacket packet {arguments.at(0).value<YalmpPacket>()};

    QCOMPARE(packet.startFlag(), 0x4E);
    QCOMPARE(packet.messageId(), 0xFF);
    QCOMPARE(packet.payloadLength(), 0x05);
    QCOMPARE(packet.payload(), QByteArray {"0.1.0"});
    QCOMPARE(packet.checksum(), 0x0E);
  }
}

void TestYalmpPacketParser::cleanupTestCase()
{
}

QTEST_APPLESS_MAIN(TestYalmpPacketParser)

#include "TestYalmpPacketParser.moc"
