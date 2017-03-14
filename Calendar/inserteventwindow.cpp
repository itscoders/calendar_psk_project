#include "inserteventwindow.h"
#include "ui_inserteventwindow.h"


InsertEventWindow::InsertEventWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertEventWindow)
{
    ui->setupUi(this);
}

InsertEventWindow::~InsertEventWindow()
{
    delete ui;
}


/*!
    *   W środku sygnału znajdują się pola:
    *   @see InsertEventWindow::eventName
    *   @see InsertEventWindow::eventLocation
    *   @see InsertEventWindow::eventInfo
    *   @see InsertEventWindow::eventDate
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
void InsertEventWindow::on_buttonInsertEventDialogBox_accepted()
{
    eventName = ui->textEventNameBoxDialog->text();
    eventLocation = ui->textEventLocationBoxDialog->text();
    eventInfo = ui->textEventInfoBoxDialog->text();

    if(SqlDateBase::insertEventToDateBase(eventName, eventLocation, eventInfo, eventDate))
    {
       QMessageBox::information(this,"Information","ADD EVENT TO BASE -> SUCCESFUL");
    }else
    {
        QMessageBox::information(this,"Error","ADD EVENT TO BASE -> FALIURE");
    }

}
