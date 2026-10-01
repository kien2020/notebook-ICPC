vector<int> zfunction(vector<int> s)
{
    int n = s.size(), l = 0, r = 0;
    vector<int> z(n);
    z[0] = 0;
    for (int x = 1; x < n; x++)
    {
        int cr = min(max(0, r - x + 1), z[x - l]);
        while (x + cr < n && s[x + cr] == s[cr])
        {
            cr++;
        }
        z[x] = cr;
        if (x + cr < r)
        {
            l = x;
            r = x + cr - 1;
        }
    }
    return z;
}
