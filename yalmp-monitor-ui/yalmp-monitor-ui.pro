########################################################################################################################
#                                                                                                                      #
# YALMP Monitor <https://github.com/pabloelices/yalmp-monitor>                                                         #
# Copyright (C) 2020  Pablo Daniel Gómez Elices                                                                        #
#                                                                                                                      #
# This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public    #
# License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later #
# version.                                                                                                             #
#                                                                                                                      #
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied   #
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more        #
# details.                                                                                                             #
#                                                                                                                      #
# You should have received a copy of the GNU General Public License along with this program.  If not, see              #
# <http://www.gnu.org/licenses/>.                                                                                      #
#                                                                                                                      #
########################################################################################################################

QT += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.hpp

FORMS += \
    MainWindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../yalmp-monitor-core/release/ -lyalmp-monitor-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../yalmp-monitor-core/debug/ -lyalmp-monitor-core
else:unix: LIBS += -L$$OUT_PWD/../yalmp-monitor-core/ -lyalmp-monitor-core

INCLUDEPATH += $$PWD/../yalmp-monitor-core/include
DEPENDPATH += $$PWD/../yalmp-monitor-core/include

RESOURCES += \
  resources.qrc
