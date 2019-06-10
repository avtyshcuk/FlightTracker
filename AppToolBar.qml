import QtQuick 2.0
import QtQuick.Controls 2.1

ToolBar {
    id: root
    leftPadding: 8

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
                id: addSamButton
                text: internal.addSamIcon
                font.family: myCustomFont.name
                onClicked: {
                    samRegistry.isSamModifying = true;
                }
            }
        }
    }

    QtObject {
        id: internal

        readonly property string addSamIcon: "\uE807"
    }
}
