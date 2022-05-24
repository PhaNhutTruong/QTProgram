#ifndef CUSTOMMODELOFCUSTOMOBJECT_H
#define CUSTOMMODELOFCUSTOMOBJECT_H

#include <QAbstractTableModel>
#include <ctdonhang.h>


class CustomModelOfCustomObject:public QAbstractTableModel
{
public:
    CustomModelOfCustomObject();
    CustomModelOfCustomObject(QObject *parent);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QList<CTDonHang*> list;
    bool insertRows(int position, int rows, const QModelIndex &index);
    bool removeRows(int position, int rows, const QModelIndex &index);
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QList<CTDonHang *> getList();
    void setList(QList<CTDonHang *> clist);
};

#endif // CUSTOMMODELOFCUSTOMOBJECT_H
