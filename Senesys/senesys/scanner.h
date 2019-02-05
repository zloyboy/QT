#ifndef SCANNER_H
#define SCANNER_H

#include <QImage>
#include <QObject>
#include <QPixmap>

#include <ftrScanAPI.h>

class Scanner : public QObject
{
    Q_OBJECT

public:
    explicit Scanner(QObject *parent = 0);

signals:
    void fingerPresent(QPixmap pixmap);

protected:
    virtual void timerEvent(QTimerEvent *) Q_DECL_OVERRIDE;

private:
    FTRHANDLE handle;
    FTRSCAN_IMAGE_SIZE imageSize;
};

#endif // SCANNER_H
