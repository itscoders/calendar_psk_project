#ifndef CALENDARWINDOW_H
#define CALENDARWINDOW_H

#include <QDialog>
#include <QString>
#include "sqldatebase.h"
#include "inserteventwindow.h"
#include "insertmenueventwindow.h"
#include "logwindow.h"
#include "calculatedayofweek.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>


namespace Ui {
class CalendarWindow;
}

/*!
 * @brief Klasa okna z głównej obsługi Kalendarza/Terminarza
 */

class CalendarWindow : public QDialog
{
    Q_OBJECT

public:

    /*!
        *   @brief Tworzy UI i oglne cechy okna
        * */
    explicit CalendarWindow(QWidget *parent = 0);

    /*!
       *   @brief Usuwa UI
       * */
    ~CalendarWindow();



private slots:
    /*!
        *   @brief Sygnał dodawania eventu przez QCalendarWidget
        * */
    void on_calendarWidget_clicked(const QDate &date);
    /*!
        *   @brief Sygnał wylogowania z konta użytkownika
        * */
    void on_actionLog_out_triggered();
    /*!
        *   @brief Sygnał dodawania wydarzenia z menu okna obiektu Klasy CalendarWindow jak i Kontekstowego menu QTableView
        * */
    void on_actionAdd_Event_triggered();
    /*!
        *   @brief Sygnał usunięcia wszystkich wydarzeń z bazy danych zalogowanego użytkownika
        * */
    void on_actionAll_Event_triggered();
    /*!
        *   @brief Sygnał zakończenia pracy aplikacji
        * */
    void on_actionExit_triggered();
    /*!
        *   @brief Sygnał usunięcia
        * */
    void on_useDeleteEvent();



    void on_actionCalculate_Day_Of_Week_triggered();

    void on_actionSave_Events_To_File_triggered();

private:
    /*!
        *   Inicjalizacja obiektu ui klasy MainWindow w przestrzeni nazw Ui.
        * */
    Ui::CalendarWindow *ui;
    /*!
        *   Inicjalizacja obiektu sqlModel Klasy QSqlTableModel.
        * */
    QSqlTableModel *sqlModel;

};

#endif // CALENDARWINDOW_H
