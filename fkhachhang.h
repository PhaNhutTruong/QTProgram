#ifndef FKHACHHANG_H
#define FKHACHHANG_H

#include <QWidget>
#include <connection.h>
#include <QSqlTableModel>

namespace Ui {
class FKhachHang;
}

class FKhachHang : public QWidget
{
    Q_OBJECT

public:
    explicit FKhachHang(QWidget *parent = nullptr);
    ~FKhachHang();
    Connection *conn;
    void loadData(int page = 1);
    void clearData();
    int getTotalPage();

private slots:
    void on_btnThem_clicked();

    void on_tabKhachHang_clicked(const QModelIndex &index);

    void on_btnXoa_clicked();

    void on_btnSua_clicked();

    void on_pushButton_clicked();

    void on_btnBack_clicked();

    void on_btnNext_clicked();

    void on_btnFirst_clicked();

    void on_btnEnd_clicked();

private:
    Ui::FKhachHang *ui;
    int currentPage;
    int totalPage;

};

#endif // FKHACHHANG_H
