#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDesktopWidget"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QSize size = this->sizeHint();
    QDesktopWidget* desktop = QApplication::desktop();
    int width = desktop->width();
    int height = desktop->height();
    int mw = size.width();
    int mh = size.height();
    int centerW = (width/2) - (mw/2);
    int centerH = (height/2) - (mh/2);
    this->move(centerW/2.5, centerH/2.5);
    conn= new Connection();
    conn->openCon();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnKhachHang_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->currentPage->setText("Khách Hàng");
}

void MainWindow::on_btnSanPham_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
     ui->currentPage->setText("Sản Phẩm");
}

void MainWindow::on_btnDatHang_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->currentPage->setText("Đặt Hàng");
}
