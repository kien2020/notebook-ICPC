struct Update
{
    int a, b, t;
    Update(int a, int b) : a(a), b(b), t(1) {}
};

struct QueueUndo
{
    Dsu dsu;
    vector<Update> v;
    int bot = 0;
    inline void init(int n)
    {
        dsu.init(n);
    }
    inline void moveBot()
    {
        while (bot < v.size() && v[bot].t == 1)
        {
            bot++;
        }
    }
    inline void add(Update upd)
    {
        v.push_back(upd);
        dsu.update(upd.a, upd.b);
    }
    inline void fixQueue()
    {
        if (v.empty() || v.back().t == 0)
            return;
        vector<Update> t0, t1;
        t1.push_back(v.back());
        dsu.undo();
        v.pop_back();
        while (t1.size() != t0.size() && v.size() > bot)
        {
            if (v.back().t == 0)
            {
                t0.push_back(v.back());
                dsu.undo();
                v.pop_back();
            }
            else
            {
                t1.push_back(v.back());
                dsu.undo();
                v.pop_back();
            }
        }
        reverse(t1.begin(), t1.end());
        reverse(t0.begin(), t0.end());
        for (auto &a : t1)
        {
            add(a);
        }
        for (auto &a : t0)
        {
            add(a);
        }
    }
    inline void reverseQueue()
    {
        bot = 0;
        for (int x = 0; x < v.size(); x++)
        {
            dsu.undo();
        }
        reverse(v.begin(), v.end());
        for (int x = 0; x < v.size(); x++)
        {
            dsu.update(v[x].a, v[x].b);
            v[x].t = 0;
        }
    }
    inline void undo()
    {
        moveBot();
        if (bot == v.size())
        {
            reverseQueue();
        }
        fixQueue();
        dsu.undo();
        // cout << v.back().a << " " << v.back().b << "undo\n";
        v.pop_back();
    }
};
