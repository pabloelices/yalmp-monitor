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

#include "MainWindow.hpp"

#include <QApplication>

#include <YalmpMonitor/Core/YalmpPacket.hpp>

using YalmpMonitor::Core::YalmpPacket;

int main(int argc, char* argv[])
{
  QCoreApplication::setOrganizationName("Pablo Daniel Gómez Elices");
  QCoreApplication::setApplicationName("YALMP Monitor");
  QCoreApplication::setApplicationVersion("2020.05.1-alpha");

  qRegisterMetaType<YalmpPacket>("YalmpPacket");

  QApplication application(argc, argv);

  MainWindow mainWindow;

  mainWindow.showMaximized();

  return application.exec();
}
