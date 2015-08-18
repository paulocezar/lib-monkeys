vector< int > gr[MAXN];

int depth[MAXN], parent[MAXN], treesz[MAXN];
int chain[MAXN], chainpos[MAXN], chainleader[MAXN];

int N, cur_chain, pos;

void explore(int u) {
	int v;
	treesz[u] = 1;
	for (size_t i = 0, sz = gr[u].size(); i < sz; ++i) {
		v = gr[u][i];
        if (parent[ v ] == -1) {
			parent[ v ] = u;
			depth[ v ] = depth[ u ]+1;
			explore(v);
			treesz[ u ] += treesz[ v ];
		}
	}
}

void decompose(int u, bool light = true) {
	if (light) {
		++cur_chain;
		chainleader[ cur_chain ] = u;
	}
	
	chain[ u ] = cur_chain;
	chainpos[ u ] = pos++;
	
	int v, ind = -1, mx = -1;
	for( size_t i = 0, sz = gr[u].size(); i < sz; i++ ){
		v = gr[u][i];
        if (parent[ v ] == u && (mx == -1 || treesz[mx] < treesz[v]))
			mx = v, ind = i;
	}
	
	if (mx != -1) {
		decompose(mx, false);
	}
	
	for (size_t i = 0, sz = gr[u].size(); i < sz; ++i) {
		v = gr[u][i];
        if (parent[ v ] == u && v != mx) {
			decompose( v );
		}
	}		
}

int lca(int u, int v) {
	while (chain[u] != chain[v]) {
		if (depth[ chainleader[chain[u]] ] < depth[ chainleader[chain[v]] ])
			v = parent[ chainleader[ chain[v] ] ];
		else
			u = parent[ chainleader[ chain[u] ] ];
	}
	if (depth[u] < depth[v]) return u;
	return v;
}
