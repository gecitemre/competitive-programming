#include <bits/stdc++.h>

using namespace std;

// Segment Tree with Lazy Propagation (Lazy Segment Tree). Supports O(logN) range updates and O(logN) range queries.
class lst {
    private:
        int size;
        long *tree;
        long *lazy;
        function<long(long, long)> f;
    public:
        lst(int size, long array[], function<long(long, long)> f) : size(size), f(f) {
            tree = new long[4 * size];
            lazy = new long[4 * size];
            build(1, 0, size - 1, array);
        }
        void build(int node, int start, int end, long array[]) {
            if (start == end) {
                tree[node] = array[start];
            } else {
                int mid = (start + end) / 2;
                build(2 * node, start, mid, array);
                build(2 * node + 1, mid + 1, end, array);
                tree[node] = f(tree[2 * node], tree[2 * node + 1]);
            }
        }
        void update(int node, int start, int end, int l, int r, long val) {
            if (lazy[node] != 0) {
                tree[node] += lazy[node];
                if (start != end) {
                    lazy[2 * node] += lazy[node];
                    lazy[2 * node + 1] += lazy[node];
                }
                lazy[node] = 0;
            }
            if (start > end || start > r || end < l) {
                return;
            }
            if (start >= l && end <= r) {
                tree[node] += val;
                if (start != end) {
                    lazy[2 * node] += val;
                    lazy[2 * node + 1] += val;
                }
                return;
            }
            int mid = (start + end) / 2;
            update(2 * node, start, mid, l, r, val);
            update(2 * node + 1, mid + 1, end, l, r, val);
            tree[node] = f(tree[2 * node], tree[2 * node + 1]);
        }
        long query(int node, int start, int end, int l, int r) {
            if (start > end || start > r || end < l) {
                return 0; // returning 0 is ok for sum and max queries, but not for min queries it should be INT_MAX
            }
            if (lazy[node] != 0) {
                tree[node] += lazy[node];
                if (start != end) {
                    lazy[2 * node] += lazy[node];
                    lazy[2 * node + 1] += lazy[node];
                }
                lazy[node] = 0;
            }
            if (start >= l && end <= r) {
                return tree[node];
            }
            int mid = (start + end) / 2;
            return f(query(2 * node, start, mid, l, r), query(2 * node + 1, mid + 1, end, l, r));
        }
};
