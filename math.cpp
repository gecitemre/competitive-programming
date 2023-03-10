#define MOD 1000000007

long fast_pow(long base, long exp) {
    long res = 1;
    while (exp > 0) {
        if (exp % 2) {
            res = (res * base) % MOD;
        }
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}
