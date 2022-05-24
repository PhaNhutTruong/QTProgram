#include "fkhachhang.h"
#include "ui_fkhachhang.h"
#include "QSqlQuery"
#include "QMessageBox"

FKhachHang::FKhachHang(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FKhachHang)
{
    ui->setupUi(this);
    loadData();
}

FKhachHang::~FKhachHang()
{
    delete ui;
}

void FKhachHang::loadData(int page){
        int limit=5;
        int skip=(page-1)*limit;
        currentPage=page;
        getTotalPage();
        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery query;
        query.prepare("SELECT * FROM KhachHang ORDER BY MaKH DESC LIMIT "+QString::number(skip)+","+QString::number(limit));
        query.exec();
        model->setQuery(query);
        ui->tabKhachHang->setModel(model);
        ui->tabKhachHang->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tabKhachHang->verticalHeader()->hide();
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Mã Khách Hàng"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Tên Khách Hàng"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Số điện thoại"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Địa chỉ"));
        ui->tabKhachHang->show();
        ui->lbPage->setText(QString::number(currentPage)+" / "+QString::number(totalPage));
    clearData();
}

void FKhachHang::clearData(){
    ui->txtTenKH->clear();
    ui->txtDiaChi->clear();
    ui->txtSDT->clear();
    ui->txtMaKH->clear();
    ui->btnSua->setEnabled(false);
    ui->btnXoa->setEnabled(false);
}

int FKhachHang::getTotalPage()
{
    QSqlQuery query;
    query.prepare("SELECT Count(MaKH) FROM KhachHang");
    if(query.exec()){
        while(query.next()){
           totalPage=ceil((query.value(0).toDouble())/5);
       }
        return totalPage;
    }
    return totalPage;
}

void FKhachHang::on_btnThem_clicked()
{
    if(QMessageBox::question(this, "Thông báo", "Bạn có muốn thêm?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::No){
        return;
    }
    QString tenKH,sdt,diachi;
    tenKH=ui->txtTenKH->text();
    sdt=ui->txtSDT->text();
    diachi=ui->txtDiaChi->text();
    if(tenKH.isEmpty()){
        QMessageBox::critical(this,"Thông báo","Tên khách hàng không được bỏ trống");
        return;
    }
        QSqlQuery query;
        query.prepare("INSERT INTO KhachHang (TenKH,SDT,DiaChi) VALUES ('"+tenKH+"','"+sdt+"','"+diachi+"')");
        if(query.exec()){
            QMessageBox::critical(this,"Thông báo","Thêm thành công");
            loadData();
        }
}

void FKhachHang::on_tabKhachHang_clicked(const QModelIndex &index)
{
    QString id = index.sibling(index.row(), 0).data().toString();
        QSqlQuery query;
        query.prepare("SELECT * FROM KhachHang WHERE MaKH="+id);
        if(query.exec()){
            while(query.next()){
                ui->txtMaKH->setText(query.value(0).toString());
                ui->txtTenKH->setText(query.value(1).toString());
                ui->txtSDT->setText(query.value(2).toString());
                ui->txtDiaChi->setText(query.value(3).toString());
            }
            ui->btnSua->setEnabled(true);
            ui->btnXoa->setEnabled(true);
         }
}

void FKhachHang::on_btnXoa_clicked()
{
    if(QMessageBox::question(this, "Thông báo", "Bạn có muốn xóa ?\n Khách hàng tên: "+ ui->txtTenKH->text(),QMessageBox::Yes|QMessageBox::No)==QMessageBox::No){
        return;
    }
    QString id = ui->txtMaKH->text();
        QSqlQuery query;
        query.prepare("DELETE FROM KhachHang WHERE MaKH="+id);
        if(query.exec()){
           loadData();
         }
}

void FKhachHang::on_btnSua_clicked()
{
    if(QMessageBox::question(this, "Thông báo", "Bạn có muốn sửa? \n Khách hàng có id :"+ui->txtMaKH->text(),QMessageBox::Yes|QMessageBox::No)==QMessageBox::No){
        return;
    }

    QString tenKH,sdt,diachi,id;
    id = ui->txtMaKH->text();
    tenKH=ui->txtTenKH->text();
    sdt=ui->txtSDT->text();
    diachi=ui->txtDiaChi->text();

        QSqlQuery query;
        query.prepare("UPDATE KhachHang SET TenKH='"+tenKH+"',SDT='"+sdt+"',DiaChi='"+diachi+"' WHERE MaKH="+id);
        if(query.exec()){
            QMessageBox::critical(this,"Thông báo","Sửa thành công");
            loadData();
        }
}

void FKhachHang::on_pushButton_clicked()
{
    loadData();
}

void FKhachHang::on_btnBack_clicked()
{
    int page=currentPage-1;
    if(page<1){
        currentPage=1;
        return;
    }
    loadData(page);
}

void FKhachHang::on_btnNext_clicked()
{
    int page=currentPage+1;
    if(page>totalPage){
        currentPage=totalPage;
        return;
    }
    loadData(page);
}

void FKhachHang::on_btnFirst_clicked()
{
    int page = currentPage =1;
    loadData(page);
}

void FKhachHang::on_btnEnd_clicked()
{
    int page = currentPage = totalPage;
    loadData(page);
}
