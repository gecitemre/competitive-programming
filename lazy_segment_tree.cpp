#include <bits/stdc++.h>
using namespace std;

// Segment Tree supports O(logN) point updates and O(logN) range queries.
struct segment_tree_config {
    long empty_value;
    function<long(long, long)> combine;
};

#define left(node) (2 * node)
#define right(node) (2 * node + 1)

class segment_tree
{
private:
    int size;
    long *tree;
    long *lazy;
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
            build(left(node), start, mid, array);
            build(right(node), mid + 1, end, array);
            tree[node] = config.combine(tree[left(node)], tree[right(node)]);
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
                _update(left(node), start, mid, pos, val);
            }
            else
            {
                _update(right(node), mid + 1, end, pos, val);
            }
            tree[node] = config.combine(tree[left(node)], tree[right(node)]);
        }
    }
    long _query(int node, int start, int end, int l, int r)
    {
        if (start > r || end < l)
        {
            return config.empty_value;
        }
        range_update(node, start, end);

        if (start >= l && end <= r)
        {
            return tree[node];
        }
        int mid = (start + end) / 2;
        return config.combine(_query(left(node), start, mid, l, r), _query(right(node), mid + 1, end, l, r));
    }
    void _increase(int node, int start, int end, int l, int r, long val)
    {
        range_update(node, start, end);
        if (start > r || end < l)
        {
            return;
        }
        if (start >= l && end <= r)
        {
            tree[node] += val;
            if (start != end)
            {
                lazy[left(node)] += val;
                lazy[right(node)] += val;
            }
            return;
        }
        int mid = (start + end) / 2;
        _increase(left(node), start, mid, l, r, val);
        _increase(right(node), mid + 1, end, l, r, val);
        tree[node] = config.combine(tree[left(node)], tree[right(node)]);
    }
    void range_update(int node, int start, int end)
    {
        tree[node] += lazy[node];
        if (start != end)
        {
            lazy[left(node)] += lazy[node];
            lazy[right(node)] += lazy[node];
        }
        lazy[node] = 0;
    }

public:
    segment_tree(int size, const long array[], segment_tree_config config) : size(size), config(config)
    {
        tree = new long[4 * size];
        lazy = new long[4 * size];
        memset(lazy, 0, 4 * size * sizeof(long));
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
    void increase(int l, int r, long val)
    {
        _increase(1, 0, size - 1, l, r, val);
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

