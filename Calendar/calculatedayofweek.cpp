#include "calculatedayofweek.h"
#include "ui_calculatedayofweek.h"


CalculateDayOfWeek::CalculateDayOfWeek(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalculateDayOfWeek)
{
    ui->setupUi(this);
}

CalculateDayOfWeek::~CalculateDayOfWeek()
{
    delete ui;
}

int CalculateDayOfWeek::intercalaryYear(int year)
{
    return ((year % 4 == 0  && year % 100 != 0) || year % 400 == 0);
}

/*!
   *   W środku metody fooDayWeek znajdują się pola pomocznicze:
   *
   *    typu int:
   *
   *         int dayofYear
   *
   *          int v_y, v_c, v_g
   *
   *            int result
   *
   *    Oraz tablica numberOfDaysTable z Klasy CalculateDayOfWeek
   * */

int CalculateDayOfWeek::fooDayWeek(int day, int month, int year)
{
    int dayofYear;
    int v_y, v_c, v_g;
    int result;

    dayofYear = day + numberOfDaysTable[month-1];

        if ((month > 2) && (intercalaryYear(year)) == 1) dayofYear++;

v_y = (year-1) % 100;
v_c = (year - 1) - v_y;
v_g = v_y + (v_y / 4);
result = (((((v_c / 100) % 4) * 5) + v_g) % 7);
result += dayofYear- 1;
result %= 7;

return result;
}



/*!
    *  Sygnał on_buttonBox_accepted() pobiera dane z pól formularza i przekazuje do pól Obiektu klasy:
    *   day
    *   month
    *   year
    *   @see day
    *   @see month
    *   @see year
    *
    *   Wprowadzone przez użytkownika dane są sprawdzane pod względem poprawności
    *
    *   Jeżeli data jest poprawna obliczny jest szukany dzień, a następnie użytkownik otrzymuje informację o Nazwie wyznaczonego Dnia Tygodnia.
    *
    *   Jeżeli jest nie poprawna użytkownik otrzymuje informację o treści:
    *
    *   "INVALID DATE TRY AGAIN".
    * */

void CalculateDayOfWeek::on_buttonBox_accepted()
{
    QMessageBox *msgBox = new QMessageBox;
    QString title;
    QString text;

    day = ui->textDayEdit->text();
    month = ui->textMonthEdit->text();
    year = ui ->textYearEdit->text();

    int d = day.toInt();
    int m = month.toInt();
    int y = year.toInt();


    if(QDate::isValid(y,m,d))
    {
        int index = fooDayWeek(d,m,y);
        title = "RESULT";
        text =  daysOfWeek[index];
        msgBox->setParent(0);
        msgBox->setWindowTitle(title);
        msgBox->setText(text);
        msgBox->show();
    }else
    {
        title = "Error";
        text =  "INVALID DATE TRY AGAIN";
        msgBox->setParent(0);
        msgBox->setWindowTitle(title);
        msgBox->setText(text);
        msgBox->show();
    }
}
