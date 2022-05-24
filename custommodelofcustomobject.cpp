#include "custommodelofcustomobject.h"
#include <QColor>
#include <QBrush>
#include <QFont>

CustomModelOfCustomObject::CustomModelOfCustomObject()
{
}
CustomModelOfCustomObject::CustomModelOfCustomObject(QObject *parent):QAbstractTableModel(parent)
{
}
int CustomModelOfCustomObject::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return list.size();
}
int CustomModelOfCustomObject::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}
QVariant CustomModelOfCustomObject::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= list.size() || index.row() < 0)
        return QVariant();
    switch(role){
    case Qt::BackgroundColorRole:
    {
        return QVariant(QBrush (QColor(Qt::white)));
    }
    case Qt::TextAlignmentRole:
    {
        return QVariant ( Qt::AlignVCenter | Qt::AlignHCenter );
    }
    case Qt::DisplayRole:
    {
        CTDonHang* obj = list.at(index.row());
        switch(index.column())
        {
        case 0:
            return obj->getMaSP();
        case 1:
            return obj->getTenSP();
        case 2:
            return obj->getSoLuong();
        case 3:
            return obj->getTongTien();
        default:
            return false;
        }//displayrole switch
    }
    }// role switch
    return QVariant();
}
QVariant CustomModelOfCustomObject::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if(role==Qt::FontRole)
    {
        // return QVariant(QBrush (QColor(Qt::white)));
        return QFont("Courier New", 24, QFont::Bold);
    }
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("Mã sản phẩm");
        case 1:
            return tr("Tên sản phẩm");
        case 2:
            return tr("Số lượng");
        case 3:
            return tr("Tổng tiền");
        default:
            return QVariant();
        }
    }
    return QVariant();
}
bool CustomModelOfCustomObject::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);
    for (int row=0; row < rows; row++) {
        CTDonHang* obj;
        list.insert(position, obj);
    }
    endInsertRows();
    return true;
}
bool CustomModelOfCustomObject::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);
    for (int row=0; row < rows; ++row) {
        list.removeAt(position);
    }
    endRemoveRows();
    return true;
}
bool CustomModelOfCustomObject::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();
        CTDonHang* p = list.value(row);
        /*if (index.column() == 0)
            p->set_Account(value.toString());
        else if (index.column() == 1)
            p->set_Exchange(value.toString());
        else
            return false;*/
        switch(index.column())
        {
        case 0:
            p->setMaSP(value.toString());
            break;
        case 1:
            p->setTenSP(value.toString());
            break;
        case 2:
            p->setSoLuong(value.toString());
            break;
        case 3:
            p->setTongTien(value.toString());
            break;
        default:
            return false;
        }
        list.replace(row, p);
        emit(dataChanged(index, index));
        return true;
    }
    return false;
}
QList<CTDonHang*> CustomModelOfCustomObject::getList()
{
    return list;
}
void CustomModelOfCustomObject :: setList(QList<CTDonHang *> clist){
    list = clist;
}
