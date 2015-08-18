// using line sweep to get the minimum distance between a pair of points
template<typename T> T inline SQR( const T &a ){ return a*a; }

double min_dist(vector< pair<double,double> > &point) {

	// Ordena os pontos pelo X que vai ser o eixo percorrido no line sweep
	sort(point, point+N);
	// Comeca a menor distancia com um valor grande o suficiente
	double h = 1e10;
	// Conjunto de pontos ativos, usa uma funcao que ordena eles pelo y
	set< pair<double,double>, comp > active;
	int pactive = 0;
	for (int i = 0; i < N; ++i) {  // Comeca a varrer o eixo X
		
		// Tira os pontos que estavam no conjuntos de ativos e nao tem mais
        // chance de melhorarem a menor distancia
		while (pactive < i && point[pactive].first < point[i].first-h) { 
			active.erase( point[pactive] );
			pactive++;
		}
	
		// Limita os pontos a serem verificados numa box de interesse
		set< pair<double,double> >:: iterator lb,ub;
		lb = active.lower_bound( make_pair( -1000000, point[i].second-h) );
		ub = active.upper_bound( make_pair( +1000000, point[i].second+h) );
	
		// Verifica se algum dos pontos na box melhora a distancia
		while (lb != ub) {
			double hh = sqrt(SQR(point[i].second-(lb->second))
                            + SQR(point[i].first-(lb->first)));
			if (hh < h) h = hh;
			lb++;
		}
		// Adiciona o ponto atual no conjunto de ativos
		active.insert(point[i]);			
	}
	return h;
}

// using line sweep to get the area of the union of rectangles O(n^2)
struct event_t {
	int ax, frm;
	char wut;
	event_t(int a = 0, int b = 0, char c = 0) : ax(a), frm(b), wut(c){}
	bool operator < (const event_t& a) const {
		if (ax != a.ax) return ax < a.ax;
		return wut < a.wut;
	}
};

struct rect_t{
	int x1, x2, y1, y2;
	rect_t(int a = 0, int b = 0, int c = 0, int d = 0) 
        : x1(a), y1(b), x2(c), y2(d) {}
};

int area(vector<rect_t> rect) {
	vector< event_t > eventx, eventy;
	for (size_t i = 0, sz = rect.size(); i < sz; ++i) {
		eventx.pb(event_t(rect[i].x1, i, 0));
		eventx.pb(event_t(rect[i].x2, i, 1));
		eventy.pb(event_t(rect[i].y1, i, 0));
		eventy.pb(event_t(rect[i].y2, i, 1));
	}
	
	sort(eventx.begin(), eventx.end());
	sort(eventy.begin(), eventy.end());
	vector< bool > active(int(rect.size()), false);
	
	active[eventx[0].frm] = true;
	
	int ans = 0;
	for (size_t i = 1, sz = eventx.size(); i < sz; ++i) {
		
		int in = 0;
		int lst = 0;
		for (size_t j = 0, szz = eventy.size(); j < szz; ++j) {
			if (!active[eventy[j].frm]) continue;
			if (in) {
				ans += (eventy[j].ax-lst)*(eventx[i].ax-eventx[i-1].ax);
				lst = eventy[j].ax;
			} else lst = eventy[j].ax;
			
			if (eventy[j].wut) in--;
			else in++;
		}
		
		if (eventx[i].wut) active[eventx[i].frm] = false;
		else active[eventx[i].frm] = true;
	}
	
	return ans;
}
