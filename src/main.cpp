#include <QCoreApplication>
#include <qxmlparser.h>
#include <iostream>
#include <QString>

using namespace std;

void outputHelp(){
    cout << endl << "Help" << endl;
    cout << "--help - show arguments list." << endl;
    cout << "-w --width - minimal width in pixels." << endl;
    cout << "-h --height - minimal height in pixels." << endl;
    cout << "-q --quantity - download pitcures quantity." << endl;
    cout << "-df --datefrom - date from downloading begins. (Date fromat YYYY.MM.DD)" << endl;
    //cout << "-dt --dateto - date to downloading ends." << endl;
}

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    int year = 0;
    int month = 0;
    int day = 0;
    int width = 0;
    int height = 0;
    int quantity = 0;

    for (int i = 0; i < argc; i++){
        string tmp;
        tmp.append(argv[i]);
        //cout << "c " << tmp << endl;
        if (!tmp.find("--help"))
            outputHelp();
        if (!tmp.find("-w") || !tmp.find("--width")){
            tmp.clear();
            if (argv[i + 1] != nullptr){
                tmp.append(argv[i + 1]);
                try{
                    width = std::stoi(tmp);
                    if (width < 0)
                        width = abs(width);
                }
                catch(const invalid_argument ar){
                    tmp.clear();
                    tmp.append(argv[i]);
                    cout << "Error: " << ar.what() << endl << "After " + tmp + " must stand be integer value" << endl;
                }
                i++;
            }
        }
        if (!tmp.find("-h") || !tmp.find("--height")){
            tmp.clear();
            if (argv[i + 1] != nullptr){
                tmp.append(argv[i + 1]);
                try{
                    height = std::stoi(tmp);
                    if (height < 0)
                        height = abs(height);
                }
                catch(const invalid_argument ar){
                    tmp.clear();
                    tmp.append(argv[i]);
                    cout << "Error: " << ar.what() << endl << "After " + tmp + " must stand be integer value" << endl;
                }
                i++;
            }
        }
        if (!tmp.find("-q") || !tmp.find("--quantity")){
            tmp.clear();
            if (argv[i + 1] != nullptr){
                tmp.append(argv[i + 1]);
                try{
                    quantity = std::stoi(tmp);
                    if (quantity < 0)
                        quantity = abs(quantity);
                }
                catch(const invalid_argument ar){
                    tmp.clear();
                    tmp.append(argv[i]);
                    cout << "Error: " << ar.what() << endl << "After " + tmp + " must stand be integer value" << endl;
                }
                i++;
            }
        }
        if (!tmp.find("-df") || !tmp.find("--datefrom")){
            tmp.clear();
            if (argv[i + 1] != nullptr){
                tmp.append(argv[i + 1]);
                string loc = "";
                for(int i = 0; i < tmp.size(); i++){
                    if (tmp.at(i) != '.')
                        loc += tmp.at(i);
                    else if (tmp.at(i) == '.' && i == 4){
                        try{
                            year = std::stoi(loc);
                            if (year < 0)
                                year = abs(year);
                        }
                        catch(const invalid_argument ar){
                            tmp.clear();
                            tmp.append(argv[i]);
                            cout << "Error: " << ar.what() << endl << "After " + tmp + " must stand be integer value" << endl;
                        }
                        loc.clear();
                    }
                    else if (tmp.at(i) == '.' && i == 7){
                        try{
                            month = std::stoi(loc);
                            if (month < 0)
                                month = abs(month);
                        }
                        catch(const invalid_argument ar){
                            tmp.clear();
                            tmp.append(argv[i]);
                            cout << "Error: " << ar.what() << endl << "After " + tmp + " must stand be integer value" << endl;
                        }
                        loc.clear();
                    }
                    if (i == tmp.size() - 1){
                        try{
                            day = std::stoi(loc);
                            if (day < 0)
                                day = abs(day);
                        }
                        catch(const invalid_argument ar){
                            tmp.clear();
                            tmp.append(argv[i]);
                            cout << "Error: " << ar.what() << endl << "After " + tmp + " must stand be integer value" << endl;
                        }
                        loc.clear();
                    }
                }
            }
            i++;
        }
    }
    cout << width << endl << height << endl << quantity << endl << year << endl << month << endl << day << endl;

    if (year == 0 || month == 0 || day == 0){
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
    }
    if (width == 0 || height == 0){
        cout << "Укажите минимальное разрешение фото: " << endl;
        cout << "Ширина: "; cin >> width;
        cout << "Высoта: "; cin >> height;
    }
    if (quantity == 0){
        cout << "Укажите кол-во фотографий: "; cin >> quantity;
    }

    QXmlParser *p = new QXmlParser(nullptr, QDate(year, month, day));
    p->setSize(width, height);
    p->setQuantity(quantity);
    p->setQuality(65);
    p->setIMGFormat("JPEG");
    p->getPhoto();

    QObject::connect(p, SIGNAL(isDone()), &a, SLOT(quit()));
    QObject::connect(p, SIGNAL(error()), &a, SLOT(quit()));

    return a.exec();
}
