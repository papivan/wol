#include <QCoreApplication>


#include <QFile>
#include <QUdpSocket>
#include <QHostAddress>

//const QString HOST_IP = "192.168.1.102";
//const QString HOST_MAC = "1c:1b:0d:7d:a9:7b";


const QString HOST_IP = "10.18.69.72";
const QString HOST_MAC = "74:d0:2b:7d:ff:19";


void wakeOnLan(QString MAC)
{
    char MACAddr [6];
    char MagicPacket [102]; // Magic package for remote boot

    int j = sscanf (MAC.toLatin1().data(), "%2x-%2x-%2x-%2x-%2x-%2x",
                    & MACAddr [0], & MACAddr [1], & MACAddr [2], & MACAddr [3], & MACAddr [4], & MACAddr [5]);
    j = sscanf (MAC.toLatin1().data(), "%2x:%2x:%2x:%2x:%2x:%2x",
                    & MACAddr [0], & MACAddr [1], & MACAddr [2], & MACAddr [3], & MACAddr [4], & MACAddr [5]);

    // Set to hexadecimal before the magicpacket array 6 characters ff
    memset (MagicPacket, 0xff, 6);

    int packetsize = 6; // the beginning of the initial value is 6, do not wrong. I is because the effect of the initial value of the written as 0, it is too effortless.
    // Build MagicPacket.
    for (int i = 0; i <16; i++)
    {
        memcpy (MagicPacket + packetsize, MACAddr, 6);
        packetsize += 6;
    }

    QHostAddress FakeAddress;
    FakeAddress.setAddress (HOST_IP);

    QUdpSocket udpSocket;
    quint64 ret = udpSocket.writeDatagram(MagicPacket, 102, FakeAddress, 9);
    qInfo() << "writeDatagram:" << ret;
}

int main(int argc, char *argv766[])
{

    wakeOnLan(HOST_MAC);
//    QCoreApplication a(argc, argv);

//    return a.exec();
    return 0;
}
