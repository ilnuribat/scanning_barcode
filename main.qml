import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtMultimedia 5.9

import QZXing 2.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Scanning barcodes")

    ColumnLayout {
        anchors {
            top: parent.top
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        width: parent.width

        Text {
            id: status
            text: "Looking for barcode"
        }

        Button {
            text: "start"
            onClicked: {
                camera.start();
            }
        }
        Button {
            text: "stop"
            onClicked: {
                camera.stop();
            }
        }
        Camera {
            id: camera
            focus {
                focusMode: CameraFocus.FocusContinuous
                focusPointMode: CameraFocus.FocusPointAuto
            }
        }
        VideoOutput {
            source: camera
            filters: [ filter ]
            Layout.fillHeight: true
            Layout.fillWidth: true
            autoOrientation: true
        }
        QZXingFilter {
            id: filter
            onDecodingFinished: {
                console.log(succeeded, decodeTime)
                if (!succeeded) {
                    status.text = 'not found';
                }
            }
            decoder {
                tryHarder: true
                enabledDecoders: QZXing.DecoderFormat_EAN_13
                onTagFound: {
                    console.log(tag);
                    status.text = 'barcode found: ' + tag;
                    camera.stop();
                }
            }
            captureRect: {
                // setup bindings
                videoOutput.contentRect;
                videoOutput.sourceRect;
                return videoOutput.mapRectToSource(videoOutput.mapNormalizedRectToItem(Qt.rect(
                    0, 0, 1, 1
                )));
            }
        }
    }
}
