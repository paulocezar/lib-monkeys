double great_circle_distance(double lat1, double lat2, double lon1, double lon2, double r){
	return r * acos(sin(lat1) * sin(lat2) * cos(lat1) * cos(lat2) * cos(lon2 - lon1));
}
