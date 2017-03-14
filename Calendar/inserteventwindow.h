#ifndef INSERTEVENTWINDOW_H
#define INSERTEVENTWINDOW_H

#include <QDialog>
#include "calendarwindow.h"
#include "sqldatebase.h"
#include <QMessageBox>



namespace Ui {
class InsertEventWindow;
}

/*!
 * @brief Klasa okna dodawania eventu bezpośrednio z okna głównego(Obiekt klasy CalendarWindow)
 */

class InsertEventWindow : public QDialog
{
    Q_OBJECT

public:

    /*!
        *   @brief Tworzy UI i oglne cechy okna
        * */
    explicit InsertEventWindow(QWidget *parent = 0);

    /*!
       *   @brief Usuwa UI
       * */
    ~InsertEventWindow();

    QString eventName;/*!< Zmienna pomocnicza przechowująca nazwe wydarzenia */
    QString eventLocation;/*!< Zmienna pomocnicza przechowująca lokacje wydarzenia */
    QString eventInfo;/*!< Zmienna pomocnicza przechowująca informacje wydarzenia */
    QString eventDate;/*!< Zmienna pomocnicza przechowująca date wydarzenia */


private slots:
    /*!
        *   @brief Sygnał akceptowania wprowadzonych danych wydarzenia i dodania ich do bazy wydarzeń
        * */
    void on_buttonInsertEventDialogBox_accepted();

private:
    /*!
        *   Inicjalizacja obiektu ui klasy MainWindow w przestrzeni nazw Ui.
        * */
    Ui::InsertEventWindow *ui;
};

#endif // INSERTEVENTWINDOW_H
