#include "calendarwindow.h"
#include "ui_calendarwindow.h"

/*!
    *
    * */

CalendarWindow::CalendarWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalendarWindow)
{
    ui->setupUi(this);

    Qt::WindowFlags windowFlags = (Qt::CustomizeWindowHint);
    windowFlags |= Qt::WindowCloseButtonHint;
    windowFlags |= Qt::WindowMinMaxButtonsHint;
    this->setWindowFlags( windowFlags );

    ui->userLabelView->setText(SqlDateBase::userlogin);

    sqlModel= new QSqlTableModel(this);
    sqlModel->setTable("events");
    ui->tableBaseEventView->setModel(sqlModel);
    ui->tableBaseEventView->hideColumn(0);
    ui->tableBaseEventView->hideColumn(4);
    sqlModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    sqlModel->setHeaderData(2, Qt::Horizontal, tr("Location"));
    sqlModel->setHeaderData(3, Qt::Horizontal, tr("Info"));
    sqlModel->setHeaderData(5, Qt::Horizontal, tr("Date"));
    sqlModel->setFilter("event_login_user= '"+SqlDateBase::userlogin+"';");//WHERE event_user_login = userlogin;
    sqlModel->select();


    ui->tableBaseEventView->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction* addAction = new QAction("Add Event");
    QAction* deleteAction = new QAction("Delete Event");
    QAction* allDeleteAction = new QAction("Delete All Event");
    ui->tableBaseEventView->connect(addAction, SIGNAL(triggered()), this, SLOT(on_actionAdd_Event_triggered()));
    ui->tableBaseEventView->connect(deleteAction, SIGNAL(triggered()), this, SLOT(on_useDeleteEvent()));
    ui->tableBaseEventView->connect(allDeleteAction, SIGNAL(triggered()), this, SLOT(on_actionAll_Event_triggered()));
    ui->tableBaseEventView->addAction(addAction);
    ui->tableBaseEventView->addAction( deleteAction);
    ui->tableBaseEventView->addAction( allDeleteAction);
}


CalendarWindow::~CalendarWindow()
{
    delete ui;
}


/*!
    *   Sygnał ten Tworzy obiekt Klasy InsertEventWindow i wywołuje okno utworzonego objektu, przekazując do niego date wybraną przez użytkownika do utworzenia wydarzenia.
    * */

void CalendarWindow::on_calendarWidget_clicked(const QDate &date)
{

    InsertEventWindow ie;
    ie.eventDate = date.toString();
    ie.exec();
    sqlModel->select();
}

/*!
    *   @brief Sygnał powoduje zamknięcie obecnego okna Klasy CalendarWindow i utworzenie obiektu Klasy LogWindow, w celu umożliwienia przelogowania się na innego użytkownika.
    * */

void CalendarWindow::on_actionLog_out_triggered()
{
    this->close();
    LogWindow lw;
    lw.exec();
}


/*!
    *   @brief Sygnał powoduje utworzenie obiektu Klasy InsertMenuEventWindow w celu umożliwienia dodania przez użytkownika wydarzenia do bazy.
    * */

void CalendarWindow::on_actionAdd_Event_triggered()
{
    InsertMenuEventWindow ime;
    ime.exec();
    sqlModel->select();
}

/*!
    *   @brief Sygnał z kontekstowego menu QTableView oraz menu głównego okna.
    *
    *   Pozwalający usunąć wszystkie wydarzenia jeżeli takowe istnieją.
    *
    *   W przypadku, gdy nie istnieją użytkownik dostaję informację o treści:
    *
    *  "DELETE FROM BASE -> FAILURE\nEMPTY BASE"
    *
    *   W pozostałym przypadku podejmowania jest próba usunięcia wpisóW z bazy:
    *
    *   Jeżeli jest udana użytkownik otrzymuje informację o treści:
    *
    *   "DELETE FROM BASE -> SUCCEFUL"
    *
    *   Usuwane wydarzenia są przez metode deleteAllEventFromDateBase Klasy SqlDateBase
    *   @see SqlDateBase::deleteAllEventFromDateBase
    *
    *   W przeciwnym wypadku użytkownik otrzymuje informację:
    *
    *   "DELETE FROM BESE -> FAILURE"
    *
    * */


