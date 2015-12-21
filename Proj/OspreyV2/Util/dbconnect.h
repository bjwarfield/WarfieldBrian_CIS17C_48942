#ifndef DBCONNECT_H
#define DBCONNECT_H
#include <QDebug>
#include <QSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>

class DBConnect
{
    static const QString HOST ;
    static const QString DBNAME;
    static const QString USER;
    static const QString PASS;

    struct Connection{
        QSqlDatabase db;
        bool connected;
    };

public:
    static Connection createConnection();
    static void closeConnection(Connection &connection);
    static int checkEmail(const QString &email);
    static int doRegister(const QString &fName, const QString &lName, const QString &uName,
                          const QString &email, const QString &pass);
    static bool login(const QString &email, const QString &pass);
    static void submitScore(int userID, int score, int kills, int deaths);
    //TODO getPlayerStats
private:
    DBConnect();

};

#endif // DBCONNECT_H
