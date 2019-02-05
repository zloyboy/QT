#include "proxy.h"

Proxy::Proxy(QObject *parent) : QObject(parent)
{
    //serialPort.setPortName("/dev/ttyUSB0");
    //serialPort.open(QIODevice::ReadOnly);

    startTimer(0);
}

void Proxy::timerEvent(QTimerEvent *)
{
    /*while (serialPort.canReadLine())
    {
        QByteArray line = serialPort.readLine();

        if (line.size() != 15)
            continue;

        ulong cardId = line.mid(3, 8).toULong(0, 16);

        if (cardId == 0)
            continue;

        emit cardDetected(cardId);
    }

    serialPort.waitForReadyRead(2000);*/
}
