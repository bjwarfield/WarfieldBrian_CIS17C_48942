#ifndef REGEX_H
#define REGEX_H

#include <QRegExp>




/**
* valid name alpha 1-20 characters long
* @param name String value to check
* @return true if regex patter match
*/
static bool matchName(const QString &name){
    return QRegExp("^[-a-zA-Z ]{1,20}$").exactMatch(name);
}

/**
* valid email (name@site.domain)
* @param email string value to check against
* @return true if regex patter match
*/
static bool matchEmail(const QString &email){
    return QRegExp("^[a-zA-Z0-9_.-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$").exactMatch(email);
}

/**
* match Password must be 6-20 characters long, AlphaNumeric or @ # $ %
* @param password string value to check against
* @return true if regex patter match
*/
static bool matchPass(const QString &pass){
    return QRegExp("^([a-zA-Z0-9@#$%]{6,20})$").exactMatch(pass);
}


/**
* match username must be 3-20 characters long, AlphaNumeric or @ # $ %
* @param handle string value to check against
* @return true if regex patter match
*/
static bool matchUser(const QString &pass){
    return QRegExp("^([ a-zA-Z0-9@#$%]{3,20})$").exactMatch(pass);
}




#endif // REGEX_H
