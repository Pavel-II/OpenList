#ifndef OPENVPNCLIENT_H
#define OPENVPNCLIENT_H

#include <QObject>

class OpenVPNCLIENT : public QObject
{
    Q_OBJECT
public:
    explicit OpenVPNCLIENT(QObject *parent = 0);
    //
public:
    QString CommonName;
    QString RealAddress;
    QString BytesReceived;
    QString BytesSent;
    QString ConnectedSince;
    QString VirtualAddress;
    QString LastRef;

signals:

public slots:
};

#endif // OPENVPNCLIENT_H
