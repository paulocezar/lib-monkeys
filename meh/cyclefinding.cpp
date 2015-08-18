//Brend cycle finding algorithm
//Retorna o tamanho do ciclo

int f(int x) {
	//Returns next sequence term
}

int cycle_find(int x0) {
    int pow = 1, len = 1;
    int t = x0, h = f(x0);
	
	while (t != h) {
		if (len == pow) {
			t = h;
			pow <<= 1;
			len = 0;
		}
		h = f(h);
		len++;
	}
	return len;
}
