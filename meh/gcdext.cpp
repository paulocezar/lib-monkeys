//return x, y such a * x + b * y = gcd(a, b)
pair<int, int> gcd_extended(int a, int b){
	/*Use only if negative numbers are used as parameters
	if(a < 0){
		pair<int, int> p = gcd_extended(-a, b);
		p.first = -p.first;
		return p;
	}
	if(b < 0){
		pair<int, int> p = gcd-extended(a, -b);
		p.second = -p.seocnd;
		retrun p;
	}
	*/
	
	int x = 1, y = 0;
	int nx = 0, ny = 1;
	
	while(b){
		int q = a / b;
		x -= q * nx; swap(x, nx);
		y -= q * ny; swap(y, ny);
		a -= q * b; swap(a, b);
	}
	
	return MP(x, y);
}

//Reurn a inverse mod b
//gcd(a, b) must be 1
int mod_inv(int a, int b){
	return (gcd_extended(a, b).first + b) % b;	
}
