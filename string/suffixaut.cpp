#define MAXN 250000

struct state_t {
	int len, link;
	map< char, int > next;

    bool clone;
    int first_pos;
    vector<int> inv_link;
    
    int cnt, nxt;
};

int sz, last;
state_t state[2*MAXN];

void automata_init() {
	sz = last = 0;
	state[0].len = 0;
	state[0].link = -1;
	++sz;
}

void automata_extend(char c) {
	int cur = sz++;
	state[cur].len = state[last].len+1;
    state[cur].first_pos = state[last].len;
    state[cur].cnt = 1;
    int p = last;
    
	for (; p != -1 && !state[p].next.count(c); p = state[p].link) {
		state[p].next[c] = cur;
    }
    
	if (p == -1) {
        state[cur].link = 0;
	} else {
		int q = state[p].next[c];
		if (state[p].len+1 == state[q].len) {
            state[cur].link = q;
		} else {
			int clone = sz++;
			state[clone].len = state[p].len+1;
			state[clone].next = state[q].next;
			state[clone].link = state[q].link;
            state[clone].first_pos = state[q].first_pos;
            state[clone].clone = true;
			for (; p != -1 && state[p].next[c]==q; p=state[p].link) {
				state[p].next[c] = clone;
			}
            state[q].link = state[cur].link = clone;
		}
	}
	last = cur;
}

for (int v = 1; v < sz; ++v)
    state[ state[v].link ].inv_link.push_back(v);

int first[n+1];
memset(first,-1,sizeof(first));
for (int v = 0; v < sz; ++v) {
    state[v].nxt = first[state[v].len];
    first[state[v].len] = v;
}

for (int i = n; i >= 0; --i) {
    for (int u = first[i]; u != -1; u = state[u].nxt) {
        if (state[u].link != -1)
            state[ state[u].link ].cnt += state[u].cnt;
    }
}