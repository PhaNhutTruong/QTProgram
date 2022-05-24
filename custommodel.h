#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H

#include "ctdonhang.h"
#include "QList"
#include <QAbstractListModel>

class customModel
{
public:
    customModel();
    QList<CTDonHang> list;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QList<CTDonHang> getList() const;
};

#endif // CUSTOMMODEL_H
