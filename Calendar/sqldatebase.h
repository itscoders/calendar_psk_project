#ifndef SQLDATEBASE_H
#define SQLDATEBASE_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>

/*!
 * @brief Klasa do zarządzania komunikacją z bazą danych
 */


class SqlDateBase : public QObject
{
    Q_OBJECT

public:

    static QString userpassword;/*!< Zmienna pomocnicza przechowująca hasło użytkownika */
    static QString userlogin;/*!< Zmienna pomocnicza przechowująca nazwe/login użytkownika */


    /*!
        *   @brief Konstruktor Klasy SqlDateBase
        * */

    SqlDateBase();

    /*!
       *    @brief Metoda tworząca połączenie z istniejącą bazą danych
       * */

    static void connectDateBase();
    /*!
       *    @brief Metoda tworząca połączenie konta użytkownika z baządanych
       *    @param login
       *    @param password
       *    @return true/false
       * */
    static bool createConnectionWithDateBaseByUserAccount(QString login, QString password);
    /*!
       *    @brief Metoda dodająca event do bazy
       *    @param ename
       *    @param elocation
       *    @param einformation
       *    @param edate
       *    @return true/false
       * */
    static bool insertEventToDateBase(QString ename, QString elocation, QString einformation, QString edate);

    /*!
       *    @brief Metoda dodająca nowego użytkownika do bazy
       *    @param userl
       *    @param usern
       *    @param usersn
       *    @param userpass
       *    @return true/false
       * */

    static bool addNewUserToDataBase(QString userl,QString usern, QString usersn, QString userpass);
    /*!
       *    @brief Metoda sprawdzająca czy użytkownik o podanym loginie jest już w bazie
       *    @param userl
       *    @return true/false
       * */
    static bool isExistUserlogin(QString userl);
    /*!
       *    @brief Metoda usuwająca wszystkie wydarzenia danego użytkownika
       * */
    static bool deleteAllEventFromDateBase();
    /*!
       *    @brief Metoda dodająca event do bazy
       *    @param *ename
       *    @param *elocation
       *    @param *einformation
       *    @param *edate
       *    @return true/false
       * */
    static void infoAboutEvent(QString *ename,QString *elocation, QString *einformation, QString *edate);
};

#endif // SQLDATEBASE_H
