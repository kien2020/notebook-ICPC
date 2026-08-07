struct PersistentSegmentTree
{
    struct Node
    {
        int mx;
        Node *le, *ri;
        Node(int v)
        {
            mx = v;
            le = ri = NULL;
        }
        Node(Node *a, Node *b)
        {
            mx = max(a->mx, b->mx);
            le = a;
            ri = b;
        }
        Node(Node *a)
        {
            mx = a->mx;
            le = a->le;
            ri = a->ri;
        }
        void update(int a, int b)
        {
            mx = max(a, b);
        }
    } *root[N];
    int cid = 1, n;
    Node *build(int l, int r)
    {
        if (l == r)
            return new Node(0);
        else
        {
            int m = (l + r) / 2;
            return new Node(build(l, m), build(m + 1, r));
        }
    }
    void update2(Node *cur, int v, int p, int l, int r)
    {
        if (l == r)
        {
            cur->mx = v;
        }
        else
        {
            int m = (l + r) >> 1;
            if (m >= p)
            {
                update2(cur->le, v, p, l, m);
            }
            else
            {
                update2(cur->ri, v, p, m + 1, r);
            }
            cur->update(cur->ri->mx, cur->le->mx);
        }
    }
    Node *update1(Node *cur, int v, int p, int l, int r)
    {
        if (l == r)
        {
            return new Node(v);
        }
        else
        {
            int m = (l + r) >> 1;
            if (m >= p)
            {
                return (update1(cur->le, v, p, l, m), cur->ri);
            }
            else
            {
                return (cur->le, update1(cur->ri, v, p, m + 1, r));
            }
        }
    }
    int get(Node *cur, int l, int r, int tl, int tr)
    {
        if (tl > tr)
            return 0;
        if (tl <= l && r <= tr)
        {
            return cur->mx;
        }
        else
        {
            int m = (l + r) >> 1;
            return max(get(cur->le, l, m, tl, min(tr, m)), get(cur->ri, m + 1, r, max(tl, m + 1), tr));
        }
    }
    PersistentSegmentTree(int len)
    {
        n = len;
        cid = 1;
        root[0] = build(0, n);
    }
    void update1(int v, int p)
    {
        root[cid] = update1(root[cid - 1], v, p, 0, n);
        cid++;
    }
    void update2(int v, int p)
    {
        update2(root[p], v, p, 0, n);
    }
    int get(int l, int r, int i)
    {
        return get(root[i], 0, n, l, r);
    }
};
