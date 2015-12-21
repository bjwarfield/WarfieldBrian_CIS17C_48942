#include "dbconnect.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <Users/user.h>


const QString DBConnect::HOST = "localhost";
const QString DBConnect::DBNAME = "48941";
const QString DBConnect::USER = "root";
const QString DBConnect::PASS = "";

DBConnect::Connection DBConnect::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(HOST);
    db.setDatabaseName(DBNAME);
    db.setUserName(USER);
    db.setPassword(PASS);

    Connection connection;
    connection.db = db;
    if(!db.open()){
        qDebug()<< "Database connection error\n";
        connection.connected = false;
        return connection;
    }
    connection.connected = true;
    return connection;
}

void DBConnect::closeConnection(DBConnect::Connection &connection)
{
    connection.db.close();
    connection.connected = false;
}

int DBConnect::checkEmail(const QString &email)
{
    Connection conn = createConnection();
    if(!conn.connected){
        qDebug() << "Database connection failed\n";
        return -1;
    }

    int numRows = 0;
    QSqlQuery query;
    query.prepare("SELECT count(*) FROM `osprey_entity_player` WHERE `email` = :email;");

    query.bindValue(":email", email.trimmed().toLower());
    query.exec();

    while(query.next()){
        numRows = query.value(0).toInt();
    }

    closeConnection(conn);

    return numRows;
}

int DBConnect::doRegister(const QString &fName, const QString &lName,
                           const QString &uName, const QString &email,
                           const QString &pass)
{
    Connection conn = createConnection();
    if(!conn.connected){
        qDebug() << "Database connection failed\n";
        return 0;

    }

    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(pass.trimmed().toUtf8(), pass.size());
    QSqlQuery query;

    query.prepare("INSERT INTO "
                   "`osprey_entity_player` (`first_name`, `last_name`, "
                   "`email`, `password`,`user_name`, date_created) "
                   "VALUES(:fname, :lname, :email, :pass, :uname, now());");

    query.bindValue(":fname", fName.trimmed());
    query.bindValue(":lname", lName.trimmed());
    query.bindValue(":email", email.trimmed().toLower());
    query.bindValue(":pass", hash.result().toHex());
    query.bindValue(":uname", uName.trimmed());

    if(!query.exec()){
        qDebug() << "Failed to insert into Database\n";
        closeConnection(conn);
        return 0;
    }
    int numRows = query.numRowsAffected();

    closeConnection(conn);
    return numRows;
}

bool DBConnect::login(const QString &email, const QString &pass)
{
    Connection conn = createConnection();
    if(!conn.connected){
        qDebug() << "Database connection failed\n";
        return false;
    }

    int id = 1;
    QString userName = "";
    int numRows = 0;

    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(pass.trimmed().toUtf8(), pass.size());
    QSqlQuery query;

    query.prepare("SELECT `player_id`, `user_name` FROM `osprey_entity_player"
                   "` WHERE `email` = :email AND `password` =  :pass;");

    query.bindValue(":email", email.trimmed().toLower());
    query.bindValue(":pass", hash.result().toHex());

    if(!query.exec()){
        qDebug() << "Failed to query Database\n";
        closeConnection(conn);
        return false;
    }

    while(query.next()){
        numRows++;
        id = query.value(0).toInt();
        userName = query.value(1).toString();
    }

    closeConnection(conn);

    if(numRows == 1){
        User::login(id, userName);
        return true;
    }
    return false;
}

void DBConnect::submitScore(int userID, int score, int kills, int deaths)
{
    Connection conn = createConnection();
    if(!conn.connected){
        qDebug() << "Database connection failed\n";
        return ;
    }

    QSqlQuery query;

    query.prepare("INSERT INTO `osprey_entity_score` (score, kills, deaths)"
                   " VALUES (:score, :kills, :deats);");
    query.bindValue(":score", score);
    query.bindValue(":kills", kills);
    query.bindValue(":deaths", deaths);

    if(!query.exec()){
        qDebug() << "Failed to insert score";
        closeConnection(conn);
        return;
    }
    int scoreID = query.lastInsertId().toInt();

    query.prepare("INSERT INTO `osprey_xref_player_score` (player_id, score_id) "
                  "VALUES (:uid,:sid)");
    query.bindValue(":uid", userID);
    query.bindValue(":sid", scoreID);
    if(!query.exec()){
        qDebug() << "Failed to xref score to player";
        closeConnection(conn);
        return;
    }


    closeConnection(conn);

}



