typedef complex<long double> Complex;
long double PI = 2 * acos(0.0L);
// Decimation-in-time radix-2 FFT.
//
// Computes in-place the following transform:
//   y[i] = A(w^(dir*i)),
// where
//   w = exp(2pi/N) is N-th complex principal root of unity,
//   A(x) = a[0] + a[1] x + ... + a[n-1] x^{n-1}m
//   dir \in {-1, 1} is FFTs direction (+1=forward, -1=inverse).
//
// Notes:
//   * N must be a power of 2,
//   * scaling by 1/N after inverse FFT is callers resposibility.
void FFT(Complex *a, int N, int dir) {
    int lgN;
    for (lgN = 1; (1 << lgN) < N; lgN++);
    assert((1 << lgN) == N);
    
    for (int i = 0; i < N; ++i) {
        int j = 0;
        for (int k = 0; k < lgN; ++k)
            j |= ((i>>k)&1) << (lgN-1-k);
        if (i < j) swap(a[i], a[j]);
    }
    for (int s = 1; s <= lgN; ++s) {
        int h = 1 << (s - 1);
        Complex t, w, w_m = exp(Complex(0, dir*PI/h));
        for (int k = 0; k < N; k += h+h) {
            w = 1;
            for (int j = 0; j < h; ++j) {
                t = w * a[k+j+h];
                a[k+j+h] = a[k+j] - t;
                a[k+j] += t;
                w *= w_m;
            }
        }
    }
}
