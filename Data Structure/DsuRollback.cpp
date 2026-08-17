struct Dsu
{
    vector<int> par, sz;
    vector<array<int, 3>> his;
    Dsu(int n)
    {
        par.assign(n + 1, 0);
        sz.assign(n + 1, 0);
        for (int x = 0; x <= n; x++)
        {
            sz[x] = 1;
            par[x] = x;
        }
    }
    inline int getParent(int i)
    {
        return par[i] == i ? par[i] : getParent(par[i]);
    }
    inline void update(int a, int b)
    {
        a = getParent(a);
        b = getParent(b);
        if (a != b)
        {
            if (sz[a] < sz[b])
                swap(a, b);
            his.push_back({a, b, sz[a]});
            sz[a] += sz[b];
            par[b] = a;
        }
        else
        {
            his.push_back({-1, -1, -1});
        }
    }
    inline bool chkConnect(int a, int b)
    {
        return getParent(a) == getParent(b);
    }
    inline void rollback()
    {
        auto [a, b, s] = his.back();
        his.pop_back();
        if(a == -1) return;
        par[b] = b;
        sz[a] = s;
    }
} dsu(N);

int n, m, ans[N];
pair<int, int> query[N];
map<pair<int, int>, vector<int>> start;
vector<pair<int, int>> have[4 * N];
vector<int> ask[4 * N];
bool isQuery[N];

inline void addQuery(int v, int p, int l, int r)
{
    if (l == r)
    {
        ask[v].push_back(p);
    }
    else
    {
        int m = (l + r) / 2;
        if (p <= m)
        {
            addQuery(2 * v, p, l, m);
        }
        else
        {
            addQuery(2 * v + 1, p, m + 1, r);
        }
    }
}

inline void addEdge(int v, pair<int, int> p, int l, int r, int tl, int tr)
{
    if (tl > tr)
        return;
    if (tl <= l && r <= tr)
    {
        have[v].push_back(p);
    }
    else
    {
        int m = (l + r) / 2;
        addEdge(2 * v, p, l, m, tl, min(m, tr));
        addEdge(2 * v + 1, p, m + 1, r, max(tl, m + 1), tr);
    }
}

inline void dfs(int v, int l, int r)
{
    if (l == r)
    {
        for (auto &[a, b] : have[v])
        {
            dsu.update(a, b);
        }
        for (int i : ask[v])
        {
            ans[i] = dsu.chkConnect(query[i].first, query[i].second);
        }
        for (auto &[a, b] : have[v])
        {
            dsu.rollback();
        }
    }
    else
    {
        int m = (l + r) / 2;
        for (auto &[a, b] : have[v])
        {
            dsu.update(a, b);
        }
        dfs(2 * v, l, m);
        dfs(2 * v + 1, m + 1, r);
        for (auto &[a, b] : have[v])
        {
            dsu.rollback();
        }
    }
}
