mt19937 rnd(time(NULL));
 
struct Node
{
    char c;
    int w, s;
    Node *le, *ri;
    Node(char c) : c(c), w(rnd()), le(NULL), ri(NULL), s(1) {};
} *root;
 
int sz(Node *cur)
{
    return cur ? cur->s : 0;
}
 
void prop(Node *cur)
{
    if(!cur) return;
    cur->s = sz(cur->le) + sz(cur->ri) + 1;
}
 
pair<Node *, Node *> split(Node *cur, int num)
{
    if(!cur) return {NULL, NULL};
    prop(cur);
    if (num <= sz(cur->le))
    {
        pair<Node *, Node *> p = split(cur->le, num);
        cur->le = p.second;
        prop(cur);
        return {p.first, cur};
    }
    else
    {
        num -= 1 + sz(cur->le);
        pair<Node *, Node *> p = split(cur->ri, num);
        cur->ri = p.first;
        prop(cur);
        return {cur, p.second};
    }
}
 
Node *merge(Node *le, Node *ri)
{
    if (le == NULL)
        return ri;
    if (ri == NULL)
        return le;
    if (le->w < ri->w)
    {
        le->ri = merge(le->ri, ri);
        prop(le);
        return le;
    }
    else
    {
        ri->le = merge(le, ri->le);
        prop(ri);
        return ri;
    }
}
