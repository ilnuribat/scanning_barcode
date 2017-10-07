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
    Q_PROPERTY(QImage newPhoto READ newPhoto WRITE setNewPhoto NOTIFY newPhotoChanged)

    Q_INVOKABLE void start();
    Q_INVOKABLE void capture();
    Q_INVOKABLE void stop();

    QString status() const;

signals:
    void statusChanged();
public slots:
private:
    void cameraNames();
    bool checkCameraAvailability();

    void setStatus(QString status);

    QCamera *camera;
    QCameraImageCapture *imageCapture;
    QString m_status;
};

#endif // CAPTURE_H
