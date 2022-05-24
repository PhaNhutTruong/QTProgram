#include "ctdonhang.h"

CTDonHang::CTDonHang()
{

}


QString CTDonHang::getTongTien() const
{
    return tongTien;
}

void CTDonHang::setTongTien(const QString &value)
{
    tongTien = value;
}

QString CTDonHang::getMaSP() const
{
    return maSP;
}

void CTDonHang::setMaSP(const QString &value)
{
    maSP = value;
}

QString CTDonHang::getTenSP() const
{
    return tenSP;
}

void CTDonHang::setTenSP(const QString &value)
{
    tenSP = value;
}

QString CTDonHang::getSoLuong() const
{
    return soLuong;
}

void CTDonHang::setSoLuong(const QString &value)
{
    soLuong = value;
}
