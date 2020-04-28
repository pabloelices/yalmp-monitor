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

#include "YalmpMonitor/Core/PortNameListModel.hpp"

namespace YalmpMonitor::Core
{
  PortNameListModel::PortNameListModel(QObject* parent)
    : QAbstractListModel {parent}
    , mSerialPortsInfo {QList<QSerialPortInfo> {QSerialPortInfo::availablePorts()}}
  {
    updateData();
  }

  int PortNameListModel::rowCount(const QModelIndex& parent) const
  {
    Q_UNUSED(parent)

    return mSerialPortsInfo.count();
  }

  QVariant PortNameListModel::data(const QModelIndex& index, int role) const
  {
    if (!index.isValid())
    {
      return QVariant {};
    }

    if (index.row() >= mSerialPortsInfo.count())
    {
      return QVariant {};
    }

    if (role == Qt::DisplayRole)
    {
      return mSerialPortsInfo.at(index.row()).portName();
    }
    else
    {
      return QVariant {};
    }
  }

  QVariant PortNameListModel::headerData(int section, Qt::Orientation orientation, int role) const
  {
    if (role != Qt::DisplayRole)
    {
      return QVariant {};
    }

    if (orientation == Qt::Horizontal)
    {
      if (section == 0)
      {
        return QStringLiteral("Port Name");
      }
      else
      {
        return QVariant {};
      }
    }
    else
    {
      return QStringLiteral("%1").arg(section);
    }
  }

  void PortNameListModel::updateData()
  {
    if (mSerialPortsInfo.count() > 0)
    {
      beginRemoveRows(QModelIndex {}, 0, mSerialPortsInfo.count() - 1);

      mSerialPortsInfo.clear();

      endRemoveRows();
    }

    const QList<QSerialPortInfo> temp {QSerialPortInfo::availablePorts()};

    if (temp.count() > 0)
    {
      beginInsertRows(QModelIndex {}, 0, temp.count() - 1);

      mSerialPortsInfo.append(temp);

      endInsertRows();
    }
  }
}
