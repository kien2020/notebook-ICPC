inline long long PollardRho(long long n)
{
    if (n % 2 == 0)
        return 2;
    if (n % 3 == 0)
        return 3;
    if (n % 5 == 0)
        return 5;
    long long c = rnd() % (n - 1) + 1;
    long long s = rnd() % (n - 2) + 2;
    long long t = s;
    long long h = s;
    auto f = [&](long long val)
    {
        return ((i128)val * val + c) % n;
    };
    long long d = 1;
    while (d == 1)
    {
        t = f(t);
        h = f(f(h));
        d = __gcd(abs(t - h), n);
        if (d == n)
        {
            c = rnd() % (n - 1) + 1;
            s = rnd() % (n - 2) + 2;
            t = s;
            h = s;
            d = 1;
        }
    }
    return d;
}

inline void decompose(long long n, vector<long long> &dv)
{
    if (n == 1)
        return;
    if (RabinMiller(n))
    {
        dv.push_back(n);
        return;
    }
    long long d = PollardRho(n);
    decompose(d, dv);
    decompose(n / d, dv);
}
