import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtMultimedia 5.9
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
            text: "Status: "
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
        Camera {
            id: camera
        }
        MyFilter {
            id: filter
            // set properties, they can also be animated
            // onFinished: console.log("results of the computation: " + result)
        }
        VideoOutput {
            source: camera
            filters: [ filter ]
            anchors.fill: parent
        }
    }
}
