#include <bits/stdc++.h>

using namespace std;

// Segment Tree. Supports O(logN) point updates and O(logN) range queries.
class lst {
    private:
        int size;
        int *tree;
        int *lazy;
        function<int(int, int)> f;
    public:
        lst(int size, int array[], function<int(int, int)> f) : size(size), f(f) {
            tree = new int[4 * size];
            build(1, 0, size - 1, array);
        }
        void build(int node, int start, int end, int array[]) {
            if (start == end) {
                tree[node] = array[start];
            } else {
                int mid = (start + end) / 2;
                build(2 * node, start, mid, array);
                build(2 * node + 1, mid + 1, end, array);
                tree[node] = f(tree[2 * node], tree[2 * node + 1]);
            }
        }
        void update(int node, int start, int end, int idx, int val) {
            if (start == end) {
                tree[node] = val;
            } else {
                int mid = (start + end) / 2;
                if (start <= idx && idx <= mid) {
                    update(2 * node, start, mid, idx, val);
                } else {
                    update(2 * node + 1, mid + 1, end, idx, val);
                }
                tree[node] = f(tree[2 * node], tree[2 * node + 1]);
            }
        }
        int query(int node, int start, int end, int l, int r) {
            if (start > end || start > r || end < l) {
                return 0; // returning 0 is enough for sum and max queries, but not for min queries it should be INT_MAX
            }
            if (start >= l && end <= r) {
                return tree[node];
            }
            int mid = (start + end) / 2;
            int p1 = query(2 * node, start, mid, l, r);
            int p2 = query(2 * node + 1, mid + 1, end, l, r);
            return f(p1, p2);
        }
};