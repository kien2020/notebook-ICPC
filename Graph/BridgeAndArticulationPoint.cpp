int n, m, id[N], cid, bridge, arcu, low[N];
vector<int> adj[N];
bool vis[N];

void dfs(int c, int p)
{
    low[c] = cid;
    id[c] = cid++;
    vis[c] = 1;
    int t = 0;
    bool b = 0;
    for (int i : adj[c])
    {
        if (i == p)
            continue;
        if (vis[i])
        {
            low[c] = min(low[c], id[i]);
        }
        else
        {
            dfs(i, c);
            low[c] = min(low[c], low[i]);
            t++;
            if (low[i] == id[i])
            {
                bridge++;
            }
            if (c == p)
            {
                if (t > 1)
                {
                    b = 1;
                }
            }
            else
            {
                if (low[i] >= id[c])
                {
                    b = 1;
                }
            }
        }
    }
    arcu += b;
    // cout << low[c] << " " << id[c] << " " << c << "\n";
}

inline void solve()
{
    cin >> n >> m;
    bridge = 0;
    arcu = 0;
    for (int x = 0; x < m; x++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cid = 0;
    for (int x = 1; x <= n; x++)
    {
        if (vis[x])
            continue;
        dfs(x, x);
    }
    cout << arcu << " " << bridge << "\n";
}
