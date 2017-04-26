#include "filedownloader.h"

filedownloader::filedownloader(QUrl fileUrl, QObject *parent):
    QObject(parent)
{
    connect(&m_WebCtrl,
            SIGNAL(finished(QNetworkReply*)),
            SLOT(fileDownloaded(QNetworkReply*)));
    //
    QNetworkRequest request(fileUrl);
    QNetworkReply *reply;
    reply = m_WebCtrl.get(request);
    ReplyTimeout::set(reply, 100) ;//(reply, 1);
    //

    //
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
                   SLOT(replyError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()), reply,
                   SLOT(deleteLater()));
    //
    host = fileUrl.host();
    //
}

filedownloader::~filedownloader()
{

}

void filedownloader::fileDownloaded(QNetworkReply* pReply)
{
    m_DownloadedData = pReply->readAll();
    //emit a signal
    pReply->deleteLater();
    emit downloaded();
}

void filedownloader::replyError(QNetworkReply::NetworkError code)
{
    Q_UNUSED(code);
    //qDebug() << "Net error " << code;
    emit someError();
}

QByteArray filedownloader::downloadedData() const
{
    return m_DownloadedData;
}

QString filedownloader::url_host(){
    return host;
}
