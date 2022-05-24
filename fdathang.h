#ifndef FDATHANG_H
#define FDATHANG_H

#include <QWidget>
#include <connection.h>
#include <ctdonhang.h>
#include <QList>
#include <custommodelofcustomobject.h>

namespace Ui {
class FDatHang;
}

class FDatHang : public QWidget
{
    Q_OBJECT

public:
    explicit FDatHang(QWidget *parent = nullptr);
    ~FDatHang();
    void loadData();
    void loadCTHD();
    void loadCBKH();
    void loadCBSP();
    void loadTabCTHD(int page = 1);
    void clearData();
    void tinhTongTien();
    void luuHoaDon();
    void luuCTHoaDon();
    int getTotalPage();

private slots:
    void on_cbKhachHang_currentTextChanged(const QString &arg1);

    void on_cbSanPham_currentTextChanged(const QString &arg1);

    void on_sbSL_valueChanged(int arg1);

    void on_btnXacNhan_clicked();

    void on_btnXoa_clicked();

    void on_btnThanhToan_clicked();

    void on_btnFirst_clicked();

    void on_btnBack_clicked();

    void on_btnNext_clicked();

    void on_btnEnd_clicked();

    void on_btnLoadCB_clicked();

private:
    Ui::FDatHang *ui;
    QList<CTDonHang*> list;
    int currentPage;
    int totalPage;

};

#endif // FDATHANG_H
