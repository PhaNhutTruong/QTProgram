#include "fcthd.h"
#include "ui_fcthd.h"

FCTHD::FCTHD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FCTHD)
{
    ui->setupUi(this);
}

FCTHD::~FCTHD()
{
    delete ui;
}
