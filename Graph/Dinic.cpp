struct Edge
{
    int a, b, c, f;
};

struct Dinic
{
    int n;
    vector<Edge> edge;
    vector<vector<int>> adj;
    vector<int> dis, ptr;
    deque<int> q;
    bool bfs(int s, int t)
    {
        for (int x = 0; x <= n; x++)
        {
            dis[x] = -1;
        }
        dis[s] = 0;
        q.push_back(s);
        while (!q.empty())
        {
            int i = q.front();
            q.pop_front();
            for (int id : adj[i])
            {
                int j = edge[id].b;
                if (edge[id].f < edge[id].c && dis[j] == -1)
                {
                    dis[j] = dis[i] + 1;
                    q.push_back(j);
                }
            }
        }
        return dis[t] != -1;
    }
    int dfs(int i, int t, long long v)
    {
        if (v == 0)
        {
            return 0;
        }
        if (i == t)
        {
            return v;
        }
        for (int &x = ptr[i]; x < adj[i].size(); x++)
        {
            int id = adj[i][x];
            if (edge[id].f == edge[id].c)
            {
                continue;
            }
            if (dis[edge[id].b] != dis[edge[id].a] + 1)
            {
                continue;
            }
            int j = dfs(edge[id].b, t, min(v, edge[id].c - edge[id].f));
            if (j == 0)
                continue;
            edge[id].f += j;
            edge[id ^ 1].f -= j;
            return j;
        }
        return 0;
    }
    void addEdge(int a, int b, int c)
    {
        adj[a].push_back(edge.size());
        edge.push_back({a, b, c, 0});
        adj[b].push_back(edge.size());
        edge.push_back({b, a, 0, 0});
    }
    int maxFlow(int s, int t)
    {
        int flow = 0;
        while (bfs(s, t))
        {
            for (int x = 0; x <= n; x++)
            {
                ptr[x] = 0;
            }
            while (long long v = dfs(s, t, INF))
            {
                flow += v;
            }
        }
        return flow;
    }
    vector<Edge> minCut(int s, int t)
    {
        vector<bool> vis(n, 0);
        vector<Edge> ans;
        q.push_back(s);
        while (!q.empty())
        {
            int i = q.front();
            q.pop_front();
            if (vis[i])
                continue;
            vis[i] = 1;
            for (int id : adj[i])
            {
                if (edge[id].f < edge[id].c && !vis[edge[id].b])
                {
                    q.push_back(edge[id].b);
                }
            }
        }
        for (Edge &e : edge)
        {
            if (vis[e.a] && !vis[e.b])
            {
                ans.push_back(e);
            }
        }
        return ans;
    }
    void init(int i)
    {
        n = i;
        adj.assign(n + 1, {});
        dis.assign(n + 1, 0);
        ptr.assign(n + 1, 0);
    }
};
