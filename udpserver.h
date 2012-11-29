#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QtNetwork/QtNetwork>
#include <QTextStream>

class QUdpSocket;

class UdpServer : public QObject
{
    Q_OBJECT
public:
    UdpServer();

private:
    QUdpSocket* socket;
    QTextStream out;
    QString address;
    QString sortLine(QString);
    void sendString(QString);
    QHostAddress addr;
    quint16 port;

private slots:
    void readDatagrams();
    void handleError();
};

#endif // UDPSERVER_H
