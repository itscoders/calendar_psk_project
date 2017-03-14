#include "logwindow.h"
#include "ui_logwindow.h"




LogWindow::LogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogWindow)
{

    ui->setupUi(this);

    Qt::WindowFlags windowFlags = (Qt::CustomizeWindowHint);
    windowFlags |= Qt::WindowCloseButtonHint;
    this->setWindowFlags( windowFlags );

    ui->textPasswordBox->setEchoMode(QLineEdit::Password);
}


LogWindow::~LogWindow()
{
    delete ui;
}
/*!
    *   W środku sygnału znajdują się pola:
    *   @see LogWindow::usernameText
    *   @see LogWindow::sPasswordText
    *   @see LogWindow::cypher
    *   @see LogWindow::passwordText
    *
    *   Sygnał pobiera dane wprowadzone do okna logowania.
    *   Uruchamia metode z Klasy SqlDateBase:
    *   createConnectionWithDateBaseByUserAccount
    *
    *   @see SqlDateBase::createConnectionWithDateBaseByUserAccount
    *
    *   Metoda ta sprawdza czy w bazie istnieje użytkownik o podanych danych:
    *
    *   -zwraca gdy istnieje 'true' w przeciwnym 'false'.
    *
    * TRUE
    *
    *   Jeżeli użytkownik znajduje się w bazie, zostaje zamknięte okno logowania.
    *   Następnie zostaje utworzony obiekt Klasy CalendarWindow.
    *
    *FALSE
    *
    *   Jeżeli niema użytkownika w bazie, zostaje wysłana do użytkownika informacja o błędzie:
    *
    * Treść:
    *
    *   "INCORRECT USERNAME OR PASSWORD"
    * */
void LogWindow::on_buttonBox_accepted()
{
    usernameText = ui->textUsernameBox->text();
    passwordText = ui->textPasswordBox->text();
    cypher = passwordText.toUtf8();
    sPasswordText = QString::fromUtf8(cypher.toBase64());

    if(SqlDateBase::createConnectionWithDateBaseByUserAccount(usernameText,sPasswordText))
    {
        CalendarWindow w;
        w.exec();
        this->close();

    }else{
        QString title = "Error";
        QString text = "INCORRECT USERNAME OR PASSWORD";
        QMessageBox *msgBox = new QMessageBox;
        msgBox->setParent(0);
        msgBox->setWindowTitle(title);
        msgBox->setText(text);
        msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
        msgBox->show();
        this->show();
    }
}


/*!
    *   Utworzenie Obiektu Klasy AddUser i jego wywołanie.
    * */
void LogWindow::on_commandLinkButton_clicked()
{
    AddUser au;
    au.exec();
}
