//Usa line sweep (mais simples e pega pontos colineares)
polygon convex_hull(polygon p){
	polygon hull;
	sort(ALL(p));
	p.resize(unique(ALL(p)) - p.begin());
	//lower hull
	int sz = 0, n = p.size();
	REP(i, n){
		while(sz >= 2 && side_sign(hull[sz - 2], hull[sz - 1], p[i]) <= 0){
			hull.pop_back(); sz--;
		}
		hull.PB(p[i]); sz++;
	}
	//upeer hull
	sort(RALL(p));
	int t = sz + 1;
	RFOR(i, n-2, 0){
		while(sz >= 2 && side_sign(hull[sz - 2], hull[sz - 1], p[i]) <= 0){
			hull.pop_back(); sz--;
		}
		hull.PB(p[i]); sz++;
	}
}
