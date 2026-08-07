struct Edge
{
    int a, b, c, w, f;
};

struct MinCostMaxFlow
{
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> dis, pi;
    vector<pair<int, int>> ptr;
    vector<bool> vis;
    int s, t, n;
    MinCostMaxFlow(int n, int s, int t) : n(n), s(s), t(t)
    {
        dis.assign(n + 1, INF);
        adj.assign(n + 1, {});
        vis.assign(n + 1, 0);
        pi.assign(n + 1, INF);
        ptr.assign(n + 1, {-1, -1});
    }
    inline void addEdge(int a, int b, int w, int c)
    {
        edges.push_back({a, b, c, w, 0});
        adj[a].push_back(edges.size() - 1);
        edges.push_back({b, a, 0, -w, 0});
        adj[b].push_back(edges.size() - 1);
    }
    inline void addFlow(int c, int i)
    {
        edges[i].f += c;
        edges[i ^ 1].f -= c;
    }
    inline void bellManFord()
    {
        pi[s] = 0;
        bool chk = 0;
        for (int x = 0; x <= n; x++)
        {
            chk = 0;
            for (auto &e : edges)
            {
                if (e.c > e.f && pi[e.a] != INF && pi[e.a] + e.w < pi[e.b])
                {
                    pi[e.b] = pi[e.a] + e.w;
                    chk = 1;
                }
            }
            if (!chk)
                break;
        }
    }
    inline pair<long long, int> dijkstra()
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for (int x = 0; x <= n; x++)
        {
            dis[x] = INF;
            vis[x] = 0;
            ptr[x] = {-1, -1};
        }
        pq.push({0, s});
        dis[s] = 0;
        while (!pq.empty())
        {
            auto [d, c] = pq.top();
            pq.pop();
            if (vis[c])
                continue;
            vis[c] = 1;
            for (int id : adj[c])
            {
                int i = edges[id].b, w = edges[id].w + pi[c] - pi[i];
                if (edges[id].f != edges[id].c && dis[c] + w < dis[i])
                {
                    dis[i] = dis[c] + w;
                    ptr[i] = {c, id};
                    pq.push({dis[i], i});
                }
            }
        }
        for (int x = 0; x <= n; x++)
        {
            if (dis[x] == INF)
                continue;
            pi[x] += dis[x];
        }
        if (!vis[t])
        {
            return {-1, -1};
        }
        int cur = t, bottleneck = INF, cost = 0;
        while (cur != s)
        {
            auto &[i, id] = ptr[cur];
            bottleneck = min(bottleneck, edges[id].c - edges[id].f);
            cost += edges[id].w;
            cur = i;
        }
        return {bottleneck, cost};
    }
    inline pair<int, int> cal()
    {
        bellManFord();
        int flow = 0, cost = 0, bottleneck = 0, curcost = 0;
        while ((tie(bottleneck, curcost) = dijkstra(), bottleneck) > 0)
        {
            flow += bottleneck;
            cost += curcost * bottleneck;
            int cur = t;
            while (cur != s)
            {
                auto &[i, id] = ptr[cur];
                addFlow(bottleneck, id);
                cur = i;
            }
        }
        return {flow, cost};
    }
    inline int calWithLimit(int k)
    {
        bellManFord();
        int cost = 0, bottleneck = 0, curcost = 0, init = k;
        while (k > 0 && (tie(bottleneck, curcost) = dijkstra(), bottleneck) > 0)
        {
            bottleneck = min(bottleneck, k);
            k -= bottleneck;
            cost += curcost * bottleneck;
            int cur = t;
            while (cur != s)
            {
                auto &[i, id] = ptr[cur];
                addFlow(bottleneck, id);
                cur = i;
            }
            // cout << k << "\n";
        }
        if (k != 0)
            return -1;
        else
            return cost;
    }
};
