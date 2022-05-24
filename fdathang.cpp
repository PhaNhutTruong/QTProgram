#include "fdathang.h"
#include "ui_fdathang.h"
#include <QSqlQuery>
#include <QMessageBox>

FDatHang::FDatHang(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FDatHang)
{
    ui->setupUi(this);
    loadData();
}

FDatHang::~FDatHang()
{
    delete ui;
}

void FDatHang::loadData()
{
    loadCBKH();
    loadCBSP();
    loadTabCTHD();
}

void FDatHang::loadCTHD()
{
    CustomModelOfCustomObject *model = new CustomModelOfCustomObject();
    tinhTongTien();
    model->setList(list);
    ui->tabCTDH->setModel(model);
    ui->tabCTDH->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabCTDH->show();
}

void FDatHang::loadCBKH()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT MaKH FROM KhachHang");
    query.exec();
    model->setQuery(query);
    ui->cbKhachHang->setModel(model);
}

void FDatHang::loadCBSP()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT MaSP FROM SanPham");
    query.exec();
    model->setQuery(query);
    ui->cbSanPham->setModel(model);
}

void FDatHang::loadTabCTHD(int page)
{
    int limit=5;
    int skip=(page-1)*limit;
    currentPage=page;
    getTotalPage();
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT tempp.ID,TenKH,tempp.Time,tempp.tong "
                  "FROM KhachHang,(SELECT ID,Time,IDKH,temp.tong FROM DonHang,"
                  "(SELECT MaDH,SUM(Tong)as tong FROM CTDonHang GROUP BY MaDH) as temp WHERE ID=temp.MaDH) as tempp "
                  "WHERE tempp.IDKH =MaKH ORDER BY tempp.ID DESC LIMIT "+QString::number(skip)+","+QString::number(limit));
    query.exec();
    model->setQuery(query);
    ui->tabDonHang->setModel(model);
    ui->tabDonHang->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabDonHang->verticalHeader()->hide();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Mã đơn"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Tên Khách Hàng"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Ngày mua"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Tổng tiền"));
    ui->tabDonHang->show();
    ui->lbPage->setText(QString::number(currentPage)+" / "+QString::number(totalPage));
}

void FDatHang::clearData()
{

}

void FDatHang::tinhTongTien()
{
    double tong=0;
    foreach (CTDonHang *x,list) {
       tong+=x->getTongTien().toDouble();
    }
    ui->lbTongTien->setText(QString::number(tong));
}

void FDatHang::luuHoaDon()
{
    QString time,status,MaKH;
    MaKH=ui->cbKhachHang->currentText();
    time=QDateTime::currentDateTime().toString(Qt::ISODate);
    status="Đã thanh toán";
        QSqlQuery query;
        query.prepare("INSERT INTO DonHang (Time,Status,IDKH) VALUES ('"+time+"','"+status+"','"+MaKH+"')");
        if(query.exec()){
            luuCTHoaDon();
        }
}

void FDatHang::luuCTHoaDon()
{
    foreach (CTDonHang *x,list) {
        QSqlQuery query;
        query.prepare("INSERT INTO CTDonHang (MaDH,IDSP,SL,Tong) "
                      "VALUES ((SELECT ID FROM DonHang ORDER BY ID DESC LIMIT 1),'"+x->getMaSP()+"','"+x->getSoLuong()+"','"+x->getTongTien()+"')");
        query.exec();
    }
    list.clear();
    loadCTHD();
    loadTabCTHD();
}

int FDatHang::getTotalPage()
{
    QSqlQuery query;
    query.prepare("SELECT Count(ID) FROM DonHang");
    if(query.exec()){
        while(query.next()){
           totalPage=ceil((query.value(0).toDouble())/5);
       }
        return totalPage;
    }
    return totalPage;
}

void FDatHang::on_cbKhachHang_currentTextChanged(const QString &arg1)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM KhachHang WHERE MaKH="+arg1);
    query.exec();
    if(query.exec()){
        while(query.next()){
            ui->lbTenKH->setText(query.value(1).toString());
            ui->lbSDT->setText(query.value(2).toString());
            ui->lbDiaChi->setText(query.value(3).toString());
        }
    }
}

void FDatHang::on_cbSanPham_currentTextChanged(const QString &arg1)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM SanPham WHERE MaSP="+arg1);
    query.exec();
    if(query.exec()){
        while(query.next()){
            ui->txtTenSP->setText(query.value(1).toString());
            ui->txtGia->setText(query.value(3).toString());
            ui->txtTong->setText(QString::number((query.value(3).toInt())*ui->sbSL->value()));
        }
    }
}

void FDatHang::on_sbSL_valueChanged(int arg1)
{

  ui->txtTong->setText(QString::number(ui->txtGia->text().toInt()*arg1));

}

void FDatHang::on_btnXacNhan_clicked()
{
    CTDonHang *item = new CTDonHang();
    item->setMaSP(ui->cbSanPham->currentText());
    item->setTenSP(ui->txtTenSP->text());
    item->setSoLuong(QString::number(ui->sbSL->value()));
    item->setTongTien(ui->txtTong->text());
    auto itr = std::find_if(list.begin(), list.end(), [=](CTDonHang* temp) { return temp->getMaSP() == item->getMaSP(); });
        if(itr == list.end()) {
            list.append(item);
        }
    foreach (CTDonHang *x,list) {
        if(x->getMaSP()==item->getMaSP()){
                x->setSoLuong(item->getSoLuong());
                x->setTongTien(item->getTongTien());
                break;
        }
    }
    loadCTHD();
}

void FDatHang::on_btnXoa_clicked()
{
    list.clear();
    loadCTHD();
}

void FDatHang::on_btnThanhToan_clicked()
{

    if(QMessageBox::question(this, "Thông báo", "Bạn có muốn thanh toán?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::No){
        return;
    }

    luuHoaDon();
    QMessageBox::critical(this,"Thông báo","Thanh toán thành công");
}

void FDatHang::on_btnFirst_clicked()
{
    int page = currentPage =1;
    loadTabCTHD(page);
}

void FDatHang::on_btnBack_clicked()
{
    int page=currentPage-1;
    if(page<1){
        currentPage=1;
        return;
    }
    loadTabCTHD(page);
}

void FDatHang::on_btnNext_clicked()
{
    int page=currentPage+1;
    if(page>totalPage){
        currentPage=totalPage;
        return;
    }
    loadTabCTHD(page);
}

void FDatHang::on_btnEnd_clicked()
{
    int page = currentPage = totalPage;
    loadTabCTHD(page);
}

void FDatHang::on_btnLoadCB_clicked()
{
    loadData();
    QMessageBox::critical(this,"Thông báo","Đã cập nhật dữ liệu");
}
