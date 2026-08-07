vector<int> kmp(string s)
{
    vector<int> ans;
    int n = s.length(), last = 0;
    ans.assign(n, 0);
    ans[0] = 0;
    for (int x = 1; x < n; x++)
    {
        while (s[x] != s[last] && last > 0)
        {
            last = ans[last - 1];
        }
        if (s[x] == s[last])
        {
            last++;
        }
        ans[x] = last;
    }
    return ans;
}
