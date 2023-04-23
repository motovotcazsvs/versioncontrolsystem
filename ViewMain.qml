import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4


Page {
    id: rootMain
    visible: true
    

    Connections {
        target: control
        onChangeShowString: {
            text_str1.text = str1;
            text_str2.text = str2;
            text_str3.text = str3;
            textedit_enterstring.text = str4;
            text_str5.text = str5;
            text_str6.text = str6;
            text_str7.text = str7;
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
                    textedit_enterstring.x = textedit_enterstring.width > 380 ? 380 - textedit_enterstring.width : 0;

                }
            }
        }
        
        Rectangle {
            id: rec_text1
            anchors.left: parent.left
            anchors.leftMargin: 75
            anchors.right: parent.right
            anchors.rightMargin: 75
            height: 25
            anchors.bottom: rec_text2.top
            anchors.bottomMargin: 10
            border.color: "white"
            color: "transparent"
            clip: true

            Text {
                id: text_str1
                //text: "hjj"
                color: color_strings
                x: text_str1.contentWidth > 230 ? 230 - text_str1.contentWidth : (230 - text_str1.contentWidth) / 2
                font.pixelSize: 20
                font.italic: control.commandOrRepository(text_str1.text)
            }
        }

        Rectangle {
            id: rec_text2
            anchors.left: parent.left
            anchors.leftMargin: 45
            anchors.right: parent.right
            anchors.rightMargin: 45
            height: rec_text1.height
            anchors.bottom: rec_text3.top
            anchors.bottomMargin: 10
            border.color: "white"
            color: "transparent"
            clip: true

            Text {
                id: text_str2
                text: ""
                x: text_str2.contentWidth > 290 ? 290 - text_str2.contentWidth : (290 - text_str2.contentWidth) / 2
                color: color_strings
                font.pixelSize: 20
                font.italic: control.commandOrRepository(text_str2.text)
            }
        }

        Rectangle {
            id: rec_text3
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.right: parent.right
            anchors.rightMargin: 15
            height: rec_text1.height
            anchors.bottom: center_circle.top
            anchors.bottomMargin: 10
            border.color: "white"
            color: "transparent"
            clip: true

            Text {
                id: text_str3
                color: color_strings
                text: ""
                x: text_str3.contentWidth > 350 ? 350 - text_str3.contentWidth : (350 - text_str3.contentWidth) / 2
                font.pixelSize: 20
                font.italic: control.commandOrRepository(text_str3.text)
            }
        }

        Rectangle {
            id: rec_enterstring
            width: parent.width
            height: 30
            anchors.verticalCenter: parent.verticalCenter
            clip: true
            border.color: "black"

            TextEdit {
                id: textedit_enterstring
                text: ""
                x: textedit_enterstring.width > 380 ? 380 - textedit_enterstring.width : (380 - textedit_enterstring.contentWidth) / 2
                color: "#48a011"
                font.italic: true
                anchors.verticalCenterOffset: -3
                font.pixelSize: 20
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Rectangle {
            id: rec_text5
            height: rec_text1.height
            border.color: "white"
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.top: center_circle.bottom
            anchors.topMargin: 10
            color: "transparent"
            clip: true

            Text {
                id: text_str5
                text: ""
                color: color_strings
                x: text_str5.contentWidth > 350 ? 350 - text_str5.contentWidth : (350 - text_str5.contentWidth) / 2
                font.pixelSize: 20
                anchors.verticalCenterOffset: -5
                anchors.verticalCenter: parent.verticalCenter
                font.italic: control.commandOrRepository(text_str5.text)
            }
        }

        Rectangle {
            id: rec_text6
            height: rec_text1.height
            anchors.left: parent.left
            anchors.leftMargin: 45
            anchors.right: parent.right
            anchors.rightMargin: 45
            anchors.top: rec_text5.bottom
            anchors.topMargin: 10
            border.color: "white"
            color: "transparent"
            clip: true

            Text {
                id: text_str6
                text: ""
                color: color_strings
                x: text_str6.contentWidth > 290 ? 290 - text_str6.contentWidth : (290 - text_str6.contentWidth) / 2
                font.pixelSize: 20
                anchors.verticalCenterOffset: -5
                anchors.verticalCenter: parent.verticalCenter
                font.italic: control.commandOrRepository(text_str6.text)
            }
        }

        Rectangle {
            id: rec_text7
            height: rec_text1.height
            border.color: "white"
            anchors.left: parent.left
            anchors.leftMargin: 75
            anchors.right: parent.right
            anchors.rightMargin: 75
            anchors.top: rec_text6.bottom
            anchors.topMargin: 10
            color: "transparent"
            clip: true

            Text {
                id: text_str7
                text: ""
                color: color_strings
                x: text_str7.contentWidth > 230 ? 230 - text_str7.contentWidth : (230 - text_str7.contentWidth) / 2
                font.pixelSize: 20
                anchors.verticalCenterOffset: -5
                anchors.verticalCenter: parent.verticalCenter
                font.italic: control.commandOrRepository(text_str7.text)
            }
        }

        Rectangle {
            id: rec_up_button
            width: parent.width
            anchors.top: parent.top
            anchors.bottom: center_circle.top
            color: "transparent"
            border.color: "red"

            MouseArea {
                id: mouseArea_upbutton
                anchors.fill: parent
                onClicked: {
                    control.setControlUp();
                }
            }
        }

        Rectangle {
            id: rec_down_button
            width: parent.width
            anchors.top: center_circle.bottom
            anchors.bottom: parent.bottom
            color: "transparent"
            border.color: "red"

            MouseArea {
                id: mouseArea_downbutton
                anchors.fill: parent
                onClicked: {
                    control.setControlDown();
                }
            }
        }
    }
}