void CalendarWindow::on_actionAll_Event_triggered()
{
    if(sqlModel->rowCount() == 0){
        QString title = "Error";
        QString text = "DELETE FROM BASE -> FAILURE\nEMPTY BASE";
        QMessageBox *msgBox = new QMessageBox;
        msgBox->setParent(0);
        msgBox->setWindowTitle(title);
        msgBox->setText(text);
        msgBox->show();
    }else
    {

    if(SqlDateBase::deleteAllEventFromDateBase())
   {
    QString title = "DELETE SIGNAL";
    QString text = "DELETE FROM BASE -> SUCCEFUL";
    QMessageBox *msgBox = new QMessageBox;
    msgBox->setParent(0);
    msgBox->setWindowTitle(title);
    msgBox->setText(text);
    msgBox->show();
    sqlModel->select();
   }else
   {
       QString title = "Error";
       QString text = "DELETE FROM BESE -> FAILURE";
       QMessageBox *msgBox = new QMessageBox;
       msgBox->setParent(0);
       msgBox->setWindowTitle(title);
       msgBox->setText(text);
       msgBox->show();
   }
    }
}



void CalendarWindow::on_actionExit_triggered()
{
    this->close();
}

/*!
    *   @brief Sygnał z kontekstowego menu QTableView .
    *
    *   Pozwalający usunąć wydarzenia zaznaczone w QTableView jeżeli takowe istnieją.
    *
    *   W przypadku, gdy nie istnieją użytkownik dostaję informację o treści:
    *
    *  "DELETE FROM BASE -> FAILURE\nEMPTY BASE"
    *
    *   W pozostałym przypadku podejmowania jest próba usunięcia wpisóW z bazy:
    *
    *   Jeżeli jest udana użytkownik otrzymuje informację o treści:
    *
    *   "DELETE FROM BASE -> SUCCEFUL"
    *
    *   Usuwane wydarzenia są przez metode deleteAllEventFromDateBase Klasy SqlDateBase
    *   @see SqlDateBase::deleteAllEventFromDateBase
    *
    *   W przeciwnym wypadku użytkownik otrzymuje informację:
    *
    *   "DELETE FROM BESE -> FAILURE"
    *
    * */

void CalendarWindow::on_useDeleteEvent()
{
    if(sqlModel->rowCount() == 0){
        QString title = "Error";
        QString text = "DELETE FROM BESE -> FAILURE\nEMPTY BASE";
        QMessageBox *msgBox = new QMessageBox;
        msgBox->setParent(0);
        msgBox->setWindowTitle(title);
        msgBox->setText(text);
        msgBox->show();
    }else
    {
    sqlModel->removeRow(ui->tableBaseEventView->currentIndex().row());
    sqlModel->select();
    }
}


void CalendarWindow::on_actionCalculate_Day_Of_Week_triggered()
{
    CalculateDayOfWeek cdow;
    cdow.exec();
}

void CalendarWindow::on_actionSave_Events_To_File_triggered()
{QString name = QFileDialog::getSaveFileName(this, "Save Your Events", QDir::currentPath(), "Plain Text(*.txt);;");


    if (name.isEmpty()) return;

    QFile File(name);
    if (!File.open(QIODevice::Text | QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", QString("Error: %1").
                              arg(File.errorString()));
    }else{
    QTextStream ts(&File);
    QStringList strList;
    ts << "Format odczytu:\n\n";
            ts << "Nazwa_wydarzenia\n\nMiejsce\n\nInformacje\n\nData\n\n";
            ts << "Wydarzenia użytkownika: "+sqlModel->data(sqlModel->index(0,4)).toString()+"\n\n";
            for (int i=0; i<sqlModel->rowCount(); i++)
            {
                int nr=i;
                QString s = QString::number(nr+1);
                ts<<"Wydarzenie nr"+s+": \n";
                strList.clear();
                for (int j=1; j<sqlModel->columnCount(); j++)
                    if(j!=4){
                    strList << sqlModel->data(sqlModel->index(i,j)).toString();}
                    ts << strList.join("\n\n") + "\n\n";
            }
    File.flush();
    File.close();
    }
}
