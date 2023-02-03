#include <bits/stdc++.h>
using namespace std;

class fenwick {
    private:
        long *tree;
        void add(long val, int x, int size) {
            while (x <= size) {
                tree[x] += val;
                x += x & (-x);
            }
        }
    public:
        fenwick(int size, const long array[]){
            tree = new long[size + 1];
            memset(tree, 0, sizeof(long) * (size + 1));
            for (int i = 1; i <= size; i++) {
                add(array[i], i, size);
            }
        }
        long sum(int x) {
            long res = 0;
            while (x >= 1) {
                res += tree[x];
                x -= x & (-x);
            }
            return res;
        }
        long query(int l, int r) {
            return sum(r) - sum(l - 1);
        }
};

int main() {
    int N;
    cin >> N;
    long heights[N];

}