#define MAXN 111

int N;
vector< int > gr[MAXN];
int low[MAXN], lbl[MAXN], parent[MAXN];
int dfsnum;
vector< pair<int,int> > brid; // the bridges themselves

void dfs( int u ){
	lbl[u] = low[u] = dfsnum++;
	for( size_t i = 0, sz = gr[u].size(); i < sz; i++ ){
		int v = gr[u][i];
		if( lbl[v] == -1 ){
			parent[v] = u;
			dfs( v );
			if( low[v] > lbl[u] )
				brid.push_back( make_pair(u, v) );
			low[u] = min( low[u], low[v] );
			
			/*
			if( low[u] > low[v] ) low[u] = low[v];
			if( low[v] == lbl[v] )
				brid.push_back( make_pair(u, v) );
			*/
		} else if( v != parent[u] ) low[u] = min( low[u], lbl[v] );
	}
}
