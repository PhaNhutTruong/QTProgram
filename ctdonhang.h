#ifndef CTDONHANG_H
#define CTDONHANG_H

#include "QString"


class CTDonHang
{
public:
    CTDonHang();

    QString getTongTien() const;
    void setTongTien(const QString &value);

    QString getMaSP() const;
    void setMaSP(const QString &value);

    QString getTenSP() const;
    void setTenSP(const QString &value);

    QString getSoLuong() const;
    void setSoLuong(const QString &value);

private:
    QString maSP;
    QString tenSP;
    QString soLuong;
    QString tongTien;
};

#endif // CTDONHANG_H
