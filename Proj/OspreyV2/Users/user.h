#ifndef USER_H
#define USER_H

#include <QString>



class User
{
private:
    User();
    static bool loggedIn;
    static int userID;
    static QString userName;

public:
    static void login(int ID, const QString &user){
        loggedIn = true;
        userID = ID;
        userName = user;
    }

    static void logout(){
        loggedIn = false;
        userName = "Anon";
        userID = 1;
    }

    static int getUserID(){
        return userID;
    }

    static bool& isLoggedIn(){
        return loggedIn;
    }

    static QString& getUserName(){
        return userName;
    }



};

#endif // USER_H
