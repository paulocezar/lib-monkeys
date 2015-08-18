//Tests if c is on ab segment
bool point_and_seg(pt a, pt b, pt c){
	if(side_sign(a, b, c)) return false;
	return in_box(a, b, c);
}

//Find the intersection between lines ab and cd

//Normal cases
pt intersect(pt a, pt b, pt c, pt d){
	return a + (b - a) * cross(d - c, a - c) / cross(a - c, b - d);
}

//Use only for DEGENERATE cases or with intersect_seg
bool intersect(pt a, pt b, pt c, pt d, pt& inter){
	double det = cross(a - c, b - d);
	if(!cmp(det)){
		if(side_sign(a, b, c)) return false; //parallel
		inter = pt(inf, inf); return true;   //coincident
	}
	inter = a + (b - a) * cross(d - c, a - c) / det;
	return true; 
}


bool intersect_seg(pt a, pt b, pt c, pt d, pt &inter){
	if(!intersect(a, b, c, d, inter)) return false;
	if(inter == pt(inf, inf)){
		return in_box(a, b, min(c, d)) || in_box(c, d, min(a, b));
	}
	return in_box(a, b, inter) && in_box(c, d, inter);	
}
