.pragma library
/*
Google Maps Interface
*/

function moveMapTo(lat,lon) {
    var str = "var center = new google.maps.LatLng("+lat+","+lon+");" +
            "map.panTo(center);"
    return str
}

function changeMapType(type)
{
    var str = "map.setMapTypeId("+ type + ");"
    return str
}

function addMarker(lat,lng,titles,index) {
    var str =
            "var image = '/Images/truck_icon_blue.png';" +
            "var myLatlng = new google.maps.LatLng("+lat+","+lng+");" +
            "markers["+index+"] = new google.maps.Marker({" +
            "position: myLatlng," +
            "map: map," +
            "icon: image," +
            "title: \"Entered Location here\"});" +
            "var contentString = \"Entered Location\";" +
            "infoWindows["+index+"] = new google.maps.InfoWindow({ content: \"<b>"+titles+"  </b></br>\" });" +
            "google.maps.event.addListener(markers["+index+"], 'click', function() {" +
            "infoWindows["+index+"].open(map,markers["+index+"]);});"
    return str
}

function hideMarker(index) {
    var str =
            "markers["+index+"].setMap(null);"
    return str
}

function removeMarker(index) {
    var str =
            "markers["+index+"].setMap(null);" +
            "markers["+index+"] = null;"
    return str
}

function showMarker(index) {
    var str =
            "markers["+index+"].setMap(map);"
    return str
}

function setAnimation(index) {
    var str =
            "for(var i = 0; i < markers.length; i++) {"+
            "   markers[i].setAnimation(null)" +
            "}"+
            "markers["+index+"].setAnimation(google.maps.Animation.BOUNCE)"
    return str
}

function startTrip(driverName, lat, lng) {
    var str =
            "drivingCoordinates.push(new google.maps.LatLng("+lat+","+lng+"));" +
            "drivingPath = new google.maps.Polyline({" +
            "  strokeColor: '#FF0000'," +
            "  strokeOpacity: 1.0," +
            "  strokeWeight: 2" +
            "});" +
            "drivingPath.setPath(drivingCoordinates);" +
            "drivingPath.setMap(map);" +
            "var tripStartMarker = new google.maps.Marker({" +
            "   position: drivingCoordinates[0]," +
            "   map: map" +
            "});"
    return str
}

function closeTrip(driverName) {

}

function addTripPosition(driverName, lat, lng) {
    var str =
            "var indexFound = -1;" +
            "var myLatlng = new google.maps.LatLng("+lat+","+lng+");" +
            "for(var i = 0; i < driverNames.length; i++) {" +
            "    if(driverNames[i] === '"+driverName+"') {" +
            "        indexFound = i;" +
            "        break;" +
            "    }" +
            "}" +
            "if(indexFound === -1) {" +
            "    driverNames.push('"+driverName+"');" +
            "    indexFound = driverNames.length - 1;" +
            "    var polyOptions = {" +
            "        strokeColor: COLORS[indexFound][1]," +
            "        strokeOpacity: 1.0," +
            "        strokeWeight: 3" +
            "    };" +
            "    var image = '/Images/marker_blue.png';" +
            "    var imageHome = '/Images/marker_blue.png';" +
            "    var poly = new google.maps.Polyline(polyOptions);" +
            "    poly.setMap(map);" +
            "    var positions = [];" +
            "    positions.push(myLatlng);" +
            "    poly.setPath(positions);" +
            "    routes.push(poly);" +
            "    routesStartMarkers.push(new google.maps.Marker({" +
            "        position: myLatlng," +
            "        icon: imageHome," +
            "        map: map" +
            "    }));" +
            "    routesCurrentPosMarkers.push(new google.maps.Marker({" +
            "        position: myLatlng," +
            "        icon: image," +
            "        map: map" +
            "    }));" +
            "} else {" +
            "    var currentPath = routes[indexFound].getPath();" +
            "    currentPath.push(myLatlng);" +
            "    routes[indexFound].setPath(currentPath);" +
            "    routesCurrentPosMarkers[indexFound].setPosition(myLatlng);" +
            "    routesCurrentPosMarkers[indexFound].setAnimation(google.maps.Animation.BOUNCE);" +
            "}"
    return str
}

function hideTrackingObject(index) {
    var str =
//            "var polyOptions = {" +
//            "   strokeOpacity: 0.3" +
//            "};" +
//            "routes["+index+"].setOptions(polyOptions);"
            "routes["+index+"].setMap(null);" +
            "routesStartMarkers["+index+"].setMap(null);" +
            "routesCurrentPosMarkers["+index+"].setMap(null);"
    return str;
}

function showTrackingObject(index) {
    var str =
//            "var polyOptions = {" +
//            "   strokeOpacity: 1.0" +
//            "};" +
//            "routes["+index+"].setOptions(polyOptions);"
            "routes["+index+"].setMap(map);" +
            "routesStartMarkers["+index+"].setMap(map);" +
            "routesCurrentPosMarkers["+index+"].setMap(map);" +
            "routesCurrentPosMarkers["+index+"].setAnimation(google.maps.Animation.BOUNCE);"
    return str;
}
