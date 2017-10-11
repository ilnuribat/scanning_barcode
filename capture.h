#ifndef CAPTURE_H
#define CAPTURE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QZXing.h>
#include <QImage>
#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraInfo>
#include <QAbstractVideoSurface>
#include "myvideosurface.h"

class Capture : public QObject
{
    Q_OBJECT
public:
    explicit Capture(QObject *parent = nullptr);
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)

    Q_INVOKABLE void start();
    Q_INVOKABLE void capture();
    Q_INVOKABLE void stop();

    QString status() const;
    QString url() const;

signals:
    void statusChanged();
    void urlChanged();
public slots:
private:
    void cameraNames();
    bool checkCameraAvailability();

    void setStatus(QString status);
    void setUrl(QString url);

    QCamera *camera;
    QCameraImageCapture *imageCapture;
    QString m_status;
    QString m_url;
};

#endif // CAPTURE_H
