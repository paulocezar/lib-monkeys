void manacher(strind &ss) {
    string s = "#";
    for (size_t i = 0, sz = ss.size(); i < sz; ++i) {
        s += ss[i];
        s += "#";
    }
    
    int n = int(s.size());
	for (int i = 0; i < n; ++i) ans[i] = 0;
    
    int cur = 1;
	while (cur < n) {
        
        while ((cur > ans[cur])
            && (cur+ans[cur]+1 < n)
            && (s[cur-ans[cur]-1] == s[cur+ans[cur]+1])) ans[cur]++;
		
		int j = 1;
		while ((cur+j < n) && (j < ans[cur]-ans[cur-j])) {
            ans[cur+j] = ans[cur-j];
            j++;
        }
        
        if (cur+j < n)
            ans[cur+j] = ans[cur]-j;
        cur += j;
	}
}
