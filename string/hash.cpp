#define MAXN 10000
#define BASE 33ULL
#define VALUE(c) ((c)-'a')

typedef unsigned long long hash;

hash h[MAXN], pw[MAXN];

hash calc_hash(int beg, int end) {
	return h[end] - h[beg]*pw[end-beg];
}

void init() {
	pw[0] = 1ULL;
	for (int i=1; i<MAXN; ++i) {
        pw[i] = pw[i-1]*BASE;
    }
    h[0] = 0ULL;
    for (int j=0; s[j]!='\0'; ++j) {
        h[j+1] = h[j]*BASE + VALUE(s[j]);
    }
}