#include "adduser.h"
#include "ui_adduser.h"


AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
    ui->adduserPassword->setEchoMode(QLineEdit::Password);
    ui->adduserConfirmpassword->setEchoMode(QLineEdit::Password);
}

AddUser::~AddUser()
{
    delete ui;
}
/*!
    *   W środku sygnału znajdują się pola:
    *   @see AddUser::adduserloginText
    *   @see AddUser::addusernameText
    *   @see AddUser::addusersurnameText
    *   @see AddUser::addpasswordText
    *   @see AddUser::addCypher
    *   @see AddUser::addpasswordCypher
    *
    *   Sygnał ten przy uruchomieniu sprawdza czy pola zostały wypełnione, jeżeli tak to wykonuje dalszę czyności.
    *
    *   W innym przypadku wysyła wiadomość o nie uzupełnionych polach.
    *
    *   Wprowadzone hasła w pola addpasswordText i addpasswordCypher sprawdza czy są sobie równe.
    *
    *   W przypadku poprawnego wprowadzenia hasła w oba pola:
    *
    *   Hasło zostaje zaszyfrowane a następnie zostaje wywołana Metoda addNewUserToDataBase z Klasy SqlDateBase, w celu dodania użytkownika.
    *
    *   @see SqlDateBase::addNewUserToDataBase
    *
    *   W przypadku poprawnie dodanego użytkownika zwracana jest do użytkownika informacja o treści:
    *
    *   "ADD SUCCEFUL TO BASE NEW USER ACCOUNT"
    *
    *   W przeciwnym wypadku użytkownik otrzymuje informacje o treści:
    *
    *   "ADD USER TO BASE FALIURE | USER LOGIN EXIST | PUTS OTHER USER LOGIN"
    *
    *   W przypadku różnych wartości w polach password i confirm password użytkownik otrzyma informacje o treści:
    *
    *   "ADD USER TO BASE FALIURE | PASSWORD INCORECT -> TRY AGAIN"
    *
    *   Ostatnim przypadkiem jest sytułacja gdy jakie kolwiek pole formularza zostaje puste, a użytkownik otrzymuje  informacje o treści:
    *
    *   "ANY FIELDS CAN'T BE EMPTY"
    *
    * */


void AddUser::on_buttonBox_accepted()
{
    adduserloginText = ui->adduserLogin->text();
    addusernameText = ui->adduserName->text();
    addusersurnameText = ui->adduserSurname->text();
    addpasswordText = ui->adduserPassword->text();

   if( adduserloginText != NULL && addusernameText != NULL && addusersurnameText != NULL && addpasswordText != NULL && ui->adduserConfirmpassword->text() != NULL)
   {
    if(addpasswordText == ui->adduserConfirmpassword->text())
    {
        addCypher = addpasswordText.toUtf8();
        addpasswordCypher = QString::fromUtf8(addCypher.toBase64());

        if(SqlDateBase::addNewUserToDataBase(adduserloginText,addusernameText,addusersurnameText,addpasswordCypher))
        {
            QString title = "Information";
            QString text = "ADD SUCCEFUL TO BASE NEW USER ACCOUNT";
            QMessageBox *msgBox = new QMessageBox;
            msgBox->setParent(0);
            msgBox->setWindowTitle(title);
            msgBox->setText(text);
            msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
            msgBox->show();
            this->close();
        }else
        {
            QString title = "Error";
            QString text = "ADD USER TO BASE FALIURE\n USER LOGIN EXIST \n PUTS OTHER USER LOGIN";
            QMessageBox *msgBox = new QMessageBox;
            msgBox->setParent(0);
            msgBox->setWindowTitle(title);
            msgBox->setText(text);
            msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
            msgBox->show();
        }

    }else
    {
        QString title = "Error";
        QString text = "ADD USER TO BASE FALIURE\nPASSWORD INCORECT -> TRY AGAIN";
        QMessageBox *msgBox = new QMessageBox;
        msgBox->resize(145,45);
        msgBox->setParent(0);
        msgBox->setWindowTitle(title);
        msgBox->setText(text);
        msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
        msgBox->show();

    }
   }else
   {
       QString title = "Error";
       QString text = "ANY FIELDS CAN'T BE EMPTY";
       QMessageBox *msgBox = new QMessageBox;
       msgBox->resize(145,45);
       msgBox->setParent(0);
       msgBox->setWindowTitle(title);
       msgBox->setText(text);
       msgBox->show();
   }
}
