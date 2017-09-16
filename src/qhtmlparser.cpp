#include "qhtmlparser.h"

QHtmlParser::QHtmlParser(QObject *parent, QDate dateFrom) : QObject(parent){
    m_dateFrom = dateFrom;
    m_dateTo = QDate::currentDate();
    m_downloader = new Downloader(nullptr, "");
    m_downloader->setUrl("http://api-fotki.yandex.ru/api/recent/updated;" + QString::number(m_dateFrom.year()) + "-" + QString::number(m_dateFrom.month()) + "-" + QString::number(m_dateFrom.day()) + "T14:59:24Z,567023,31779780/");
    m_downloader->get();

    setSize(800, 600);

    m_dCounter = 0;

    if (!QDir().exists(QDir::homePath() + "/photos"))
        QDir().mkdir(QDir::homePath() + "/photos");

    connect(m_downloader, SIGNAL(downloaded(QByteArray)), this, SLOT(getPhotoList(QByteArray)));
    connect(m_downloader, SIGNAL(downloaded(QByteArray)), this, SLOT(savePhoto(QByteArray)));
    connect(this, SIGNAL(gotLinks(QList<QUrl>)), this, SLOT(downloadPhotos(QList<QUrl>)));
}
QHtmlParser::~QHtmlParser(){
    delete m_downloader;
}

void QHtmlParser::getPhotoList(QByteArray data){
    QXmlStreamReader reader(data);

    while (!reader.hasError() && !reader.atEnd()) {
        QXmlStreamReader::TokenType token = reader.readNext();

        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement){
            if (reader.name() != "img")
                continue;
            else {
                foreach (QXmlStreamAttribute atr, reader.attributes()) {
                    if (atr.name() == "height" && atr.value().toInt() < m_photoSize.x())
                        break;
                    if (atr.name() == "width" && atr.value().toInt() < m_photoSize.y())
                        break;
                    if (atr.name() == "href")
                        m_photoList.append(QUrl(atr.value().toString()));
                }
            }
        }
    }
    disconnect(m_downloader, SIGNAL(downloaded(QByteArray)), this, SLOT(getPhotoList(QByteArray)));
    emit gotLinks(m_photoList);
}

void QHtmlParser::downloadPhotos(QList<QUrl> list){
    qDebug() << list.size();
    auto it = list.begin();
    while (it != list.end()) {
        QUrl tmp = *it;
        m_downloader->setUrl(tmp);
        m_downloader->get();
        it++;
    }
}
void QHtmlParser::savePhoto(QByteArray data){
    if (m_photoList.isEmpty()){
        qDebug() << "There is no photos";
        return;
    }
    QImage image;
    if (image.loadFromData(data)){
        m_dCounter++;
        QString name = genName();
        qDebug() << m_dCounter << " - " << name << " - " << image.save(QString(QDir::homePath() + "/photos/" + name), "JPEG", 100);
    }
    if (m_dCounter == m_photoList.size()){
        connect(m_downloader, SIGNAL(downloaded(QByteArray)), this, SLOT(getPhotoList(QByteArray)));
        m_dateFrom.setDate(m_dateFrom.year(), m_dateFrom.month(), m_dateFrom.day() + 1);
        if (m_dateFrom == m_dateTo){
            qDebug() << "(D)Done!";
            return;
        }
        else if (m_dCounter == 10000){
            qDebug() << "(Q)Done!";
            return;
        }
        m_downloader->setUrl("http://api-fotki.yandex.ru/api/recent/updated;" + QString::number(m_dateFrom.year()) + "-" + QString::number(m_dateFrom.month()) + "-" + QString::number(m_dateFrom.day()) + "T14:59:24Z,567023,31779780/");
        m_downloader->get();
    }
}

QString QHtmlParser::genName(){
    char s[10 + 26 + 26];
    memset(s, 0, strlen(s));
    for (int i = 48; i <= 57; i++)
        s[i - 48] = i;
    for (int i = 65; i <= 90; i++)
        s[10 + i - 65] = i;
    for (int i = 97; i <= 122; i++)
        s[10 + 26 + i - 97] = i;
    QString res;
    for (int i = 0; i < 13; i++){
        res.append(s[qrand() % 61]);
    }
    return res;
}

void QHtmlParser::setSize(int width, int height){
    m_photoSize.setX(width);
    m_photoSize.setY(height);
}
void QHtmlParser::setSize(QVector2D size){
    m_photoSize = size;
}
