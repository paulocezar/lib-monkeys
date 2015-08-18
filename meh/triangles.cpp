//Uses Intersections
//Closest Point

using namespace std;

double triangle_area(pt a, pt b, pt c){
	return fabs(cross(a - c, b - c) / 2.0);
}

//Encontro das Alturas
pt hcenter(pt a, pt b, pt c){
	pt p1 = closest_point(b, c, a);
	pt p2 = closest_point(a, c, b);
	return intersect(a, p1, b, p2);
}

//Circuncenttro
pt ccenter(pt a, pt b, pt c){
	pt r1 = (b + c) / 2.0;
	pt r2 = (a + c) / 2.0;
	pt s1(r1.x - (c.y - b.y), r1.y + (c.x - b.x));
	pt s2(r2.x - (c.y - a.y), r2.y + (c.x - a.x));
	return intersect(r1, s1, r2, s2);
}

//Encontro das bissetrizes
pt bcenter(pt a, pt b, pt c){
	double s1 = dist(b, c), s2 = dist(a, c), s3 = dist(a, b);
	double rt1 = s2/(s2 + s3), rt2 = s1/(s1 + s3);
	pt p1 = b * rt1 + c * (1.0 - rt1);
	pt p2 = a * rt2 + c * (1.0 - rt2);
	return intersect(a, p1, b, p2);
}
