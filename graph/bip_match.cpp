/* Maximum Bipartite Matching (Minimum Vertex Cover) on unweighted graph */
#define MAXN 111

int N, M;                // N - # of vertexes on X,  M - # of vertexes on Y
vector< int > gr[MAXN];  // gr[u] -- edges from u in X to v in Y
bool seen[MAXN];		
int m[MAXN], m1[MAXN];   // with whom it's matched

int dfs(int u) {
	if (u < 0) return 1;
	if (seen[u]) return 0;
	seen[u] = true;
	for (size_t i = 0, sz = gr[u].size(); i < sz; ++i) {
		if (dfs(m1[ gr[u][i] ])) {
			m[u] = gr[u][i];
			m1[ gr[u][i] ] = u;
			return 1;
		}
	}
	return 0;
}

int dfsExp(int u) {
	for (int i = 0; i < N; ++i) seen[i] = false;
	return dfs(u);
}


int bipMatch() {
	for (int i = 0; i < N; ++i) m[i] = -1;
	for (int i = 0; i < M; ++i) m1[i] = -1;
	int aug, ans = 0;
	do {
		aug = 0;
		bool first = true;
		for (int i = 0; i < N; ++i) if (m[i] < 0) {
			if (first) aug += dfsExp(i);
			else aug += dfs(i);
			first = false;
		}
		ans += aug;
	} while (aug);
	return ans;
}

/* needed for minium vertex cover.. */
int vx[MAXN], vy[MAXN];
void buildVC( int u ){
	seen[u] = true;
	vx[u] = 0;
	for (size_t w = 0, sz = gr[u].size(); w < sz; ++w)
        if (gr[u][w] != m[u] && vy[ gr[u][w] ] == 0) {
            vy[ gr[u][w] ] = 1;
            if (!seen[ m1[ gr[u][w] ] ]) buildVC(m1[ gr[u][w] ]);
        }
}

// T ~ Unmatched L + reachable using alternating paths
// ANS ..  (L \ T) U ( R intersect T )
for (int i = 0; i < N; ++i) {
    seen[i] = false;
	if (m[i] == -1) vx[i] = 0;		//  T  -- unmatched L
	else vx[i] = 1;					// L \ T -- for now..
}

for (int i = 0; i < M; ++i) vy[i] = 0;	// R  .. ~T -- for now..
for (int i = 0; i < N; ++i) if (vx[i] == 0 && !seen[i]) buildVC(i);
