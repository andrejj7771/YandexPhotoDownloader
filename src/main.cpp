#include <QCoreApplication>
#include <qhtmlparser.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int year = 0;
    int month = 0;
    int day = 0;
    int width = 0;
    int height = 0;
    int quantity = 0;
    cout << "Введите дату: " << endl;
    cout << "Год: "; cin >> year;
    cout << "Месяц: "; cin >> month;
    cout << "День: "; cin >> day;
    if (year <= 0 || year < 2008)
        year = 2008;
    else if (year > QDate::currentDate().year())
        year = QDate::currentDate().year();
    if (month <= 0)
        month = 1;
    if (day <= 0)
        day = 1;
    cout << "Укажите минимальное разрешение фото: " << endl;
    cout << "Ширина: "; cin >> width;
    cout << "Высoта: "; cin >> height;
    cout << "Укажите кол-во фотографий: "; cin >> quantity;
    QHtmlParser *p = new QHtmlParser(nullptr, QDate(year, month, day));
    p->setSize(width, height);
    p->setQuantity(quantity);
    p->getPhoto();
    QObject::connect(p, SIGNAL(isDone()), &a, SLOT(quit()));
    return a.exec();
}
