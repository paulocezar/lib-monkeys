//Usa Angles

//Intersection between circunferences
pair<pt, pt> intersect(pt c1, double r1, pt c2, double r2){
	double d = dist(c1, c2);
	if(r1 < r2){
		swap(c1, c2); swap(r1, r2);
	}
	if(cmp(d, r1 + r2) > 0 || cmp(d, r1 - r2) < 0)
		return MP(pt(-inf, -inf), pt(-inf, -inf)); //no intersection
	if(!cmp(d) && !cmp(r1, r2))
		return MP(pt(inf, inf), pt(inf, inf)); //circles are identical
	
	pt p1, p2;
	
	pt v = c2 - c1;
	p1 = c1 + v * r1 / v.len();
	
	if(!cmp(d, r1 + r2) || !cmp(d, r1 - r2)){ //tangents
		return MP(p1, p1);
	}
	
	double theta = angle(r2, d, r1);
	p2 = rotate(c1, p1, theta);
	p1 = rotate(c1, p1, -theta);
	
	return MP(p1, p2);
}
