#ifndef PROXY_H
#define PROXY_H

#include <QByteArray>
#include <QObject>
//#include <QSerialPort>

class Proxy : public QObject
{
    Q_OBJECT

public:
    explicit Proxy(QObject *parent = 0);

signals:
    void cardDetected(ulong cardId);

protected:
    virtual void timerEvent(QTimerEvent *) Q_DECL_OVERRIDE;

private:
    //QSerialPort serialPort;
};

#endif // PROXY_H
