import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4


Page {
    id: rootProjectsOffline
    visible: false

    Rectangle {
        id: rec_circle
        width: 380
        height: 380
        anchors.centerIn: parent
        radius: 190
        color: "#4C2F27"

        Rectangle {
            id: center_circle
            width: 100
            height: 100
            radius: 50
            color: "white"
            anchors.centerIn: parent

            MouseArea {
                id: mouseArea_enter
                anchors.fill: parent
                onClicked: {
                    if(nameOrPath) stack.push(viewProjectsOnline);
                    else stack.push(viewProjectsOffline);
                }
            }
        }

        Rectangle {
            id: rec_enterstring
            width: parent.width
            height: 30
            anchors.verticalCenter: parent.verticalCenter
            clip: true

            Text {
                id: text_enterstring
                color: "#48a011"
                text: "C:\\QT_PROJECTS\\versioncontrolsystemk"
                font.italic: true
                anchors.verticalCenterOffset: -3
                anchors.right: parent.right
                font.pixelSize: 20
                horizontalAlignment: Text.AlignRight
                anchors.verticalCenter: parent.verticalCenter

            }
        }



        Text {
            id: text_str1
            color: color_strings
            text: "push"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: rec_enterstring.top
            anchors.bottomMargin: 40
            font.pixelSize: 20
            font.italic: true
        }

        Text {
            id: text_str2
            text: "pull"
            color: color_strings
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: rec_enterstring.bottom
            anchors.topMargin: 40
            font.pixelSize: 20
            font.italic: true
        }

        Text {
            id: text_str3
            text: "commit -m"
            color: color_strings
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: text_str1.top
            anchors.bottomMargin: 10
            font.pixelSize: 20
            font.italic: true
        }

        Text {
            id: text_str4
            text: "branch"
            color: color_strings
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: text_str2.bottom
            anchors.topMargin: 10
            font.pixelSize: 20
            font.italic: true
        }

        Text {
            id: text_str5
            text: "merge"
            color: color_strings
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: text_str3.top
            anchors.bottomMargin: 10
            font.pixelSize: 20
            font.italic: true
        }

        Text {
            id: text_str6
            text: "PROJECTS"
            color: color_strings
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: text_str4.bottom
            anchors.topMargin: 10
            font.pixelSize: 20
        }
    }
}
