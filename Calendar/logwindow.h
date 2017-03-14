#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QDialog>
#include <QString>
#include <QMessageBox>
#include "adduser.h"
#include "ui_adduser.h"
#include "sqldatebase.h"
#include "calendarwindow.h"


namespace Ui {
class LogWindow;
}

/*!
 * @brief Klasa okna Logowania użytkownika
 */

class LogWindow : public QDialog
{
    Q_OBJECT

public:

    /*!
        *   @brief Tworzy UI i oglne cechy okna
        * */

    explicit LogWindow(QWidget *parent = 0);

    /*!
       *   @brief Usuwa UI
       * */
    ~LogWindow();

    QString usernameText;/*!< Zmienna pomocnicza przechowująca nazwe/login użytkownika */
    QString passwordText;/*!< Zmienna pomocnicza przechowująca hasło użytkownika */
    QString sPasswordText;/*!< Zmienna pomocnicza przechowująca zaszyfrowane hasło użytkownika */
    QByteArray cypher;/*!< Zmienna pomocnicza wykorzystywana przy szyfrowaniu hasła użytkownika*/

private slots:

    /*!
        *   @brief Sygnał akceptowania wprowadzonych danych w celu logowania do aplikacji
        * */

    void on_buttonBox_accepted();
    /*!
        *   @brief Sygnał powodujący uruchomienie okna dodania użytkownika terminarza
        * */

    void on_commandLinkButton_clicked();

private:
    /*!
        *   Inicjalizacja obiektu ui klasy MainWindow w przestrzeni nazw Ui.
        * */
    Ui::LogWindow *ui;
};

#endif // LOGWINDOW_H
