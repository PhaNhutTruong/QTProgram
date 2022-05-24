#ifndef FSANPHAM_H
#define FSANPHAM_H

#include <QWidget>
#include <connection.h>
#include <QSqlTableModel>

namespace Ui {
class FSanPham;
}

class FSanPham : public QWidget
{
    Q_OBJECT

public:
    explicit FSanPham(QWidget *parent = nullptr);
    ~FSanPham();
    Connection *conn;
    void loadData(int page=1);
    void clearData();
    int getTotalPage();

private slots:
    void on_btnLT_clicked();

    void on_btnThem_clicked();

    void on_btnXoa_clicked();

    void on_btnSua_clicked();

    void on_tabSanPham_clicked(const QModelIndex &index);

    void on_btnFirst_clicked();

    void on_btnBack_clicked();

    void on_btnNext_clicked();

    void on_btnEnd_clicked();

private:
    Ui::FSanPham *ui;
    int currentPage;
    int totalPage;
};

#endif // FSANPHAM_H
