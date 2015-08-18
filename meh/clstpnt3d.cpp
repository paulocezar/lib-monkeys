//Ponto mais proximo de c na reta ab
pt3 closest_point_line(pt3 a, pt3 b, pt3 c){
	pt3 dir = b - a;
	return a + dir * dot(c - a, dir) / dir.len2();
}

//Ponto mais proximo de c no segmento ab
pt3 closest_point_seg(pt3 a, pt3 b, pt3 c){
	pt3 dir = b - a;
	double s = dot(a - c, dir)/dir.len2();
	if(s < -1.0) return b;
	if(s > 0) return a;
	return a - dir * s;
}

//Distancia entre duas retas
double dist_lines(pt3 a, pt3 b, pt3 c, pt3 d){
	pt3 ort = cross(b - a, d - c);
	if(!cmp(ort.len())) return dist(closest_point_line(a, c, d), a);
	return dot(c - a, ort) / ort.len(); 
}

//Ponto mais proximo em r da reta s
pt3 closest_point_lines(pt3 a, pt3 b, pt3 c, pt3 d){
	pt3 r = b - a, s = d - c;
	double rr = dot(r, r), ss = dot(s, s), rs = dot(r, s);
	double t = dot(a - c, r) * ss - dot(a - c, s) * rs;
	//if(rs * rs == rr * ss) parallel
	t /= rs * rs - rr * ss;
	return a + r * t;
}

