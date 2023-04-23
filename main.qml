import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4


Window {
    visible: true
    width: 400
    height: 400
    //color: "transparent"
    x: Screen.width - width - 50
    y: Screen.height - height - 100

    property color color_strings: "#F4F448"//

    //flags: Qt.FramelessWindowHint //скрываются кнопки сверху окошка
    /*flags: Qt.FramelessWindowHint |
           Qt.WindowMinimizeButtonHint |
           Qt.Window//скрываются кнопки сверху окошка но значек есть на панели задач
*/
    /*MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }*/

    StackView {
        id: stack
        initialItem: viewMain //для работы
        //initialItem: viewDataCalibration //для отработки страниц
        anchors.fill: parent

        delegate: StackViewDelegate { //переход со средины
            pushTransition: StackViewTransition {
                PropertyAnimation {
                    target: enterItem
                    property: "scale"
                    from: 0
                    to: 1
                    duration: 500
                }
                PropertyAnimation {
                    target: exitItem
                    property: "scale"
                    from: 1
                    to: 0
                    duration: 10
                }
            }
        }
    }

    ViewMain {
        id: viewMain
    }
}
