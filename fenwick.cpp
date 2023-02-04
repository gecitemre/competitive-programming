#include <bits/stdc++.h>

class fenwick {
    private:
        int size;
        long *tree;
    public:
        // add val to the i-th element
        // 1-indexed, i can take values in [1, size]
        void add(long val, int i) {
            while (i <= size) {
                tree[i] += val;
                i += i & (-i);
            }
        }
        fenwick(int size, const long array[]) : size(size){
            tree = new long[size + 1];
            memset(tree, 0, sizeof(long) * (size + 1));
            for (int i = 1; i <= size; i++) {
                add(array[i], i);
            }
        }
        long sum(int i) {
            long res = 0;
            while (i >= 1) {
                res += tree[i];
                i -= i & (-i);
            }
            return res;
        }
        long query(int l, int r) {
            return sum(r) - sum(l - 1);
        }
};