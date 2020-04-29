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
#include "ui_MainWindow.h"

#include "TextAlignmentProxyModel.hpp"

#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , mUi(new Ui::MainWindow)
  , mPortNameListModel {new PortNameListModel {this}}
  , mBaudRateListModel {new BaudRateListModel {this}}
  , mMessagingService {new MessagingService {this}}
  , mYalmpMessageTableModel {new YalmpMessageTableModel {*mMessagingService, this}}
  , mMessagingStatisticsService {new MessagingStatisticsService {*mMessagingService, this}}
  , mTextAlignmentProxyModel {new TextAlignmentProxyModel {this}}
{
  mUi->setupUi(this);

  // Window icon.

  mWindowIcon.addFile("://resources/16x16.png");
  mWindowIcon.addFile("://resources/24x24.png");
  mWindowIcon.addFile("://resources/32x32.png");
  mWindowIcon.addFile("://resources/48x48.png");
  mWindowIcon.addFile("://resources/64x64.png");
  mWindowIcon.addFile("://resources/128x128.png");
  mWindowIcon.addFile("://resources/256x256.png");
  mWindowIcon.addFile("://resources/512x512.png");

  setWindowIcon(mWindowIcon);

  // Models.

  mUi->comboBoxPortName->setModel(mPortNameListModel);
  mUi->comboBoxBaudRate->setModel(mBaudRateListModel);

  mTextAlignmentProxyModel->setSourceModel(mYalmpMessageTableModel);

  mUi->tableViewMessagesTopRight->setModel(mTextAlignmentProxyModel);
  mUi->tableViewMessagesBottomRight->setModel(mTextAlignmentProxyModel);
  mUi->tableViewMessagesBottomLeft->setModel(mTextAlignmentProxyModel);
  mUi->tableViewMessagesTopLeft->setModel(mTextAlignmentProxyModel);

  // Table views.

  mUi->tableViewMessagesTopRight->setSelectionBehavior(QAbstractItemView::SelectRows);
  mUi->tableViewMessagesBottomRight->setSelectionBehavior(QAbstractItemView::SelectRows);
  mUi->tableViewMessagesBottomLeft->setSelectionBehavior(QAbstractItemView::SelectRows);
  mUi->tableViewMessagesTopLeft->setSelectionBehavior(QAbstractItemView::SelectRows);

  // Buttons.

  connect(mUi->pushButtonUpdate, &QPushButton::clicked, this, &MainWindow::onUpdateClicked);
  connect(mUi->pushButtonConnect, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
  connect(mUi->pushButtonDisconnect, &QPushButton::clicked, this, &MainWindow::onDisconnectClicked);

  // Menus.

  connect(mUi->actionExit, &QAction::triggered, this, &MainWindow::onExitTriggered);
  connect(mUi->actionSingleView, &QAction::triggered, this, &MainWindow::onSingleViewTriggered);
  connect(mUi->actionTwoColumnsView, &QAction::triggered, this, &MainWindow::onTwoColumnsViewTriggered);
  connect(mUi->actionGridView, &QAction::triggered, this, &MainWindow::onGridViewTriggered);
  connect(mUi->actionAbout, &QAction::triggered, this, &MainWindow::onAboutTriggered);

  // Splitters.

  connect(mUi->splitterTop, &QSplitter::splitterMoved, this, &MainWindow::onTopSplitterMoved);
  connect(mUi->splitterBottom, &QSplitter::splitterMoved, this, &MainWindow::onBottomSplitterMoved);

  // MessagingService -> MainWindow.

  connect(mMessagingService, &MessagingService::started, this, &MainWindow::onMessagingServiceStarted);
  connect(mMessagingService, &MessagingService::errored, this, &MainWindow::onMessagingServiceErrored);
  connect(mMessagingService, &MessagingService::stopped, this, &MainWindow::onMessagingServiceStopped);

  // MessagingStatisticsService -> MainWindow.

  connect(mMessagingStatisticsService, &MessagingStatisticsService::packetsPerSecondUpdated, this,
          &MainWindow::onPacketsPerSecondUpdated);

  connect(mMessagingStatisticsService, &MessagingStatisticsService::bytesPerSecondUpdated, this,
          &MainWindow::onBytesPerSecondUpdated);

  connect(mMessagingStatisticsService, &MessagingStatisticsService::rejectedPacketsUpdated, this,
          &MainWindow::onRejectedPacketsUpdated);

  // Prepare controls.

  setControlsToIdlePosition();

  // Set grid view as default.

  setGridView();
};

MainWindow::~MainWindow()
{
  delete mUi;
}

void MainWindow::onExitTriggered()
{
  close();
}

void MainWindow::onSingleViewTriggered()
{
  setSingleView();
}

void MainWindow::onTwoColumnsViewTriggered()
{
  setTwoColumnsView();
}

void MainWindow::onGridViewTriggered()
{
  setGridView();
}

void MainWindow::onTopSplitterMoved()
{
  // The following line does not trigger splitterBottom::splitterMoved so there is no circular signalling.

  mUi->splitterBottom->setSizes(mUi->splitterTop->sizes());
}

void MainWindow::onBottomSplitterMoved()
{
  // The following line does not trigger splitterTop::splitterMoved so there is no circular signalling.

  mUi->splitterTop->setSizes(mUi->splitterBottom->sizes());
}

void MainWindow::onAboutTriggered()
{
  static const QString titlePlaceholder {QStringLiteral("About %1")};
  static const QString textPlaceholder {QStringLiteral("<p><b>%1 %2</b></p><p><a href='%3'>%3</a></p>")};

  static const QString applicationName {QCoreApplication::applicationName()};
  static const QString applicationVersion {QCoreApplication::applicationVersion()};
  static const QString applicationUrl {QStringLiteral("https://github.com/pabloelices/yalmp-monitor")};

  static const QString title {titlePlaceholder.arg(applicationName)};
  static const QString text {textPlaceholder.arg(applicationName, applicationVersion, applicationUrl)};

  QMessageBox::about(this, title, text);
}

void MainWindow::onUpdateClicked()
{
  mPortNameListModel->updateData();

  setControlsToIdlePosition();
}

void MainWindow::onConnectClicked()
{
  const QString& portName {mUi->comboBoxPortName->currentText()};
  const qint32&  baudRate {static_cast<qint32>(mUi->comboBoxBaudRate->currentText().toInt())};

  mMessagingService->start(portName, baudRate);
}

void MainWindow::onDisconnectClicked()
{
  mMessagingService->stop();
}

void MainWindow::onMessagingServiceStarted()
{
  setControlsToBusyPosition();

  mYalmpMessageTableModel->clearData();
}

void MainWindow::onMessagingServiceErrored(const QString& errorMessage)
{
  setControlsToIdlePosition();

  QMessageBox::warning(this, "Error", errorMessage, QMessageBox::Ok, QMessageBox::Ok);
}

void MainWindow::onMessagingServiceStopped()
{
  setControlsToIdlePosition();
}

void MainWindow::onPacketsPerSecondUpdated(qint64 packetsPerSecond)
{
  mUi->labelPacketsPerSecond->setText(QString {"%1 Packets/s"}.arg(QString::number(packetsPerSecond)));
}

void MainWindow::onBytesPerSecondUpdated(qint64 bytesPerSecond)
{
  mUi->labelBytesPerSecond->setText(QString {"%1 Bytes/s"}.arg(QString::number(bytesPerSecond)));
}

void MainWindow::onRejectedPacketsUpdated(qint64 rejectedPackets)
{
  mUi->labelPacketsRejected->setText(QString {"%1 Packet(s) rejected"}.arg(QString::number(rejectedPackets)));
}

void MainWindow::setControlsToIdlePosition()
{
  mUi->pushButtonUpdate->setEnabled(true);

  mUi->comboBoxPortName->setEnabled(true);

  mUi->comboBoxBaudRate->setEnabled(true);

  mUi->pushButtonConnect->setEnabled(mPortNameListModel->rowCount() > 0);
  mUi->pushButtonConnect->show();

  mUi->pushButtonDisconnect->setDisabled(true);
  mUi->pushButtonDisconnect->hide();
}

void MainWindow::setControlsToBusyPosition()
{
  mUi->pushButtonUpdate->setDisabled(true);

  mUi->comboBoxPortName->setDisabled(true);

  mUi->comboBoxBaudRate->setDisabled(true);

  mUi->pushButtonConnect->setDisabled(true);
  mUi->pushButtonConnect->hide();

  mUi->pushButtonDisconnect->setEnabled(true);
  mUi->pushButtonDisconnect->show();
}

void MainWindow::setSingleView()
{
  mUi->splitterTop->show();

  mUi->tableViewMessagesTopRight->hide();
  mUi->splitterBottom->hide();
}

void MainWindow::setTwoColumnsView()
{
  mUi->splitterTop->show();
  mUi->tableViewMessagesTopRight->show();

  mUi->splitterBottom->hide();

  mUi->splitterTop->setSizes(QList<int> {1000, 1000});
}

void MainWindow::setGridView()
{
  mUi->splitterTop->show();
  mUi->tableViewMessagesTopRight->show();
  mUi->splitterBottom->show();

  mUi->splitterMiddle->setSizes(QList<int> {1000, 1000});
  mUi->splitterTop->setSizes(QList<int> {1000, 1000});
  mUi->splitterBottom->setSizes(QList<int> {1000, 1000});
}
