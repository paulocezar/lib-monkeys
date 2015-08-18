struct seg_info {
	// ...
	seg_info() {}
	void merge (seg_info* left, int key, seg_info* right) {
		// ...
	}
};

struct node_t {
	int key, pr, sz;
	seg_info seg;
	
	node_t *l, *r;
	node_t(int k) : key(k), pr(rand()), sz(0), l(NULL), r(NULL) {}
	/*~node_t(){
		if(l) delete l;
		if(r) delete r;
	}*/	
};

void rotate_right(node_t* &t) {
	node_t *n = t->l;
	t->l = n->r;
	n->r = t;
	t = n;
}

void rotate_left(node_t* &t) {
	node_t *n = t->r;
	t->r = n->l;
	n->l = t;
	t = n;
}

void fix(node_t* t) {
	if(!t) return;
	t->sz = 1 + ((t->l)?(t->l->sz):(0)) + ((t->r)?(t->r->sz):(0));
    seg_info *lseg, *rseg;
    lseg = (t->l)?(&(t->l->seg)):(NULL);
    rseg = (t->r)?(&(t->r->seg)):(NULL);
	t->seg.merge(lseg, t->key, rseg);
}

void insert(node_t* &t, int val, int pos) {
	if (!t) t = new node_t(val);
	else {
		int lsz = ((t->l)?(t->l->sz):(0));
		if (lsz >= pos) insert(t->l, val, pos);
		else insert(t->r, val, pos-lsz-1);
	}
	
	if (t->l && ((t->l->pr) > (t->pr))) rotate_right(t);
	else if (t->r && ((t->r->pr) > (t->pr))) rotate_left(t);
	
	fix(t->l); fix(t->r); fix(t);
}

inline int p(node_t* t) { return (t) ? (t->pr) : (-1); }

void erase(node_t* &t, int pos) {
	if (!t) return;
	
	int lsz = ((t->l)?(t->l->sz):(0));
	if (lsz+1 != pos) {
		if (lsz >= pos) erase(t->l, pos);
		else erase(t->r, pos-lsz-1);
	} else {
		if (!t->l && !t->r) {
			//delete t; 
			t = NULL;
		} else {
			if (p(t->l) < p(t->r)) rotate_left(t);
            else rotate_right(t);
			erase( t, pos );
		}
	}
	
	if (t) { fix(t->l); fix(t->r); } fix(t);
}

void replace(node_t* t, int pos, int val) {
	if (!t) return;
	
	int lsz = ((t->l)?(t->l->sz):(0));
	if (lsz+1 != pos) {
		if (lsz >= pos) replace(t->l, pos, val);
		else replace(t->r, pos-lsz-1, val);
	} else t->key = val;
	
	fix(t);
}

seg_info query(node_t* t, int lo, int hi) {
	
	if (x <= lo && hi <= y) {
		return t->seg;
	}
	int mid = lo + ((t->l)?(t->l->sz):(0)) - 1;
	
	seg_info q1, q2, ans;
	bool f1, f2; f1 = f2 = false;
	if (mid >= lo && mid >= x) { f1 = true; q1 = query(t->l, lo, mid); }
	if (mid+2 <= hi && mid+2 <= y) { f2 = true; q2 = query(t->r, mid+2, hi); }
	
	if (!f1 && !f2) {
		ans.best = ans.suf = ans.pref = ans.sum = t->key;
		return ans;
	}
	
	if (f1 && f2) {
		ans.merge(&q1, t->key, &q2);
	} else if (f1) {
		if (x <= mid+1 && mid+1 <= y) ans.merge(&q1, t->key, NULL);
		else ans = q1;
	} else if (x <= mid+1 && mid+1 <= y) {
        ans.merge(NULL, t->key, &q2);
	} else {
        ans = q2;
    }
	return ans;
}

void merge(node_t &t, node_t* l, node_t* r) {
	if (!l || !r)
		t = l ? l : r;
	else if (l->pr > r->pr)
		merge(l->r, l->r, r), t = l;
	else
		merge(r->l, l, r->l), t = r;
	fix(t);
}

void split (node_t* t, node_t* &l, node_t* &r, int pos, int add = 0) {
	if (!t)
		return void (l = r = 0);
	
    int cur_pos = add + ((t->l)?(t->l->sz):(0));
	if (pos <= cur_pos)
		split(t->l, l, t->l, key, add), r = t;
	else
		split(t->r, t->r, r, key, cur_pos+1), l = t;
	fix(t);
}