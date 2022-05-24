#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <connection.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Connection *conn;

private slots:
    void on_btnKhachHang_clicked();

    void on_btnSanPham_clicked();

    void on_btnDatHang_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
