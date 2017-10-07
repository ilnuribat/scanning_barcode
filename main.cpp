#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QZXing.h>
#include <QImage>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QImage image;
    bool loaded= image.load(":/photo_2017-10-07_18-27-51.jpg");

    QZXing decoder;
    decoder.setDecoder(QZXing::DecoderFormat_EAN_13);
    QString result = decoder.decodeImage(image);

    qDebug() << "result: " << result;


    return app.exec();
}
