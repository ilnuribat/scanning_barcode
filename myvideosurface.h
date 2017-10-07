#ifndef MYVIDEOSURFACE_H
#define MYVIDEOSURFACE_H

#include <QDebug>
#include <QAbstractVideoSurface>

class MyVideoSurface : public QAbstractVideoSurface
{
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const
    {
        Q_UNUSED(handleType);

        // Return the formats you will support
        return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_RGB565;
    }

    bool present(const QVideoFrame &frame)
    {
        Q_UNUSED(frame);
        // Handle the frame and do your processing

        qDebug() << frame;
        return true;
    }
};

#endif // MYVIDEOSURFACE_H
