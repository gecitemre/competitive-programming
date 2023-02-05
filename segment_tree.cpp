#include <bits/stdc++.h>
using namespace std;

// Segment Tree supports O(logN) point updates and O(logN) range queries.

class min_lst
{
private:
    int size;
    long *tree;
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
            tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        }
    }
    long _query(int node, int start, int end, int l, int r)
    {
        if (start > r || end < l)
        {
            return LONG_MAX;
        }

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

// for other types of segment trees, small changes will be required, such as using another funtion instead of min and changing default return value.
// Note: This code is not tested.