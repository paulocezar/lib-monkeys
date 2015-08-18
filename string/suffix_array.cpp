/* O( N log N ) SA build + O( N ) LCP build, #include <cstring> :P */
#define MAXN 100000
string S;
int N, SA[MAXN], LCP[MAXN], rank[MAXN], bucket[CHAR_MAX-CHAR_MIN+1];
char bh[MAXN+1];

void buildSA( bool needLCP = false ){
	int a, c, d, e, f, h, i, j, x;
	int *cnt = LCP;
	memset( bucket, -1, sizeof(bucket) ); 
	for( i = 0; i < N; i++ ){
		j = S[i] - CHAR_MIN;
		rank[i] = bucket[j];
		bucket[j] = i;
	}
	for( a = c = 0; a <= CHAR_MAX-CHAR_MIN; a++ ){
		for( i = bucket[a]; i != -1; i=j ){
			j = rank[i]; rank[i] = c;
			bh[c++] = (i==bucket[a]);
		}
	}
	bh[N] = 1;
	for( i = 0; i < N; i++ )
		SA[ rank[i] ] = i;
	x = 0;
	for( h = 1; h < N; h *= 2 ){
		for( i = 0; i < N; i++ ){
			if( bh[i] & 1 ){
				x = i;
				cnt[x] = 0;
			}
			rank[ SA[i] ] = x;
		}
		d = N-h; e = rank[d];
		rank[d] = e + cnt[e]++;
		bh[rank[d]] |= 2;
		
		i = 0;
		while( i < N ){
			for( j = i; (j == i || !(bh[j] & 1)) && j < N; j++ ){
				d = SA[j]-h;
				if( d >= 0 ){
					e = rank[d]; rank[d] = e + cnt[e]++; bh[rank[d]] |= 2;
				}
			}
			for( j = i; (j == i || !(bh[j] & 1)) && j < N; j++ ){
				d = SA[j]-h;
				if( d >= 0 && (bh[rank[d]] & 2)){
					for( e = rank[d]+1; bh[e] == 2; e++);
					for( f = rank[d]+1; f < e; f++ ) bh[f] &= 1;
				}
			}
			i = j;
		}
		for( i = 0; i < N; i++ ){
			SA[rank[i]] = i;
			if( bh[i] == 2 ) bh[i] = 3;	
		}
	}
	
	if( needLCP ){
		LCP[0] = 0;
		for( i = 0, h = 0; i < N; i++ ){
			e = rank[i];
			if( e > 0 ){
				j = SA[e-1];
				while( ((i+h) < N) && ((j+h) < N) && (S[i+h] == S[j+h]) ) h++;
				LCP[e] = h;
				if( h > 0 ) h--;
			}
		}
	}
}