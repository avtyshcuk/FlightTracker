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
                id: addSamButton
                text: internal.addSamIcon
                font.family: myCustomFont.name
                visible: !samRegistry.isSamRegistered
                onClicked: {
                    samAdded();
                }
            }
        }
    }

    QtObject {
        id: internal

        readonly property string addSamIcon: "\uE807"
    }
}
