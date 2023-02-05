#include <bits/stdc++.h>
using namespace std;

// Segment Tree with Lazy Propagation (Lazy Segment Tree) supports O(logN) range updates and O(logN) range queries.

class min_lst
{
private:
    int size;
    long *tree;
    long *lazy;
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
            tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        }
    }
    void _increase(int node, int start, int end, int l, int r, long val)
    {
        lazy_update(node, start, end);
        if (start > r || end < l)
        {
            return;
        }
        if (start >= l && end <= r)
        {
            tree[node] += val;
            if (start != end)
            {
                lazy[2 * node] += val;
                lazy[2 * node + 1] += val;
            }
            return;
        }
        int mid = (start + end) / 2;
        _increase(2 * node, start, mid, l, r, val);
        _increase(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
    void lazy_update(int node, int start, int end)
    {
        tree[node] += lazy[node];
        if (start != end)
        {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    long _query(int node, int start, int end, int l, int r)
    {
        if (start > r || end < l)
        {
            return LONG_MAX;
        }

        lazy_update(node, start, end);

        if (start >= l && end <= r)
        {
            return tree[node];
        }
        int mid = (start + end) / 2;
        return min(_query(2 * node, start, mid, l, r), _query(2 * node + 1, mid + 1, end, l, r));
    }

public:
    min_lst(int size, const long array[]) : size(size)
    {
        tree = new long[4 * size + 1];
        lazy = new long[4 * size + 1];
        memset(lazy, 0, (4 * size + 1) * sizeof(long));
        build(1, 0, size - 1, array);
    }
    void increase(int l, int r, long val)
    {
        _increase(1, 0, size - 1, l, r, val);
    }
    long query(int l, int r)
    {
        return _query(1, 0, size - 1, l, r);
    }
};

class max_lst
{
private:
    int size;
    long *tree;
    long *lazy;
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
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }
    void _increase(int node, int start, int end, int l, int r, long val)
    {
        lazy_update(node, start, end);
        if (start > r || end < l)
        {
            return;
        }
        if (start >= l && end <= r)
        {
            tree[node] += val;
            if (start != end)
            {
                lazy[2 * node] += val;
                lazy[2 * node + 1] += val;
            }
            return;
        }
        int mid = (start + end) / 2;
        _increase(2 * node, start, mid, l, r, val);
        _increase(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }
    long _query(int node, int start, int end, int l, int r)
    {
        if (start > r || end < l)
        {
            return LONG_MIN;
        }

        lazy_update(node, start, end);

        if (start >= l && end <= r)
        {
            return tree[node];
        }
        int mid = (start + end) / 2;
        return max(_query(2 * node, start, mid, l, r), _query(2 * node + 1, mid + 1, end, l, r));
    }
    void lazy_update(int node, int start, int end)
    {
        tree[node] += lazy[node];
        if (start != end)
        {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

public:
    max_lst(int size, const long array[]) : size(size)
    {
        tree = new long[4 * size + 1];
        lazy = new long[4 * size + 1];
        memset(lazy, 0, (4 * size + 1) * sizeof(long));
        build(1, 0, size - 1, array);
    }
    void increase(int l, int r, long val)
    {
        _increase(1, 0, size - 1, l, r, val);
    }
    long query(int l, int r)
    {
        return _query(1, 0, size - 1, l, r);
    }
};

class sum_lst
{
private:
    int size;
    long *tree;
    long *lazy;
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
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
    void _increase(int node, int start, int end, int l, int r, long val)
    {
        lazy_update(node, start, end);
        if (start > r || end < l)
        {
            return;
        }
        if (start >= l && end <= r)
        {
            tree[node] += val * (end - start + 1);
            if (start != end)
            {
                lazy[2 * node] += val;
                lazy[2 * node + 1] += val;
            }
            return;
        }
        int mid = (start + end) / 2;
        _increase(2 * node, start, mid, l, r, val);
        _increase(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    void lazy_update(int node, int start, int end)
    {
        tree[node] += lazy[node] * (end - start + 1);
        if (start != end)
        {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    long _query(int node, int start, int end, int l, int r)
    {
        if (start > r || end < l)
        {
            return 0;
        }
        lazy_update(node, start, end);


        if (start >= l && end <= r)
        {
            return tree[node];
        }
        int mid = (start + end) / 2;
        return _query(2 * node, start, mid, l, r) + _query(2 * node + 1, mid + 1, end, l, r);
    }

public:
    sum_lst(int size, const long array[]) : size(size)
    {
        tree = new long[4 * size + 1];
        lazy = new long[4 * size + 1];
        memset(lazy, 0, (4 * size + 1) * sizeof(long));
        build(1, 0, size - 1, array);
    }
    void increase(int l, int r, long val)
    {
        _increase(1, 0, size - 1, l, r, val);
    }
    long query(int l, int r)
    {
        return _query(1, 0, size - 1, l, r);
    }
};