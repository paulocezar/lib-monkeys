pt refer;
bool cmp_angle(pt p1, pt p2){
	int sign = side_sign(refer, p1, p2);
	if(sign) return sign > 0;
	return dist(refer, p1) >= dist(refer, p2);
}

//Algoritmo com ordenacao polar nao pega pontos colineares
polygon convex_hull(polygon p){
	polygon hull;
	
	if(p.size() < 3){ hull = p; return hull; }
	
	refer = *min_element(ALL(p));
	swap(refer, p[0]);
	
	sort(p.begin() + 1, p.end(), cmp_angle);
	p.resize(unique(ALL(p)) - p.begin());
	
	int sz = 0, n = p.size();
	REP(i, n){
		while(sz >= 2 && side_sign(hull[sz - 2], hull[sz - 1], p[i]) <= 0){
			hull.pop_back(); sz--;
		}
		hull.PB(p[i]); sz++;
	}
	return hull;
}
