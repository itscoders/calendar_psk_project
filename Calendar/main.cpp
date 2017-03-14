#include <QApplication>
#include "logwindow.h"
#include "sqldatebase.h"

/*!
 * @brief Funkcja główna
 * @param argc
 * @param argv
 * @return app.exec()
 */

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SqlDateBase::connectDateBase();

    LogWindow l;
    l.show();


    return app.exec();
}
