function initSam(map) {
    var params = { "coordinate": map.center };
    var component = Qt.createComponent("GeoSam.qml");
    var geoSam = component.createObject(map, params);
    map.addMapItem(geoSam);
    samRegistry.setSamPosition(map.center);
}

var pointsRegistry = {};

function addPoint(map, id, coordinate) {
    var params = { "coordinate": coordinate };
    var component = Qt.createComponent("GeoPoint.qml");
    var geoPoint = component.createObject(map, params);
    if (!(id in pointsRegistry)) {
        pointsRegistry[id] = [];
    }
    pointsRegistry[id].push(geoPoint);

    if (pointsRegistry[id].length > 6) {
        map.removeMapItem(pointsRegistry[id][0]);
        pointsRegistry[id].splice(0, 1);
    }

    map.addMapItem(geoPoint);
}

var flightTracksRegistry = {};

function updateFlightTracks(id, point, azimuth) {
    addPoint(map, id, point);

    map.removeMapItem(flightTracksRegistry[id]);
    var params = {
        "coordinate": point,
        "azimuth": azimuth
    };
    var component = Qt.createComponent("GeoAirPlane.qml");
    var geoFlightPlane = component.createObject(map, params);
    flightTracksRegistry[id] = geoFlightPlane;
    map.addMapItem(geoFlightPlane);
}

function clearAll() {
    for (var pointsId in pointsRegistry) {
        if (pointsRegistry.hasOwnProperty(pointsId)) {
            for (var i = 0; i < pointsRegistry[pointsId].length; ++i) {
                map.removeMapItem(pointsRegistry[pointsId][i]);
            }
            delete pointsRegistry.pointsId;
        }
    }

    for (var tracksId in flightTracksRegistry) {
        if (flightTracksRegistry.hasOwnProperty(tracksId)) {
            map.removeMapItem(flightTracksRegistry[tracksId]);
            delete flightTracksRegistry.tracksId;
        }
    }
}

function clearTrack(id) {
    if (pointsRegistry.hasOwnProperty(id)) {
        for (var i = 0; i < pointsRegistry[id].length; ++i) {
            map.removeMapItem(pointsRegistry[id][i]);
        }
        delete pointsRegistry.id;
    }

    if (flightTracksRegistry.hasOwnProperty(id)) {
        map.removeMapItem(flightTracksRegistry[id]);
        delete flightTracksRegistry.tracksId;
    }
}
