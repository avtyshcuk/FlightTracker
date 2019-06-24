import QtQuick 2.9
import QtLocation 5.9

import Tracker 1.0

MapQuickItem {
    id: root

    anchorPoint.x: referencePoint.width / 2
    anchorPoint.y: referencePoint.height / 2
    sourceItem: SamItem {
        id: referencePoint
        width: 36
        height: width
    }

    readonly property point position: Qt.point(x + width, y + width)

    MouseArea {
        anchors.fill: parent
        drag.target: parent

        onReleased: {
            var coordinate = map.toCoordinate(position, false);
            console.log(coordinate);
//            flightRegistry.finalizeFlightUpdate(index, coordinate);
//            internal.isMoving = false;
        }

//        onPressed: {
//            internal.isMoving = true;
//        }
    }
}
