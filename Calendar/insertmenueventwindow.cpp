#include "insertmenueventwindow.h"
#include "ui_insertmenueventwindow.h"

InsertMenuEventWindow::InsertMenuEventWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertMenuEventWindow)
{
    ui->setupUi(this);
}

InsertMenuEventWindow::~InsertMenuEventWindow()
{
    delete ui;
}

/*!
    *   W środku sygnału znajdują się pola:
    *   @see InsertMenuEventWindow::eventName
    *   @see InsertMenuEventWindow::eventLocation
    *   @see InsertMenuEventWindow::eventInfo
    *   @see InsertMenuEventWindow::eventDate
    *
    *   Sygnał ten wywołuje Metode insertEventToDateBase z Klasy SqlDateBase
    *
    *   @see SqlDateBase::insertEventToDateBase
    *
    *   W przypadku dodania wydarzenia do bazy użytkownik otrzymuje informację o treści:
    *
    *   "ADD EVENT TO BASE -> SUCCESFUL"
    *
    *   W przypadku błędu dodania użytkownik otrzymuje informację o teści:
    *
    *   "ADD EVENT TO BASE -> FALIURE"
    *
    * */
void InsertMenuEventWindow::on_buttonBox_accepted()
{
    eventName = ui->textEventNameBoxMenuDialog->text();
    eventLocation = ui->textEventLocationBoxMenuDialog->text();
    eventInfo = ui->textEventInfoBoxMenuDialog->text();

    if(SqlDateBase::insertEventToDateBase(eventName, eventLocation, eventInfo, eventDate))
    {
       QMessageBox::information(this,"Information","ADD EVENT TO BASE -> SUCCESFUL");
    }else
    {
        QMessageBox::information(this,"Error","ADD EVENT TO BASE -> FALIURE");
    }
}

void InsertMenuEventWindow::on_calendarWidget_clicked(const QDate &date)
{
    eventDate = date.toString();
}
