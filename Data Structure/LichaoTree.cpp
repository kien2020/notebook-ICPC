struct Line
{
    int a, b;
    Line()
    {
        a = 0;
        b = INF;
    }
    Line(int x, int y)
    {
        a = x;
        b = y;
    }
    double intersect(Line &l)
    {
        return 1.0 * (b - l.b) / (a - l.a);
    }
    long long get(int x)
    {
        return a * x + b;
    }
};

struct Node
{
    Line node;
    Node *le, *ri;
    int div(int l, int r)
    {
        if (l + r > 0)
            return (l + r) / 2;
        else
            return (l + r - 1) / 2;
    }
    void update(Line cur, int l, int r)
    {
        if (l == r)
        {
            if (cur.get(l) < node.get(l))
            {
                node = cur;
            }
        }
        else
        {
            int m = div(l, r);
            if (node.get(m) > cur.get(m))
            {
                swap(node, cur);
            }
            if (cur.a > node.a)
            {
                if (le == NULL)
                    le = new Node();
                le->update(cur, l, m);
            }
            else if (cur.a < node.a)
            {
                if (ri == NULL)
                    ri = new Node();
                ri->update(cur, m + 1, r);
            }
        }
    }
    int get(int pos, int l, int r)
    {
        int val = node.get(pos);
        if (l == r)
        {
            return val;
        }
        else
        {
            int m = div(l, r);
            if (pos <= m)
            {
                if (le != NULL)
                    val = min(le->get(pos, l, m), val);
            }
            else
            {
                if (ri != NULL)
                    val = min(ri->get(pos, m + 1, r), val);
            }
            return val;
        }
    }
} root;
