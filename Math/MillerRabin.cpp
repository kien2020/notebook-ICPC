inline long long pw(long long a, long long b, long long c)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = (i128)ans * a % c;
        a = (i128)a * a % c;
        b >>= 1;
    }
    return ans;
}

inline bool checkComposite(long long n, long long a, long long d, long long s)
{
    a %= n;
    if (a == 0)
        return false;
    long long x = pw(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++)
    {
        x = ((i128)x * x) % n;
        if (x == n - 1)
            return false;
    }
    return true;
}

bool MillerRabin(long long n)
{
    if (n < 2)
        return false;
    int s = 0;
    long long d = n - 1;
    while (d % 2 == 0)
    {
        d >>= 1;
        s++;
    }
    for (long long a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022})
        if (checkComposite(n, a, d, s))
            return false;
    return true;
}
