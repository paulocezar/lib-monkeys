void prefixfunction(string S) {
    int N = SIZE(S);
    
    p[0] = p[1] = 0;
    FOR(i, 2, N) {
        int j = p[i-1];
        while (S[i-1] != S[j]) {
            if (j == 0) { j = -1; break; }
            j = p[j];
        }
        p[i] = ++j; 
    }
}
