//Returns the angle between a-> and a->c
double angle(pt a, pt b, pt c){
	a = a - c, b = b - c;
	return acos(dot(a, b) / (a.len() * b.len()));
}

//Calculates an angle using the cossine's law
double angle(double a, double b, double c){
	return acos((b*b + c*c - a*a)/(2.0*b*c));
}

//Gira a em torno da origem por theta radiano
pt rotate(pt a, double theta){
	double c = cos(theta), s = sin(theta);
	return pt(c * a.x - s * a.y, s * a.x + c * a.y);
}

//Gira b em torno de a por theta radianos
pt rotate(pt a, pt b, double theta){
	return rotate(b - a, theta) + a;
}

//Reflete c en torna de ab
pt reflect(pt a, pt b, pt c){
	double theta = angle(a, b, c);
	return rotate(c, a, -2.0 * theta);
}
