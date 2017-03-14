#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>
#include <QMessageBox>
#include "sqldatebase.h"



namespace Ui {
class AddUser;
}

/*!
 * @brief Klasa okna Dodawania użytkownika Terminarza/Kalendarza
 */

class AddUser : public QDialog
{
    Q_OBJECT

public:

    /*!
        *   @brief Tworzy UI i oglne cechy okna
        * */
    explicit AddUser(QWidget *parent = 0);

    /*!
        *   @brief Usuwa UI
        * */
    ~AddUser();

    QString adduserloginText;/*!< Zmienna pomocnicza przechowująca logi użytkownika */
    QString addusernameText;/*!< Zmienna pomocnicza przechowująca imię użytkownika */
    QString addusersurnameText;/*!< Zmienna pomocnicza przechowująca nazwisko użytkownika */
    QString addpasswordText;/*!< Zmienna pomocnicza przechowująca hasło użytkownika */
    QString addpasswordCypher;/*!< Zmienna pomocnicza przechowująca zaszyfrowane  hasło użytkownika */
    QByteArray addCypher;/*!< Zmienna pomocnicza użyta do szyfrowania hasła użytkownika */

private slots:
    /*!
        *   @brief Sygnał akceptowania wprowadzonych danych użytkownika w celu jego utworzenia w bazie
        * */

    void on_buttonBox_accepted();

private:
    /*!
        *   Inicjalizacja obiektu ui klasy MainWindow w przestrzeni nazw Ui.
        * */
    Ui::AddUser *ui;
};

#endif // ADDUSER_H
