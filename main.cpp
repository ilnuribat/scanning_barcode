#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QVideoFilterRunnable>
#include "capture.h"
#include "imageprovider.h"
#include <QDebug>

int count = 0;

class MyFilterRunnable : public QVideoFilterRunnable {
public:
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags)
    {
        Q_UNUSED(surfaceFormat)
        Q_UNUSED(flags)
        // QVideoFrame -> QImage
        QImage img;
        QVideoFrame frame(*input);  // make a copy we can call map (non-const) on
        frame.map(QAbstractVideoBuffer::ReadOnly);
        QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(
                    frame.pixelFormat());
        if (imageFormat != QImage::Format_Invalid) {
            img = QImage(frame.bits(),
                         frame.width(),
                         frame.height(),
                         // frame.bytesPerLine(),
                         imageFormat);
        } else {
            // e.g. JPEG
            int nbytes = frame.mappedBytes();
            img = QImage::fromData(frame.bits(), nbytes);
        }
        qDebug() << img
                 << frame.bits()
                 << frame.width()
                 << frame.height()
                 << frame.bytesPerLine()
                 << imageFormat
                 << QImage::Format_Invalid
                 << frame.pixelFormat()
                 << QVideoFrame::Format_Jpeg;
        QZXing decoder;
        decoder.setDecoder(QZXing::DecoderFormat_EAN_13);

        QString result = decoder.decodeImage(img);
        if (result.length() > 0) {
            qDebug() << "result of decoding: " << result;
        }
        if (count % 10 == 0) {
            img.save("capturedFromFIlter" + QString::number(count));
        }
        count ++;
        return *input;
    }
};

class MyFilter : public QAbstractVideoFilter {
public:
    QVideoFilterRunnable *createFilterRunnable() { return new MyFilterRunnable; }
signals:
    void finished(QObject *result);
};

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    // qmlRegisterType<Capture>("ru.dreamkas.phone", 1, 0, "Capture");
    qmlRegisterType<MyFilter>("ru.dreamkas.phone", 1, 0, "MyFilter");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
