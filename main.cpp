#include <QCoreApplication>
#include <QTextCodec>

#include "udpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    {
    QTextCodec* unicode = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(unicode);
    QTextCodec::setCodecForTr(unicode);
    }

    UdpServer s;

    return a.exec();
}
