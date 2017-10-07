import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import ru.dreamkas.phone 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ColumnLayout {
        anchors {
            top: parent.top
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        width: parent.width * 0.45

        Text {
            text: "Status: " + capture.status
        }

        Button {
            text: "start"
            onClicked: {
                capture.start();
            }
        }
        Button {
            text: "capture"
            onClicked: {
                capture.capture();
            }
        }
        Button {
            text: "stop"
            onClicked: {
                capture.stop();
            }
        }
        Image {
            Layout.fillHeight: true
            Layout.fillWidth: true
            source: "image://images/"
            cache: false
        }
    }

    Capture {
        id: capture
    }
}
