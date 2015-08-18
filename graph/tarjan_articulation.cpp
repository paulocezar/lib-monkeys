#define MAXN 111

int N;

vector< int > gr[ MAXN ];
int low[MAXN], lbl[MAXN], parent[MAXN];
int dfsnum;
int rchild;	// child count of the root 
int root;	// root of the tree 
int arts;	// # of critical vertexes
bool art[MAXN];




void dfs( int u ){
	lbl[u] = low[u] = dfsnum++;
	for( size_t i = 0, sz = gr[u].size(); i < sz; i++ ){
		int v = gr[u][i];
		if( lbl[v] == -1 ){
			parent[v] = u;
			if( u == root ) rchild++;
			dfs( v );
			if( u != root && low[v] >= lbl[u] && !art[u] ) art[u] = true, arts++;
			low[u] = min( low[u], low[v] );
		} else if( v != parent[u] ) low[u] = min( low[u], lbl[v] );
	}
	if( u == root && rchild > 1 ) art[u] = true, arts++;
}
