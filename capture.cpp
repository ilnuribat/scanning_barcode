#include "capture.h"

Capture::Capture(QObject *parent) : QObject(parent)
{
    qDebug() << "instance created!";
    camera = new QCamera(QCamera::BackFace);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    MyVideoSurface *viewFinder = new MyVideoSurface();
    camera->setViewfinder(viewFinder);
    imageCapture = new QCameraImageCapture(camera);

    connect(imageCapture, &QCameraImageCapture::imageCaptured, [=] (int id, const QImage &preview) {
        qDebug() << "Image captured! " << id << preview;

        QZXing decoder;
        decoder.setDecoder(QZXing::DecoderFormat_EAN_13);
        QString result = decoder.decodeImage(preview);
        qDebug() << "decoding image from photo: " << result;
        if (result.length() > 0) {
            setStatus(result);
        }
    });
    connect(imageCapture, &QCameraImageCapture::imageExposed, [=] (int id) {
        qDebug() << "Image with id: " << id << " exposed";
    });
}

void Capture::start() {
    camera->start();
    setStatus("started");
}

void Capture::capture() {
    int id = imageCapture->capture();
    qDebug() << "captureId: " << id;
    setStatus("capturing!");
    if (camera->error()) {
        qDebug() << "errors: " << camera->error() << camera->errorString();
    }
}

void Capture::stop() {
    camera->stop();
    setStatus("stopped");
}

void Capture::setStatus(QString status) {
    this->m_status = status;
    emit statusChanged();
}

QString Capture::status() const { return this->m_status; }
