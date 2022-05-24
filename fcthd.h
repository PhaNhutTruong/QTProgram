#ifndef FCTHD_H
#define FCTHD_H

#include <QDialog>

namespace Ui {
class FCTHD;
}

class FCTHD : public QDialog
{
    Q_OBJECT

public:
    explicit FCTHD(QWidget *parent = nullptr);
    ~FCTHD();

private:
    Ui::FCTHD *ui;
};

#endif // FCTHD_H
