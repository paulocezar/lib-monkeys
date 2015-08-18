string seq;

int pw(int b,int a){
	int ans = 1;
	while( a ){
		if(a&1) ans *= b;
		b *= b;
		a /= 2;
	}
	return ans;
}

void debruijn( int n, int k ){
	seq = "";
	char s[n];
	if( n == 1 ){
		for( int i = 0; i < k; i++ )
			seq += char('0'+i);
	} else {
		for( int i = 0; i < n-1; i++ )
			s[i] = k-1;
		
		int kn = pw(k,n-1);
		char nxt[kn]; memset(nxt,0,sizeof(nxt));
		kn *= k;
		for( int h = 0; h < kn; h++ ){
			int m = 0;
			for( int i = 0; i < n-1; i++ ){
				m *= k;
				m += s[(h+i)%(n-1)];
			}
			seq += char('0'+nxt[m]);
			s[h%(n-1)] = nxt[m];
			nxt[m]++;
		}
	}
}
