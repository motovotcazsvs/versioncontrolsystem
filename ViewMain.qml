import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4


Page {
    id: rootMain
    visible: true
    
    property bool nameOrPath: false

    Connections {
        target: control
        onChangeShowString: {
            text_str1 = str1;
            text_str2 = str2;
            text_str3 = str3;
            text_enterstring = str4;
            text_str5 = str5;
            text_str6 = str6;
            text_str7 = str7;
        }
    }


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
            id: text_str3
            color: color_strings
            text: "C:/QT_PROJECTS/versio"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: rec_enterstring.top
            anchors.bottomMargin: 40
            font.pixelSize: 20
            font.italic: true
        }
        
        Text {
            id: text_str5
            text: "analyzerGL10"
            color: color_strings
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: rec_enterstring.bottom
            anchors.topMargin: 40
            font.pixelSize: 20
        }
        
        Text {
            id: text_str1
            text: "C:/QT_PROJECTS/versioncontrolsystemk/hfdjgfdg"
            color: color_strings
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: text_str2.top
            anchors.bottomMargin: 10
            font.pixelSize: 20
            font.italic: true
        }
        
        Text {
            id: text_str6
            text: "jhkjhjk"
            color: color_strings
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: text_str5.bottom
            anchors.topMargin: 10
            font.pixelSize: 20
        }
        
        Text {
            id: text_str2
            text: "jhkjhjk"
            color: color_strings
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: text_str3.top
            anchors.bottomMargin: 10
            font.pixelSize: 20
        }
        
        Text {
            id: text_str7
            text: "init"
            color: color_strings
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: text_str6.bottom
            anchors.topMargin: 10
            font.pixelSize: 20
        }
    }
}
