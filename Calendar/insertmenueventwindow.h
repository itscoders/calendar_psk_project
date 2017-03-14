#ifndef INSERTMENUEVENTWINDOW_H
#define INSERTMENUEVENTWINDOW_H

#include <QDialog>
#include "sqldatebase.h"
#include <QMessageBox>



namespace Ui {
class InsertMenuEventWindow;
}

/*!
 * @brief Klasa okna dodawania eventu bezpośrednio z menu okna głównego(Obiekt klasy CalendarWindow)
 */

class InsertMenuEventWindow : public QDialog
{
    Q_OBJECT

public:

    /*!
        *   @brief Tworzy UI i oglne cechy okna
        * */
    explicit InsertMenuEventWindow(QWidget *parent = 0);

    /*!
       *   @brief Usuwa UI
       * */
    ~InsertMenuEventWindow();


    QString eventName;/*!< Zmienna pomocnicza przechowująca nazwe wydarzenia */
    QString eventLocation;/*!< Zmienna pomocnicza przechowująca lokacje wydarzenia */
    QString eventInfo;/*!< Zmienna pomocnicza przechowująca informacje wydarzenia */
    QString eventDate;/*!< Zmienna pomocnicza przechowująca date wydarzenia */

private slots:
    /*!
        *   @brief Sygnał akceptowania wprowadzonych danych wydarzenia i dodania ich do bazy wydarzeń
        * */
    void on_buttonBox_accepted();
    /*!
        *   @brief Sygnał pobierania zaznaczonej daty z QCalendarWidget i zapisania jej do zmiennej pomoczniczej eventDate.
        *   @see InsertMenuEventWindow::eventDate
        * */
    void on_calendarWidget_clicked(const QDate &date);

private:
    /*!
        *   Inicjalizacja obiektu ui klasy MainWindow w przestrzeni nazw Ui.
        * */
    Ui::InsertMenuEventWindow *ui;
};

#endif // INSERTMENUEVENTWINDOW_H
