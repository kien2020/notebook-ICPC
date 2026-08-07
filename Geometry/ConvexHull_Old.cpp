struct POINT
{
    int x, y;
};
bool XY(POINT a, POINT b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}
bool YX(POINT a, POINT b)
{
    if (a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
}
bool CCW(POINT a, POINT b, POINT c)
{
    return ((a.x - b.x) * (a.y + b.y) + (b.x - c.x) * (b.y + c.y) + (c.x - a.x) * (c.y + a.y)) > 0;
}
vector<POINT> ConvexHullMoreLikeConvexNgu(vector<POINT> v, int n)
{
    vector<POINT> upper;
    vector<POINT> lower;
    sort(v.begin(), v.end(), XY);
    upper.push_back(v[0]);
    lower.push_back(v[n - 1]);
    for (int x = 1; x < n; x++)
    {
        while (upper.size() >= 2 && CCW(upper[upper.size() - 2], upper.back(), v[x]))
        {
            upper.pop_back();
        }
        upper.push_back(v[x]);
    }
    upper.pop_back();
    for (int x = n - 2; x >= 0; x--)
    {
        while (lower.size() >= 2 && CCW(lower[lower.size() - 2], lower.back(), v[x]))
        {
            lower.pop_back();
        }
        lower.push_back(v[x]);
    }
    lower.pop_back();
    vector<POINT> ans;
    int start = lower.size();
    POINT p = upper[0];
    for (int x = lower.size() - 1; x >= 0; x--)
    {
        if (YX(p, lower[x]))
        {
            break;
        }
        start--;
        p = lower[start];
    }
    if(start == lower.size())
    {
        ans.push_back(upper[0]);
        for(int x = lower.size() - 1; x >= 0; x--) ans.push_back(lower[x]);
        for(int x = upper.size() - 1; x > 0; x--) ans.push_back(upper[x]);
        return ans;
    }
    for (int x = start; x >= 0; x--)
        ans.push_back(lower[x]);
    for (int x = upper.size() - 1; x >= 0; x--)
        ans.push_back(upper[x]);
    for (int x = lower.size() - 1; x > start; x--)
        ans.push_back(lower[x]);
    return ans;
}
void solve()
{
    int n; cin >> n;
    vector<POINT> v(n);
    for(int x = 0; x < n; x++)
    {
        POINT p;
        cin >> p.x >> p.y;
        v[x] = p;
    }
    vector<POINT> vec = ConvexHullMoreLikeConvexNgu(v, n);
    cout << vec.size() << "\n";
    // ll ans = 0;
    // for(int x = 0; x < vec.size() - 1; x++) ans += (vec[x].x - vec[x + 1].x)*(vec[x].y + vec[x + 1].y);
    // ans += (vec[vec.size() - 1].x - vec[0].x)*(vec[vec.size() - 1].y + vec[0].y);
    // ans = abs(ans);
    // cout << fixed << setprecision(1) << ans/2.0 << "\n";
    for(POINT p : vec)
        cout << p.x << " " << p.y << "\n";
}
