#include "udpserver.h"

UdpServer::UdpServer() : out(stdout, QIODevice::WriteOnly)
{
    socket = new QUdpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readDatagrams()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(handleError()));

    QList< QHostAddress > addresses = QHostInfo::fromName( QHostInfo::localHostName() ).addresses();
        foreach ( const QHostAddress & a, addresses ){
            QString protocol = "???";
                switch ( a.protocol() ){
                    case QAbstractSocket::IPv4Protocol:
                        protocol = "IPv4";
                    break;
                    case QAbstractSocket::IPv6Protocol:
                        protocol = "IPv6";
                    break;
                    case QAbstractSocket::UnknownNetworkLayerProtocol:
                        protocol = "err";
                    break;
                }
                if(protocol == "IPv4"){
                    address = a.toString();
                    break;
                }
        }

    if(socket->bind(QHostAddress::Any, 666))
    {
        out << tr("Server has started successfully on port 666") << endl;
        out << tr("Address for connection is %1:666\n").arg(address) << endl;
    } else
    {
        QTimer::singleShot(0, qApp, SLOT(quit()));
        out << tr("Unable to start the server at 66 port") << endl;
    }
}

void UdpServer::handleError()
{
    out << "error: " << socket->errorString() << endl;
}

void UdpServer::readDatagrams()
{
    while(socket->hasPendingDatagrams())
    {
        QByteArray str;

        str.resize(socket->pendingDatagramSize());

        socket->readDatagram(str.data(), str.size(), &addr);

        QString p = QString(str);
        p.remove(0,p.indexOf("@")+1);
        port = p.toInt();

        out << addr.toString() << ":" << port << " " << tr("says") << ": "
            << str << endl;

        sendString(sortLine(str));
    }
}

QString UdpServer::sortLine(QString string){
    QString str;

    QList<int> list;
    int i = 0;

    while(!string.isEmpty()){
        str = string.section(' ',i,i);
        string.remove(0,str.length()+1);
        if(!string.contains(' '))
            string.remove(str);
        list << str.toInt();
    }

    qSort(list.begin(), list.end());
    str.clear();

    for(int i = 0; i< list.count(); i++)
        str += QString("%1 ").arg(list.at(i));

    str.remove(str.length(),1);

    return str;
}

void UdpServer::sendString(QString string){

    out << tr("Send string \"") << string << tr("to ") << addr.toString() << ":" << port << endl;
    socket->writeDatagram(string.toUtf8(), addr, port);
}
