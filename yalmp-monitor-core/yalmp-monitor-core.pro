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

QT -= gui

QT += serialport

TEMPLATE = lib

DEFINES += YALMP_MONITOR_CORE_LIBRARY

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += include

SOURCES += \
    source/YalmpMonitor/Core/BaudRateListModel.cpp \
    source/YalmpMonitor/Core/Internals/MessagingStatisticsWorker.cpp \
    source/YalmpMonitor/Core/Internals/MessagingWorker.cpp \
    source/YalmpMonitor/Core/Internals/YalmpChecksum.cpp \
    source/YalmpMonitor/Core/Internals/YalmpPacketParser.cpp \
    source/YalmpMonitor/Core/MessagingService.cpp \
    source/YalmpMonitor/Core/MessagingStatisticsService.cpp \
    source/YalmpMonitor/Core/PortNameListModel.cpp \
    source/YalmpMonitor/Core/Version.cpp \
    source/YalmpMonitor/Core/YalmpMessageTableModel.cpp \
    source/YalmpMonitor/Core/YalmpPacket.cpp

HEADERS += \
    include/YalmpMonitor/Core/BaudRateListModel.hpp \
    include/YalmpMonitor/Core/Internals/Global.h \
    include/YalmpMonitor/Core/Internals/MessagingStatisticsWorker.hpp \
    include/YalmpMonitor/Core/Internals/MessagingWorker.hpp \
    include/YalmpMonitor/Core/Internals/YalmpChecksum.hpp \
    include/YalmpMonitor/Core/Internals/YalmpPacketParser.hpp \
    include/YalmpMonitor/Core/MessagingService.hpp \
    include/YalmpMonitor/Core/MessagingStatisticsService.hpp \
    include/YalmpMonitor/Core/PortNameListModel.hpp \
    include/YalmpMonitor/Core/Version.hpp \
    include/YalmpMonitor/Core/YalmpMessageTableModel.hpp \
    include/YalmpMonitor/Core/YalmpPacket.hpp
