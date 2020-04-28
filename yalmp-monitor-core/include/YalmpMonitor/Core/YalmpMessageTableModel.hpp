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

#ifndef YALMP_MONITOR_CORE_YALMP_MESSAGE_TABLE_MODEL_HPP
#define YALMP_MONITOR_CORE_YALMP_MESSAGE_TABLE_MODEL_HPP

#pragma once

#include "YalmpMonitor/Core/Internals/Global.h"

#include <QAbstractTableModel>

namespace YalmpMonitor::Core
{
  class MessagingService;
  class YalmpPacket;

  class YALMP_MONITOR_CORE_EXPORT YalmpMessageTableModel final : public QAbstractTableModel
  {
    Q_OBJECT

  public:
    explicit YalmpMessageTableModel(const MessagingService& messagingService, QObject* parent = nullptr);
    int      rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int      columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool     hasChildren(const QModelIndex& parent = QModelIndex()) const override;
  public slots:
    void clearData();
  private slots:
    void onPacketAccepted(const YalmpPacket& acceptedPacket);

  private:
    QVector<QByteArray> mMessages;
  };
}

#endif // YALMP_MONITOR_CORE_YALMP_MESSAGE_TABLE_MODEL_HPP
