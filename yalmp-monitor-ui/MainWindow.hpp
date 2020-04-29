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

#ifndef YALMP_MONITOR_UI_MAIN_WINDOW_HPP
#define YALMP_MONITOR_UI_MAIN_WINDOW_HPP

#pragma once

#include <YalmpMonitor/Core/BaudRateListModel.hpp>
#include <YalmpMonitor/Core/MessagingService.hpp>
#include <YalmpMonitor/Core/MessagingStatisticsService.hpp>
#include <YalmpMonitor/Core/PortNameListModel.hpp>
#include <YalmpMonitor/Core/YalmpMessageTableModel.hpp>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
  namespace Ui
  {
    class MainWindow;
  }
QT_END_NAMESPACE

using YalmpMonitor::Core::BaudRateListModel;
using YalmpMonitor::Core::MessagingService;
using YalmpMonitor::Core::MessagingStatisticsService;
using YalmpMonitor::Core::PortNameListModel;
using YalmpMonitor::Core::YalmpMessageTableModel;

class TextAlignmentProxyModel;

class MainWindow final : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
private slots:
  void onExitTriggered();
  void onSingleViewTriggered();
  void onTwoColumnsViewTriggered();
  void onGridViewTriggered();
  void onAboutTriggered();
  void onUpdateClicked();
  void onConnectClicked();
  void onDisconnectClicked();
  void onTopSplitterMoved();
  void onBottomSplitterMoved();
  void onMessagingServiceStarted();
  void onMessagingServiceErrored(const QString& errorMessage);
  void onMessagingServiceStopped();
  void onPacketsPerSecondUpdated(qint64 packetsPerSecond);
  void onBytesPerSecondUpdated(qint64 bytesPerSecond);
  void onRejectedPacketsUpdated(qint64 rejectedPackets);

private:
  void setControlsToIdlePosition();
  void setControlsToBusyPosition();

  void setSingleView();
  void setTwoColumnsView();
  void setGridView();

  Ui::MainWindow*             mUi;
  QIcon                       mWindowIcon;
  PortNameListModel*          mPortNameListModel;
  BaudRateListModel*          mBaudRateListModel;
  MessagingService*           mMessagingService;
  YalmpMessageTableModel*     mYalmpMessageTableModel;
  MessagingStatisticsService* mMessagingStatisticsService;
  TextAlignmentProxyModel*    mTextAlignmentProxyModel;
};

#endif // YALMP_MONITOR_UI_MAIN_WINDOW_HPP
