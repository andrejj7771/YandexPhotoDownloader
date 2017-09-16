#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QObject>
#include <QUrl>

class Downloader : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager *m_manager;
    QByteArray m_data;
    QUrl m_url;

public:
    explicit Downloader(QObject *parent = nullptr, QUrl _url = QUrl(""));
    explicit Downloader(QObject *parent = nullptr, QString _url = "");
    ~Downloader();

    void setUrl(QString _url);
    void setUrl(QUrl _url);
    void get();

    QByteArray getData();

signals:
    void downloaded(QByteArray data);

private slots:
    void downloadFile(QNetworkReply *reply);
};

#endif // DOWNLOADER_H
