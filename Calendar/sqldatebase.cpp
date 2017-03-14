#include "sqldatebase.h"

QString SqlDateBase::userlogin;
QString SqlDateBase::userpassword;

void SqlDateBase::connectDateBase()
{
    if(!QSqlDatabase::isDriverAvailable("QSQLITE"))
    {
        qFatal("Error: QSQLITE DRIVER NOT AVAILABLE");
    }

   QSqlDatabase dateBase = QSqlDatabase::addDatabase("QSQLITE");
   dateBase.setDatabaseName("calendarBase.db");

   if(!dateBase.open()){
      qFatal("Error: DATEBASE NOT OPEN");
   }
}

/*!
    *   Metoda createConnectionWithDateBaseByUserAccount po przyjęciu parametrów login i password
    *   wykonuje zapytanie do bazy czy użytkownik o podanych danych istnieje i czy są one poprawne.
    *
    *   Jeżeli zapytanie zgłosi bląd wtedy zwracana jest 'false' w pozostałym wypadku zwracane jest 'true'.
    *
    * */

bool SqlDateBase::createConnectionWithDateBaseByUserAccount(QString login, QString password)
{

    QSqlQuery query;

    if(!query.exec("SELECT * FROM users WHERE user_login = '"+login+"' AND user_password = '"+password+"'"))
    {

       return false;
    }else if(!query.first()){

        return false;
    }else{
        SqlDateBase::userlogin = login;
        SqlDateBase::userpassword = password;
        return true;
    }

}

/*!
    *   Metoda insertEventToDateBase dodaje wydarzenie o otrzymanych parametrach do bazy.
    *
    *   Wykonuje ona zapytanie do bazy mające na celu dodanie wpisu wydarzenia.
    *
    *   Jeżeli zapytanie zgłosi bląd wtedy zwracana jest 'false' w pozostałym wypadku zwracane jest 'true'.
    *
    * */

bool SqlDateBase::insertEventToDateBase(QString ename,QString elocation, QString einformation, QString edate)
{
    QSqlQuery query;

    if(query.exec("INSERT INTO `events` (`event_name`,`event_location`,`event_information`,`event_login_user`,`event_date`) VALUES('"+ename+"','"+elocation+"','"+einformation+"','"+userlogin+"','"+edate+"');"))
    {
        return true;
    }else if(query.first())
    {
        return true;
    }else
    {
        return false;
    }
}

/*!
    *   Metoda addNewUserToDataBase dodaje użytkownika do bazy
    *
    *   Wywołuje ona Metode isExistUserlogin, która sprawdza czy podany login nie występuje w bazie.
    *
    *   @see SqlDateBase::isExistUserlogin
    *
    *   Jeżeli zapytanie zgłosi bląd wtedy zwracana jest 'false' w pozostałym wypadku zwracane jest 'true'.
    *
    * */

bool SqlDateBase::addNewUserToDataBase(QString userl,QString usern, QString usersn, QString userpass)
{
    QSqlQuery query;
    if(!SqlDateBase::isExistUserlogin(userl))
    {
    query.exec("INSERT INTO `users`(`user_name`,`user_sname`,`user_login`,`user_password`) VALUES ('"+usern+"','"+usersn+"','"+userl+"','"+userpass+"')");
        return true;
    }else return false;
}


/*!
    *   Metoda deleteAllEventFromDateBase usuwa wszystkie wydarzeńa z bazy danego użytkownika
    *
    *   Wykonuje ona zapytanie do bazy mające na celu usunięcie wszystkich wydarzeń danego użytkownika
    *
    *   Jeżeli zapytanie zgłosi bląd wtedy zwracana jest 'false' w pozostałym wypadku zwracane jest 'true'.
    *
    * */

bool SqlDateBase::deleteAllEventFromDateBase()
{
    QSqlQuery query;
    if(query.exec("DELETE FROM `events` WHERE `event_login_user`= 't'"))
    {
        return true;
    }else if(query.first())
    {
        return true;
    }else
    {
        return false;
    }
}
/*!
*   Metoda isExistUserlogin sprawdza czy podany login nie występuje w bazie.
*
*
*   Jeżeli zapytanie zgłosi bląd wtedy zwracana jest wartość true lub fols po sprawdzeniu zapytania metodą first() z <QSqlQuery>.
*
* */

bool SqlDateBase::isExistUserlogin(QString userl)
{
    QSqlQuery query;

    query.exec("SELECT `user_login` FROM `users` WHERE `user_login` = '"+userl+"';");

    bool r = query.first();
    return r;

}
