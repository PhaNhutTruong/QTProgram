#ifndef FLOGIN_H
#define FLOGIN_H

#include <QWidget>
#include <connection.h>

namespace Ui {
class FLogin;
}

class FLogin : public QWidget
{
    Q_OBJECT

public:
    explicit FLogin(QWidget *parent = nullptr);
    ~FLogin();

private slots:
    void on_btnDangNhap_clicked();


private:
    Ui::FLogin *ui;
    Connection *conn;
};

#endif // FLOGIN_H
