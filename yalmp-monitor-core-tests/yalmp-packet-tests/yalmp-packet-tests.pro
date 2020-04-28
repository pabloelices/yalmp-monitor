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

QT += testlib

QT -= gui

CONFIG += c++17

CONFIG += qt console warn_on depend_includepath testcase

CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    TestYalmpPacket.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../yalmp-monitor-core/release/ -lyalmp-monitor-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../yalmp-monitor-core/debug/ -lyalmp-monitor-core
else:unix: LIBS += -L$$OUT_PWD/../../yalmp-monitor-core/ -lyalmp-monitor-core

INCLUDEPATH += $$PWD/../../yalmp-monitor-core/include
DEPENDPATH += $$PWD/../../yalmp-monitor-core/include
