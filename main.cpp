#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "capture.h"
#include "imageprovider.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<Capture>("ru.dreamkas.phone", 1, 0, "Capture");
    // ImageProvider *imageProvider = new ImageProvider();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    // engine.addImageProvider("images", imageProvider);

    return app.exec();
}
