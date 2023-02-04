#define MOD 1000000007

long fast_pow(long base, long exp) {
    long res = 1;
    while (exp > 0) {
        if (isOdd(exp)) {
            res = (res * base) % MOD;
        }
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

inline bool isOdd(int i) {
    return i & 1;
}

inline bool isOdd(long i) {
    return i % 2;
}