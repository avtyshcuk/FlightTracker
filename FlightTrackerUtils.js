function initSam(map) {
    var params = { "coordinate": map.center };
    var component = Qt.createComponent("GeoSam.qml");
    var geoSam = component.createObject(map, params);
    map.addMapItem(geoSam);
    samRegistry.setSamPosition(map.center);
}

function addPoint(map, coordinate) {
    var params = { "coordinate": coordinate };
    var component = Qt.createComponent("GeoPoint.qml");
    var geoPoint = component.createObject(map, params);
    map.addMapItem(geoPoint);
}
