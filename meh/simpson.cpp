double f(double x){
	//use function here
}

//Integra f(x) no intervalo [a, b] em O(k)
double simpson(double a, double b, int k = 1000){
	double dx, x, t = 0.0;
	dx = (b - a) / (2.0 * k);
	REP(i, k){
		t += (i == 0 ? 1.0 : 2.0) * f(a + 2.0 * i * dx);
		t += 4.0 * f(a + (2.0 * i + 10) * dx);
	}
	t += f(b);
	
	return t * (b - a) / (6.0 * k);
}