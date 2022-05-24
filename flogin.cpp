#include "flogin.h"
#include "ui_flogin.h"
#include "QDesktopWidget"
#include "mainwindow.h"
#include "QMessageBox"

FLogin::FLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FLogin)
{
    QSize size = this->sizeHint();
    QDesktopWidget* desktop = QApplication::desktop();
    int width = desktop->width();
    int height = desktop->height();
    int mw = size.width();
    int mh = size.height();
    int centerW = (width/2) - (mw/2);
    int centerH = (height/2) - (mh/2);
    this->move(centerW/1.6, centerH/1.9);
    conn= new Connection();
    ui->setupUi(this);
}

FLogin::~FLogin()
{
    delete ui;
}

void FLogin::on_btnDangNhap_clicked()
{
    QString username,password;
    username=ui->txtUsername->text();
    password=ui->txtPassword->text();
    if(!conn->openCon()){
        QMessageBox::critical(this,"Thông báo","Không thể kết nối tới server");
        return;
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM TaiKhoan WHERE Username = '"+username+"' and Password='"+password+"'");
    if(query.exec()){
       int count=0;
       while (query.next()) {
           count++;
       }
       if(count==1){
           conn->closeCon();
           MainWindow *w=new MainWindow();
           w->show();
           this->hide();
       }else {
           QMessageBox::critical(this,"Thông báo","Sai tên đăng nhập hoặc mật khẩu!!");
       }
    }
}
