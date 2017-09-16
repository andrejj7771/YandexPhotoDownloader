#include "downloader.h"

Downloader::Downloader(QObject *parent, QString _url) : QObject(parent){
    m_manager = new QNetworkAccessManager(this);
    m_url = QUrl(_url);

    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFile(QNetworkReply*)));
}
Downloader::Downloader(QObject *parent, QUrl _url) : QObject(parent){
    m_manager = new QNetworkAccessManager(this);
    m_url = _url;

    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFile(QNetworkReply*)));
}
Downloader::~Downloader(){
    delete m_manager;
}

void Downloader::setUrl(QString _url){
    m_url = QUrl(_url);
}
void Downloader::setUrl(QUrl _url){
    m_url = _url;
}

QByteArray Downloader::getData(){
    return m_data;
}
void Downloader::get(){
    if (!m_url.isEmpty())
        m_manager->get(QNetworkRequest(m_url));
    return;
}

void Downloader::downloadFile(QNetworkReply *reply){
    m_data = reply->readAll();
    reply->deleteLater();
    emit downloaded(m_data);
}
