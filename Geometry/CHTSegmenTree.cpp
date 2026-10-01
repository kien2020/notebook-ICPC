//problem: https://codeforces.com/problemset/problem/1175/G


struct CONVEX_HULL
{
    int cur;
    vector<pair<long long, long long>> v;
    inline void Init()
    {
        cur = 0;
        v.clear();
    }
    inline long long Val(int ind, long long x)
    {
        return v[ind].first * x + v[ind].second;
    }
    inline bool Check(pair<long long, long long> a,
                      pair<long long, long long> b,
                      pair<long long, long long> c)
    {
        double cutl = (double)(b.second - a.second) / (a.first - b.first);
        double cutr = (double)(c.second - a.second) / (a.first - c.first);
        return cutr <= cutl;
    }
    inline void Add(pair<long long, long long> inp)
    {
        while (v.size() > 1 && Check(v[v.size() - 2], v.back(), inp))
        {
            v.pop_back();
        }
        v.push_back(inp);
    }
    inline long long Get(long long val)
    {
        if (v.empty())
        {
            return 1e18;
        }
        while (cur + 1 < v.size() && Val(cur, val) > Val(cur + 1, val))
        {
            cur++;
        }
        return Val(cur, val);
    }
};

struct SEGMENT_TREE
{
    CONVEX_HULL tree[20001 << 2];
    inline void Init()
    {
        for (int i = 0; i < (20001 << 2); ++i)
        {
            tree[i].Init();
        }
    }
    inline void UpdatePoint(int ind, int l, int r, int x, pair<long long, long long> v)
    {
        tree[ind].Add(v);
        if (l == r)
        {
            return;
        }
        int m = (l + r) >> 1;
        if (x <= m)
        {
            UpdatePoint(ind << 1, l, m, x, v);
            return;
        }
        UpdatePoint(ind << 1 | 1, m + 1, r, x, v);
    }
    inline long long GetRange(int ind, int l, int r, int x, int y, long long v)
    {
        if (r < x || y < l)
        {
            return 1e18;
        }
        if (x <= l && r <= y)
        {
            return tree[ind].Get(v);
        }
        int m = (l + r) >> 1;
        return min(GetRange(ind << 1, l, m, x, y, v), GetRange(ind << 1 | 1, m + 1, r, x, y, v));
    }
    inline void UpdateRange(int ind, int l, int r, int x, int y, pair<long long, long long> v)
    {
        if (r < x || y < l)
        {
            return;
        }
        if (x <= l && r <= y)
        {
            tree[ind].Add(v);
            return;
        }
        int m = (l + r) >> 1;
        UpdateRange(ind << 1, l, m, x, y, v);
        UpdateRange(ind << 1 | 1, m + 1, r, x, y, v);
    }
    inline long long GetPoint(int ind, int l, int r, int x)
    {
        if (l == r)
        {
            return tree[ind].Get(x);
        }
        int m = (l + r) >> 1;
        if (x <= m)
        {
            return min(GetPoint(ind << 1, l, m, x), tree[ind].Get(x));
        }
        return min(GetPoint(ind << 1 | 1, m + 1, r, x), tree[ind].Get(x));
    }
};
