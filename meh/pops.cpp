//Representa um plano
//p eh um ponto do plano e n eh a normal
struct plane{
	pt3 n, p;
	plane(pt3 a, pt3 b, pt3 c) { n = cross(b - a, c - a), p = a; }
	//produto misto
	double d() {
		return dot(n, p);
	}
};

//Ponto do plano mais proximo de p
pt3 closest_point_plane(pt3 a, plane p){
	return a - p.n * dot(a - p.p, p.n) / p.n.len2();
}

//Distancia entre ponto e plano
double dist_point_plane(pt3 a, plane p){
	return fabs(dot(a - p.p, p.n) / p.n.len2());
}

//Intersecao de reta e plano
pt3 intersect(pt3 a, pt3 b, plane p){
	pt3 dir = b - a;
	
	if(!cmp(dot(p.n, dir))) return pt3(inf, inf, inf); //reta paralela ao plano
	return a - dir * (dot(a, p.n) - p.d()) / dot(dir, p.n);
}

//Intersecao entre dois planos
pair<pt3, pt3> plane_intersect(plane u, plane v){
	pt3 p1 = u.n * u.d();
	pt3 uv = cross(u.n, v.n);
	pt3 uvu = cross(uv, u.n);
	
	if(!cmp(dot(v.n, uvu))) return MP(pt3(inf, inf), pt3(inf, inf)); //planos paralelos
	pt3 p2 = p1 - uvu * (dot(v.n, p1) - v.d()) / dot(v.n, uvu);
	return MP(p2, p2 + uv);
}
