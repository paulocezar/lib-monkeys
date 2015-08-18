const double pi = acos(-1.0);
const double eps = 1e-9;
const double inf = 1e50;

struct pt;

typedef pair<pt, pt> line;
typedef vector<pt> polygon;

//Comparison
int cmp(double a, double b = 0.0){
	if(a - b > eps) return 1;
	if(b - a > eps) return -1;
	return 0;
}

//Tests if c is between a and b
bool between(double a, double b, double c){
	if(a > b) swap(a, b);
	return cmp(a, c) <= 0 && cmp(c, b) <= 0;
}

//Point structure
struct pt{
	double x, y;
	
	pt(double x = 0.0, double y = 0.0) : x(x), y(y) {}
	
	double len() { return sqrt(x * x + y * y); }
	double len2() { return x * x + y * y; }
	
	pt normalize(){ return (*this)/len(); }
	
	pt operator - (pt p){ return pt(x - p.x, y - p.y); }
	pt operator + (pt p){ return pt(x + p.x, y + p.y); }
	pt operator * (double k) { return pt(x * k, y * k); }
	pt operator / (double k) { return pt(x / k, y / k); }
	
	bool operator < (const pt& p) const{
		if(cmp(x, p.x)) return x > p.x;
		return y < p.y;
	} 
	
	bool operator == (const pt p){
		return (!cmp(x, p.x) && !cmp(y, p.y));
	}
};

double dist(pt a, pt b){ return (a - b).len(); }
double dot(pt a, pt b){ return a.x * b.x + a.y * b.y; }
double cross(pt a, pt b){ return a.x * b.y - a.y * b.x; }

//1 -> right
//0 -> colinear
//1 -> left
int side_sign(pt a, pt b, pt c){
	return cmp(cross(a - c, b - c));
}

//Returns true if c is inside the box delimited by a and b
bool in_box(pt a, pt b, pt c){
	return between(a.x, b.x, c.x) && between(a.y, b.y, c.y);
}
