#ifndef QHTMLPARSER_H
#define QHTMLPARSER_H

#include "downloader.h"

#include <QXmlStreamReader>
#include <QXmlAttributes>
#include <QVector2D>
#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QDate>
#include <QDir>

class QHtmlParser : public QObject
{
    Q_OBJECT
public:
    explicit QHtmlParser(QObject *parent = nullptr, QDate dateFrom = QDate());
    ~QHtmlParser();

    void setDateFrom(int y, int m, int d);
    void setDateTo(int y, int m, int d);
    void setSize(int width, int height);
    void setDateFrom(QDate date);
    void setDateFto(QDate date);
    void setSize(QVector2D size);
    void setQuantity(int quantity);
    void getPhoto();

signals:
    void gotLinks(QList<QUrl>);
    void isDone();

private slots:
    void downloadPhotos(QList<QUrl> list);
    void getPhotoList(QByteArray data);
    void savePhoto(QByteArray data);

private:
    Downloader *m_downloader;
    QList<QUrl> m_photoList;
    QVector2D m_photoSize;

    QDate m_dateFrom;
    QDate m_dateTo;
    int m_dCounter;
    int m_quantity;

    QString genName();
};

#endif // QHTMLPARSER_H
