int n, m, in[N], low[N], cid, cnt;
bool rem[N];
vector<int> adj[N], cur;

void dfs(int c)
{
    in[c] = low[c] = cid++;
    cur.push_back(c);
    rem[c] = 1;
    for(int i : adj[c])
    {
        if(rem[i])
        {
            low[c] = min(low[c], in[i]);
            continue;
        }
        else if(in[i]) continue;
        dfs(i);
        low[c] = min(low[c], low[i]);
    }
    if(low[c] == in[c]) 
    {
        cnt++;
        while(cur.back() != c) 
        {
            rem[cur.back()] = 0;
            low[cur.back()] = c;
            cur.pop_back();
        }
        cur.pop_back();
        rem[c] = 0;
    }
}

void solve()
{
    cin >> n >> m;
    for(int x = 0; x < m; x++)
    {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
    }
    cnt = 0;
    for(int x = 1; x <= n; x++)
    {
        if(in[x]) continue;
        dfs(x);
    }
    cout << cnt << "\n";
}
