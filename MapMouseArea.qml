import QtQuick 2.9
import QtLocation 5.9

MouseArea {
    id: mapMouseArea
    anchors.fill: parent
    acceptedButtons: Qt.RightButton | Qt.LeftButton
    hoverEnabled: false

    property var map: null

    onClicked: {
        if (samRegistry.isSamModifying) {
            var point = Qt.point(mouseX, mouseY);
            var coordinate = map.toCoordinate(point);
            var params = { "coordinate": coordinate };

            var component = Qt.createComponent("GeoSam.qml");
            var geoSam = component.createObject(map, params);
            map.addMapItem(geoSam);
        }
    }
}
