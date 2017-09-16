#include <QCoreApplication>
#include <qhtmlparser.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QHtmlParser *p = new QHtmlParser(nullptr, QDate(2008, 1, 1));

    return a.exec();
}
