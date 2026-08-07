int n, a[N], b[N], flow[N], delta[N], ans;
 
inline void solve()
{
    cin >> n;
    for (int x = 0; x < n; x++)
    {
        cin >> a[x];
    }
    for (int x = 0; x < n; x++)
    {
        cin >> b[x];
    }
    flow[0] = 0;
    delta[0] = b[0] - a[0];
    for (int x = 1; x < n; x++)
    {
        flow[x] = flow[x - 1] + delta[x - 1];
        delta[x] = b[x] - a[x];
    }
    sort(flow, flow + n);
    ans = 0;
    for (int x = 0; x < n; x++)
    {
        ans += abs(flow[x] - flow[n / 2]);
    }
    cout << ans << "\n";
}
