#include <QCoreApplication>
#include <qhtmlparser.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QHtmlParser *p = new QHtmlParser(nullptr, QDate(2008, 1, 1));
    p->setSize(640, 480);
    p->setQuantity(10000);
    p->getPhoto();
    QObject::connect(p, SIGNAL(isDone()), &a, SLOT(quit()));
    return a.exec();
}
