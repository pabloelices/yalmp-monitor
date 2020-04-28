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

#include <YalmpMonitor/Core/YalmpPacket.hpp>

using YalmpMonitor::Core::YalmpPacket;

class TestYalmpPacket : public QObject
{
  Q_OBJECT

private slots:
  void TestPacket1();
  void TestPacket2();
  void TestPacket3();
};

void TestYalmpPacket::TestPacket1()
{
  // 4E | 00 | 00 | FF
  // SF | ID | PL | CS

  QBENCHMARK
  {
    YalmpPacket packet {};

    QCOMPARE(packet.startFlag(), 0x4E);
    QCOMPARE(packet.messageId(), 0x00);
    QCOMPARE(packet.payloadLength(), 0x00);
    QCOMPARE(packet.payload(), QByteArray {});
    QCOMPARE(packet.checksum(), 0xFF);
  }
}

void TestYalmpPacket::TestPacket2()
{
  // 4E | 7F | 05 | 48 65 6C 6C 6F | 87
  // SF | ID | PL |        P       | CS
  //    |    |    |  H  e  l  l  o |

  QBENCHMARK
  {
    YalmpPacket packet {0x4E, 0x7F, QByteArray {"Hello"}};

    QCOMPARE(packet.startFlag(), 0x4E);
    QCOMPARE(packet.messageId(), 0x7F);
    QCOMPARE(packet.payloadLength(), 0x05);
    QCOMPARE(packet.payload(), QByteArray {"Hello"});
    QCOMPARE(packet.checksum(), 0x87);
  }
}

void TestYalmpPacket::TestPacket3()
{
  // 4E | FF | 05 | 30 2E 31 2E 30 | 0E
  // SF | ID | PL |        P       | CS
  //    |    |    |  0  .  1  .  0 |

  QBENCHMARK
  {
    YalmpPacket packet {0x4E, 0xFF, QByteArray {"0.1.0"}};

    QCOMPARE(packet.startFlag(), 0x4E);
    QCOMPARE(packet.messageId(), 0xFF);
    QCOMPARE(packet.payloadLength(), 0x05);
    QCOMPARE(packet.payload(), QByteArray {"0.1.0"});
    QCOMPARE(packet.checksum(), 0x0E);
  }
}

QTEST_APPLESS_MAIN(TestYalmpPacket)

#include "TestYalmpPacket.moc"
