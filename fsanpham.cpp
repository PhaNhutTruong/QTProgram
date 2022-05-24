#include "fsanpham.h"
#include "ui_fsanpham.h"
#include "QMessageBox"

FSanPham::FSanPham(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FSanPham)
{
    ui->setupUi(this);
    loadData();
}

FSanPham::~FSanPham()
{
    delete ui;
}

void FSanPham::loadData(int page){
    int limit=5;
    int skip=(page-1)*limit;
    currentPage=page;
    getTotalPage();
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM SanPham ORDER BY MaSP DESC LIMIT "+QString::number(skip)+","+QString::number(limit));
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Mã sản phẩm"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Tên sản phẩm"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Số lượng"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Giá"));
    ui->tabSanPham->setModel(model);
    ui->tabSanPham->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabSanPham->verticalHeader()->hide();
    ui->tabSanPham->show();
    ui->lbPage->setText(QString::number(currentPage)+" / "+QString::number(totalPage));
    clearData();
}

void FSanPham::clearData(){
    ui->txtTenSP->clear();
    ui->txtGia->clear();
    ui->txtSL->clear();
    ui->txtMaSP->clear();
    ui->btnSua->setEnabled(false);
    ui->btnXoa->setEnabled(false);
}

int FSanPham::getTotalPage()
{
    QSqlQuery query;
    query.prepare("SELECT Count(MaSP) FROM SanPham");
    if(query.exec()){
        while(query.next()){
           totalPage=ceil((query.value(0).toDouble())/5);
       }
        return totalPage;
    }
    return totalPage;
}

void FSanPham::on_btnLT_clicked()
{
    loadData();
}

void FSanPham::on_btnThem_clicked()
{
    if(QMessageBox::question(this, "Thông báo", "Bạn có muốn thêm?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::No){
        return;
    }
    QString tenSP,soLuong,gia;
    bool ok=false;

        tenSP=ui->txtTenSP->text();
        soLuong=ui->txtSL->text();
        soLuong.toInt(&ok,10);
        if(tenSP.isEmpty()){
            QMessageBox::critical(this,"Thông báo","Tên sản phẩm không được bỏ trống");
            return;
        }
        if(ok==false){
            QMessageBox::critical(this,"Thông báo","Số lượng không hợp lệ !");
            return;
        }
        gia=ui->txtGia->text();
        gia.toDouble(&ok);
        if(ok==false){
            QMessageBox::critical(this,"Thông báo","Giá không hợp lệ !");
            return;
        }
        QSqlQuery query;
        query.prepare("INSERT INTO SanPham (TenSP,SL,Gia) VALUES ('"+tenSP+"','"+soLuong+"','"+gia+"')");
        if(query.exec()){
            QMessageBox::critical(this,"Thông báo","Thêm thành công");
            loadData();
        }
}

void FSanPham::on_btnXoa_clicked()
{
    if(QMessageBox::question(this, "Thông báo", "Bạn có muốn xóa ?\n Sản Phẩm : "+ ui->txtTenSP->text(),QMessageBox::Yes|QMessageBox::No)==QMessageBox::No){
        return;
    }
    QString id = ui->txtMaSP->text();
        QSqlQuery query;
        query.prepare("DELETE FROM SanPham WHERE MaSP="+id);
        if(query.exec()){
           loadData();
         }
}

void FSanPham::on_btnSua_clicked()
{
    if(QMessageBox::question(this, "Thông báo", "Bạn có muốn sửa? \nSản phâm có id: "+ui->txtMaSP->text(),QMessageBox::Yes|QMessageBox::No)==QMessageBox::No){
        return;
    }
    QString tenSP,soLuong,gia,id;
    bool ok=false;
        id=ui->txtMaSP->text();
        tenSP=ui->txtTenSP->text();
        soLuong=ui->txtSL->text();
        soLuong.toInt(&ok,10);
        if(ok==false){
            QMessageBox::critical(this,"Thông báo","Số lượng không hợp lệ !");
            return;
        }
        gia=ui->txtGia->text();
        gia.toDouble(&ok);
        if(ok==false){
            QMessageBox::critical(this,"Thông báo","Giá không hợp lệ !");
            return;
        }
        QSqlQuery query;
        query.prepare("UPDATE SanPham SET TenSP='"+tenSP+"',SL='"+soLuong+"',Gia='"+gia+"' WHERE MaSP="+id);
        if(query.exec()){
            QMessageBox::critical(this,"Thông báo","Sửa thành công");
            loadData();
        }
}

void FSanPham::on_tabSanPham_clicked(const QModelIndex &index)
{
    QString id = index.sibling(index.row(), 0).data().toString();
        QSqlQuery query;
        query.prepare("SELECT * FROM SanPham WHERE MaSP="+id);
        if(query.exec()){
            while(query.next()){
                ui->txtMaSP->setText(query.value(0).toString());
                ui->txtTenSP->setText(query.value(1).toString());
                ui->txtSL->setText(query.value(2).toString());
                ui->txtGia->setText(query.value(3).toString());
            }
            ui->btnSua->setEnabled(true);
            ui->btnXoa->setEnabled(true);
         }
}

void FSanPham::on_btnFirst_clicked()
{
    int page = currentPage =1;
    loadData(page);
}

void FSanPham::on_btnBack_clicked()
{
    int page=currentPage-1;
    if(page<1){
        currentPage=1;
        return;
    }
    loadData(page);
}

void FSanPham::on_btnNext_clicked()
{
    int page=currentPage+1;
    if(page>totalPage){
        currentPage=totalPage;
        return;
    }
    loadData(page);
}

void FSanPham::on_btnEnd_clicked()
{
    int page = currentPage = totalPage;
    loadData(page);
}
