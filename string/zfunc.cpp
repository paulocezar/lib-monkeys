void zfunction(string S) {
    int N = SIZE(S), a = 0, b = 0;
    REP(i,N) z[i] = N;
    
    FOR(i, 1, N-1) {
        int k = (i<b) ? min(b-i,z[i-a]) : 0;
        while (i+k < N && s[i+k]==s[k]) ++k;
        z[i] = k;
        if (i+k > b) { a = i; b = i+k; }
    }
}
