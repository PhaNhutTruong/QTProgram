#include "custommodel.h"
#include <QColor>
#include <QBrush>
#include <QFont>

customModel::customModel()
{

}

QList<CTDonHang> customModel::getList() const
{
    return list;
}

int customModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return list.size();
}
int customModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}
QVariant customModel::data(const QModelIndex &index, int role) const
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
QVariant customModel::headerData(int section, Qt::Orientation orientation, int role) const
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
            return tr("Mã Sản Phẩm");
        case 1:
            return tr("Tên Sản phẩm");
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

