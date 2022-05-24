#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql>
#include <QSqlDatabase>


class Connection
{
public:
    Connection();
public:
    QSqlDatabase db ;
    bool openCon(){
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("127.0.0.1");
        db.setPort(3307);
        db.setUserName("root");
        db.setPassword("");
        db.setDatabaseName("CuaHang");
        if(db.open()){
            return true;
        }else{
            return false;
        }
    }
    void closeCon(){
        db.close();
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    }
};

#endif // CONNECTION_H
