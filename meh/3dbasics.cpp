const double pi = acos(-1.0);
const double eps = 1e-9;
const double inf = 1e50;

//Comparison
int cmp(double a, double b = 0.0){
	if(a - b > eps) return 1;
	if(b - a > eps) return -1;
	return 0;
}

struct pt3{
	double x, y, z;
	
	pt3(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}
	
	double len() { return sqrt(x * x + y * y + z * z); }
	double len2() { return x * x + y * y + z * z; }
	
	pt3 operator + (pt3 p) { return pt3(x + p.x, y + p.y, z + p.z); }
	pt3 operator - (pt3 p) { return pt3(x - p.x, y - p.y, z - p.z); }
	pt3 operator * (double k) { return pt3(x * k, y * k, z * k); }
	pt3 operator / (double k) { return pt3(x / k, y / k, z / k); }
};

double dist(pt3 a, pt3 b) { return (b - a).len(); }
double dot(pt3 a, pt3 b) { return a.x*b.x + a.y*b.y + a.z*b.z; }

//Produto Vetorial
pt3 cross(pt3 a, pt3 b) { 
	return pt3(
		a.y * b.z - a.z * b.y, 
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}


