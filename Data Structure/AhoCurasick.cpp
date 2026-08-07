struct Node
{
    int child[26], sufflink, anslink, ans, par;
    char c;
    Node()
    {
        for (int x = 0; x < 26; x++)
        {
            child[x] = -1;
        }
        sufflink = -1;
        anslink = -1;
        ans = -1;
        par = 0;
    }
};
 
struct Trie
{
    vector<Node> node;
    Trie()
    {
        node.reserve(1e6);
        node.push_back(Node());
    }
    int add(int i)
    {
        node.push_back(Node());
        node.back().par = i;
        return node.size() - 1;
    }
    void addString(string s, int i)
    {
        int p = 0;
        for (char h : s)
        {
            int c = h - 'a';
            if (node[p].child[c] == -1)
            {
                node[p].child[c] = add(p);
            }
            p = node[p].child[c];
            node[p].c = h;
        }
        node[p].ans = i;
    }
    void build()
    {
        queue<int> q;
        q.push(0);
        while (!q.empty())
        {
            int i = q.front();
            q.pop();
            if (i == 0)
            {
                node[i].sufflink = -1;
            }
            else
            {
                int j = node[node[i].par].sufflink;
                int c = node[i].c - 'a';
                while (j >= 0)
                {
                    if (node[j].child[c] != -1)
                    {
                        break;
                    }
                    j = node[j].sufflink;
                }
                if (j >= 0)
                {
                    node[i].sufflink = node[j].child[c];
                }
                else
                {
                    node[i].sufflink = 0;
                }
            }
            if (i != 0)
            {
                if (node[node[i].sufflink].ans != -1)
                {
                    node[i].anslink = node[i].sufflink;
                }
                else if (node[node[i].sufflink].anslink != -1)
                {
                    node[i].anslink = node[node[i].sufflink].anslink;
                }
            }
            for (int x = 0; x < 26; x++)
            {
                if (node[i].child[x] != -1)
                    q.push(node[i].child[x]);
            }
        }
    }
    vector<int> get(string &s)
    {
        int p = 0;
        vector<int> ans;
        vector<bool> vis(node.size(), 0);
        for (char h : s)
        {
            int c = h - 'a';
            while (p != -1 && node[p].child[c] == -1)
            {
                p = node[p].sufflink;
            }
            if (p == -1)
            {
                p = 0;
            }
            else
            {
                p = node[p].child[c];
            }
            int q = p;
            if (node[p].ans != -1 && !vis[p])
            {
                ans.push_back(node[p].ans);
                vis[p] = 1;
            }
            while (q >= 0 && node[q].anslink != -1)
            {
                q = node[q].anslink;
                if (vis[q])
                    break;
                vis[q] = 1;
                ans.push_back(node[q].ans);
            }
        }
        return ans;
    }
};
