#include <bits/stdc++.h>
using namespace std;

// Segment Tree supports O(logN) point updates and O(logN) range queries.
struct segment_tree_config {
    long empty_value;
    function<long(long, long)> combine;
};

class segment_tree
{
private:
    int size;
    long *tree;
    segment_tree_config config;
    void build(int node, int start, int end, const long array[])
    {
        if (start == end)
        {
            tree[node] = array[start];
        }
        else
        {
            int mid = (start + end) / 2;
            build(2 * node, start, mid, array);
            build(2 * node + 1, mid + 1, end, array);
            tree[node] = config.combine(tree[2 * node], tree[2 * node + 1]);
        }
    }
    void _update(int node, int start, int end, int pos, long val)
    {
        if (start == end)
        {
            tree[node] = val;
        }
        else
        {
            int mid = (start + end) / 2;
            if (start <= pos && pos <= mid)
            {
                _update(2 * node, start, mid, pos, val);
            }
            else
            {
                _update(2 * node + 1, mid + 1, end, pos, val);
            }
            tree[node] = config.combine(tree[2 * node], tree[2 * node + 1]);
        }
    }
    long _query(int node, int start, int end, int l, int r)
    {
        if (start > r || end < l)
        {
            return config.empty_value;
        }

        if (start >= l && end <= r)
        {
            return tree[node];
        }
        int mid = (start + end) / 2;
        return config.combine(_query(2 * node, start, mid, l, r), _query(2 * node + 1, mid + 1, end, l, r));
    }

public:
    segment_tree(int size, const long array[], segment_tree_config config) : size(size), config(config)
    {
        tree = new long[4 * size];
        build(1, 0, size - 1, array);
    }
    void update(int pos, long val)
    {
        _update(1, 0, size - 1, pos, val);
    }
    long query(int l, int r)
    {
        return _query(1, 0, size - 1, l, r);
    }
};

segment_tree_config sum_config = {
    0,
    [](long a, long b) -> long {
        return a + b;
    }};

segment_tree_config min_config = {
    INT_MAX,
    [](long a, long b) -> long {
        return min(a, b);
    }};

segment_tree_config max_config = {
    INT_MIN,
    [](long a, long b) -> long {
        return max(a, b);
    }};

