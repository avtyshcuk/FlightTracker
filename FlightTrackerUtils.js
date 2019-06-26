function initSam(map) {
    var params = { "coordinate": map.center };
    var component = Qt.createComponent("GeoSam.qml");
    var geoSam = component.createObject(map, params);
    map.addMapItem(geoSam);
    samRegistry.setSamPosition(map.center);
}
