struct node_t {
	bool root;
	node_t* failure;
	node_t* n_output;
	map< char, node_t* > child;
	vector< int > output;
		
	node_t() { 
		root = false;
		n_output = NULL;
		failure = NULL;
		child.clear();
		output.clear();
	}
	
	node_t* g(char c) {
		if (!child.count(c)) return (root?(this):(NULL));
		return child[c];
	}
	
	node_t* next(char c) {
		if (g(c) != NULL) return g(c);
		child[c] = failure->next(c);
		return child[c];
	}
	
};

const string alph = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

void add(node_t* prefix_trie, string &s, int id) {
	int i = 0, sz = SIZE(s);
	while (i < sz) {
		if (prefix_trie->g(s[i]) != NULL) prefix_trie = prefix_trie->g(s[i]);
		else break;
		i++;
	}
    
    
	while (i < sz) {
		prefix_trie->child[ s[i] ] = new node_t();
		prefix_trie = prefix_trie->g(s[i]);
		i++;
	}
	prefix_trie->output.PB(id);
}

void init(node_t* root) {
	queue< node_t* > q;
	node_t *r, *s, *state;
	
	for (int i = 0; i < SIZE(alph); ++i) {
		char c = alph[i];
		if ((s=root->g(c)) != root) {
			s->failure = root;
			q.push(s);
		}
	}
	
	while (!q.empty()) {
		r = q.front(); q.pop();
		for (int i = 0; i < SIZE(alph); ++i) {
			char c = alph[i];
			if ((s=(r->g(c))) != NULL) {
				q.push(s);
				state = r->failure;
				
				while (state->g(c) == NULL) state = state->failure;
				state = state->g(c);
				s->failure = state;
				
				s->n_output = (SIZE(state->output) ? (state) : (state->n_output));
			}
		}
	}
}
// add, root->true, init, profit