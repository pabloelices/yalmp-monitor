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

#include "YalmpMonitor/Core/BaudRateListModel.hpp"

namespace YalmpMonitor::Core
{
  BaudRateListModel::BaudRateListModel(QObject* parent) : QAbstractListModel {parent}, mBaudRates {QVector<qint32>()}
  {
    beginInsertRows(QModelIndex {}, 0, 7);

    mBaudRates.resize(8);

    mBaudRates.replace(0, 115200);
    mBaudRates.replace(1, 57600);
    mBaudRates.replace(2, 38400);
    mBaudRates.replace(3, 19200);
    mBaudRates.replace(4, 9600);
    mBaudRates.replace(5, 4800);
    mBaudRates.replace(6, 2400);
    mBaudRates.replace(7, 1200);

    endInsertRows();
  }

  int BaudRateListModel::rowCount(const QModelIndex& parent) const
  {
    Q_UNUSED(parent)

    return mBaudRates.count();
  }

  QVariant BaudRateListModel::data(const QModelIndex& index, int role) const
  {
    if (!index.isValid())
    {
      return QVariant {};
    }

    if (index.row() >= mBaudRates.count())
    {
      return QVariant {};
    }

    if (role == Qt::DisplayRole)
    {
      return mBaudRates.at(index.row());
    }
    else
    {
      return QVariant {};
    }
  }

  QVariant BaudRateListModel::headerData(int section, Qt::Orientation orientation, int role) const
  {
    if (role != Qt::DisplayRole)
    {
      return QVariant {};
    }

    if (orientation == Qt::Horizontal)
    {
      if (section == 0)
      {
        return QStringLiteral("Baud Rate");
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
}
