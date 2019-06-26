import QtQuick 2.0
import QtQuick.Controls 2.1

ToolBar {
    id: root
    leftPadding: 8

    signal samAdded;

    FontLoader {
        id: myCustomFont
        source: "qrc:/fonts/aerialattackfont.ttf"
    }

    Flow {
        id: flow
        width: parent.width

        Row {
            id: fileRow

            ToolButton {
                id: startStopButton
                text: internal.startStopIcon
                font.family: myCustomFont.name
                onClicked: {

                }
            }
        }
    }

    QtObject {
        id: internal

        readonly property string startStopIcon: "\uE807"
    }
}
