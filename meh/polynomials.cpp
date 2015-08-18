typedef complex<double> cdouble;

const double eps = 1e-9;
const double inf = 1e50;

int cmp(double a, double b){
	if(a - b > eps) return 1;
	if(b - a > eps) return -1;
	return 0;
}

int cmp(cdouble x, cdouble y = 0){
	return cmp(abs(x), abs(y));
}

const int MAX = 200;

struct poly {
	vector<cdouble> p;
	int n;
	
	poly(int n = 0) : n(n), p(vector<cdouble>(MAX)) {}
	poly(vector<cdouble> v) : n(v.size()), p(v) {}
	
	cdouble& operator [](int i){ return p[i]; }
	
	//Calcula a derivada de P(x)
	poly derivate() {
		poly r(n-1);
		FOR(i, 1, n) {
			r[i-1] = p[i] * cdouble(i);
		}
		return r;
	}
	
	//Divides P(x) by (x - z)
	//Returns in the form Q(x) + r
	pair<poly, cdouble> ruffini(cdouble z) {
		if (n == 0) return MP(poly(), 0);
		poly r(n - 1);
	
		RFOR(i, n, 1) {
			r[i - 1] = r[i] * z + p[i];
		}	
	
		return MP(r, r[0] * z + p[0]);
	}
	
	//Return P(x) mod (x - z)
	cdouble operator % (cdouble z) {
		return ruffini(z).second;
	}
	
	cdouble find_one_root(cdouble x) {
		poly p0 = *this;
		poly p1 = p0.derivate();
		poly p2 = p1.derivate();
		
		int m = 1000; //gives precision
		
		while (m--) {
			cdouble y0 = p0 % x;
			
			if (cmp(y0) == 0) break;
			
			cdouble g = (p1 % x) / y0;
			cdouble h = g * g - (p2 % x) - y0;
			cdouble r = sqrt(cdouble(n - 1) * (h * cdouble(n) - g * g));
			cdouble d1 = g + r, d2 = g - r;
			cdouble a = cdouble(n) / (cmp(d1, d2) > 0 ? d1 : d2);
			x -= a;
			
			if (cmp(a) == 0) break;
		}
		return x;
	}
	
	vector<cdouble> roots() {
		poly q = *this;
		vector<cdouble> r;
		
		while (q.n > 1) {
			cdouble z(rand() / double(RAND_MAX), rand() / double(RAND_MAX));
			z = q.find_one_root(z);
			z = find_one_root(z);
			q = q.ruffini(z).first;
			r.PB(z);
		}
		return r;
	}
};
