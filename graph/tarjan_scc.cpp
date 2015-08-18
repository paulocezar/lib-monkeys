#define MAXN 111

int N;

int low[MAXN], lbl[MAXN], dfsnum;
vector<int> gr[MAXN];
bool stkd[MAXN];
stack< int > scc;

void dfs( int u ){
	lbl[u] = low[u] = dfsnum++;
	scc.push( u );
	stkd[u] = true;
	int v;
	for( size_t i = 0, sz = gr[u].size(); i < sz; i++ ){
		v = gr[u][i];
		if( lbl[v] == -1 ) dfs( v );
		if( stkd[v] ) low[u] = min( low[u], low[v] );
	}
	if( low[u] == lbl[u] ){  // new component found..
		while( !scc.empty() && scc.top() != u ){
			// .. with this guys
			stkd[ scc.top() ] = false;
			scc.pop(); 
		}
		scc.pop(); stkd[u] = false;
	}
}
