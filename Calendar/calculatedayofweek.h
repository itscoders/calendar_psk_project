#ifndef CALCULATEDAYOFWEEK_H
#define CALCULATEDAYOFWEEK_H

#include <QDialog>
#include "QMessageBox"
#include "QDate"

namespace Ui {
class CalculateDayOfWeek;
}

/*!
 * @brief Klasa okna Oblicznia Dnia Tygodnia
 */

class CalculateDayOfWeek : public QDialog
{
    Q_OBJECT

public:
    /*!
        *   @brief Tworzy UI i oglne cechy okna
        * */

    explicit CalculateDayOfWeek(QWidget *parent = 0);

    /*!
       *   @brief Usuwa UI
       * */
    ~CalculateDayOfWeek();

    int numberOfDaysTable[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334}; /*!< Tablica typu int zawierający ilość dni po których zaczyna się dany miesiąc*/
    QString daysOfWeek[7]= {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};/*!< Tablica QString 7-elementowa zawierająca nazwy dni tygodnia */

    /*!
       *    @brief Metoda sprawdzająca czy podany rok w parametrze jest przestępny
       *    @param year
       *    @return ((year % 4 == 0  && year % 100 != 0) || year % 400 == 0)
       * */
    int intercalaryYear(int year);

    /*!
       *    @brief Metoda wyliczająca dzień tygodnia na podstawie podanych wartości dzień, miesiąc i rok
       *    @param year
       *    @param month
       *    @param year
       *    @return result -> wyliczony dzień tygodnia
       * */

    int fooDayWeek(int day, int month, int year);
    QString day;/*!< Zmienna pomocnicza przechowująca dzień podany przez użytkownika */
    QString month;/*!< Zmienna pomocnicza przechowująca miesiąc przez użytkownika */
    QString year;/*!< Zmienna pomocnicza przechowująca rok podany przez użytkownika */

private slots:

    /*!
        *   @brief Sygnał akceptowania wprowadzonych danych daty i wywołania pozostałych metod klasy fooDayWeek
        *   @see CalculateDayOfWeek::fooDayWeek
        * */
    void on_buttonBox_accepted();

private:
    /*!
        *   Inicjalizacja obiektu ui klasy MainWindow w przestrzeni nazw Ui.
        * */
    Ui::CalculateDayOfWeek *ui;
};

#endif // CALCULATEDAYOFWEEK_H
