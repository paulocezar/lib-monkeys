//Closest point from c on line ab
pt closest_point(pt a, pt b, pt c){
	if(side_sign(a, b, c) == 0) return c;
	pt dir = b - a;
	return a + (dir * dot(dir, c - a) / dir.len2());
}

//Closest point from c on segment ab
pt closest_point_seg(pt a, pt b, pt c){
	pt close = closest_point(a, b, c);
	if(in_box(a, b, close)) return close;
	return dist(a, c) < dist(b, c) ? a : b;
}
