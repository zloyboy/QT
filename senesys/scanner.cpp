#include "scanner.h"

Scanner::Scanner(QObject *parent) : QObject(parent)
{
    handle = ftrScanOpenDevice();

    if (handle != 0)
    {
        ftrScanGetImageSize(handle, &imageSize);

        startTimer(500);
    }
}

void Scanner::timerEvent(QTimerEvent *)
{
    if (ftrScanIsFingerPresent(handle, 0) != 0)
    {
        uchar *frame = new uchar[imageSize.nImageSize];

        if (ftrScanGetFrame(handle, frame, 0) != 0)
        {
            QImage image(frame, imageSize.nWidth, imageSize.nHeight, imageSize.nWidth, QImage::Format_Grayscale8);

            QPixmap pixmap = QPixmap::fromImage(image, Qt::NoFormatConversion);

            pixmap.detach();

            emit fingerPresent(pixmap);
        }

        delete[] frame;
    }
}
