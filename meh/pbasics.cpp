//Uses Angles
//uses Intersections

double trap(pt a, pt b){ return 0.5 * (b.x - a.x) * (b.y - a.y); }

//Calculates the polygon area (not necessaraly convex)
double area(polygon& p){
	double ret = 0.0;
	int n = p.size();
	REP(i, n){
		ret += trap(p[i], p[(i+1) % n]); 
	}
	return fabs(ret);
}

double perimeter(polygon& p){
	double per = 0.0;
	int n = p.size();
	REP(i, n){
		per += dist(p[i], p[(i+1) % n]);
	}
	return per;
}

//Centro de massa do polygono
pt centroid(polygon& p){
	double a = area(p);
	double xc = 0.0, yc = 0.0;
	int n = p.size();
	REP(i, n){
		int ii = (i+1) % n;
		double r = cross(p[i], p[ii]);
		xc += (p[i].x + p[ii].x) * r;
		yc += (p[i].y + p[ii].y) * r; 
	}
	return pt(xc / (6.0 * a), yc / (6.0 * a));
}

//Tests if polygon is convex
bool is_convex(polygon& p){
	int left = 0, right = 0, side, n = p.size();
	REP(i, n){
		side = side_sign(p[i], p[(i+1) % n], p[(i+2) % n]);
		if(side < 0) left++;
		if(side > 0) right++;
	}
	return !(left && right);
}

//Tests if a point is inside a polygon (not necessaraly convex)
bool point_inside_poly(pt a, polygon p){
	int n = p.size();
	
	REP(i, n){
		if(point_and_seg(p[i], p[(i+1) % n], a)) return true;
	}
	
	REP(i, n){
		p[i] = p[i] - a;
	}
	a = pt(0, 0);
	
	double theta, y;
	bool inter;
	
	do{
		theta = (double)rand()/10000.0;
		inter = false;
		
		REP(i, n){
			p[i] = rotate(p[i], theta);
			if(!cmp(p[i].x) inter = true;
		}
	} 
	while(inter);
	
	REP(i, n){
		if(cmp(p[i].x * p[(i+1) % n].x) < 0){
			double dy = (p[i].y - p[(i+1) % n].y);
			double dx = (p[i].x - p[(i+1) % n].x);
			y = p[(i+1) % n].y - p[(i+1) % n].x * dy / dx;
			
			if(cmp(y) > 0) inter = !inter;
		}
	}
	
	return inter;
}
