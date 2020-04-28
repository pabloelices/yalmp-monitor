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

#include "YalmpMonitor/Core/YalmpMessageTableModel.hpp"

#include "YalmpMonitor/Core/MessagingService.hpp"
#include "YalmpMonitor/Core/YalmpPacket.hpp"

namespace YalmpMonitor::Core
{
  static const quint16 MESSAGE_COUNT {256};

  YalmpMessageTableModel::YalmpMessageTableModel(const MessagingService& messagingService, QObject* parent)
    : QAbstractTableModel {parent}
    , mMessages {QVector<QByteArray>()}
  {
    beginInsertRows(QModelIndex {}, 0, MESSAGE_COUNT - 1);

    mMessages.resize(MESSAGE_COUNT);

    endInsertRows();

    connect(&messagingService, &MessagingService::packetAccepted, this, &YalmpMessageTableModel::onPacketAccepted);
  }

  int YalmpMessageTableModel::rowCount(const QModelIndex& parent) const
  {
    Q_UNUSED(parent)

    return mMessages.count();
  }

  int YalmpMessageTableModel::columnCount(const QModelIndex& parent) const
  {
    Q_UNUSED(parent)

    return 2;
  }

  QVariant YalmpMessageTableModel::data(const QModelIndex& index, int role) const
  {
    if (!index.isValid())
    {
      return QVariant {};
    }

    if (index.row() >= mMessages.count())
    {
      return QVariant {};
    }

    if (role == Qt::DisplayRole)
    {
      if (index.column() == 0)
      {
        return index.row();
      }
      else if (index.column() == 1)
      {
        return mMessages.value(index.row());
      }
      else
      {
        return QVariant {};
      }
    }
    else
    {
      return QVariant();
    }
  }

  QVariant YalmpMessageTableModel::headerData(int section, Qt::Orientation orientation, int role) const
  {
    if (role != Qt::DisplayRole)
    {
      return QVariant {};
    }

    if (orientation == Qt::Horizontal)
    {
      if (section == 0)
      {
        return QStringLiteral("Message ID");
      }
      else if (section == 1)
      {
        return QStringLiteral("Payload");
      }
      else
      {
        return QVariant {};
      }
    }
    else // orientation == Qt::Vertical
    {
      return QStringLiteral("%1").arg(section);
    }
  }

  bool YalmpMessageTableModel::hasChildren(const QModelIndex& parent) const
  {
    Q_UNUSED(parent)

    return false;
  }

  void YalmpMessageTableModel::clearData()
  {
    for (int i = 0; i < mMessages.count(); i++)
    {
      mMessages.replace(i, QByteArray {});
    }

    QModelIndex topLeft     = createIndex(0, 1);
    QModelIndex bottomRight = createIndex(mMessages.count() - 1, 1);

    emit dataChanged(topLeft, bottomRight);
  }

  void YalmpMessageTableModel::onPacketAccepted(const YalmpPacket& acceptedPacket)
  {
    mMessages.replace(acceptedPacket.messageId(), acceptedPacket.payload());

    QModelIndex payloadCell = createIndex(acceptedPacket.messageId(), 1);

    emit dataChanged(payloadCell, payloadCell);
  }
}
