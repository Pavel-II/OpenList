#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QTimerEvent>
#include <QBasicTimer>
//
class ReplyTimeout : public QObject {
  Q_OBJECT
  QBasicTimer m_timer;
public:
  ReplyTimeout(QNetworkReply* reply, const int timeout) : QObject(reply) {
    Q_ASSERT(reply);
    if (reply && reply->isRunning())
      m_timer.start(timeout, this);
  }
  static void set(QNetworkReply* reply, const int timeout) {
    new ReplyTimeout(reply, timeout);
  }
protected:
  void timerEvent(QTimerEvent * ev) {
    if (!m_timer.isActive() || ev->timerId() != m_timer.timerId())
      return;
    auto reply = static_cast<QNetworkReply*>(parent());
    if (reply->isRunning())
      reply->close();
    m_timer.stop();
  }
};
//
class filedownloader : public QObject
{
    Q_OBJECT
public:
    explicit filedownloader(QUrl fileUrl, QObject *parent = 0);

    virtual ~filedownloader();

    QByteArray downloadedData() const;
    QString url_host();
signals:
        void downloaded();
        void someError();


private slots:

    void fileDownloaded(QNetworkReply* pReply);
    void replyError(QNetworkReply::NetworkError code);

private:
    QString host;
    QNetworkAccessManager m_WebCtrl;

    QByteArray m_DownloadedData;


};

#endif // FILEDOWNLOADER_H
