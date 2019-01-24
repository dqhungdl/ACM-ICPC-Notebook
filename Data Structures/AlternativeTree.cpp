#include <bits/stdc++.h>

using namespace std;

const int nn = 1e5 + 1;

int n, m, l, q, t, res, test,
    a[nn], tin[nn], tout[nn], mark[nn], terror[nn], f[nn][20];
vector<int> adj[nn], _adj[nn];
stack<int> stk;

void visit(const int &u)
{
    tin[u] = ++t;
    for(int i = 1; i <= l; ++i) f[u][i] = f[f[u][i-1]][i-1];
    for(auto v : adj[u])
        if (v != f[u][0])
        {
            f[v][0] = u;
            visit(v);
        }
    tout[u] = ++t;
}

bool anc(const int &u, const int &v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (anc(u,v)) return u;
    if (anc(v,u)) return v;
    for(int i = l; i >= 0; --i)
        if (!anc(f[u][i],v)) u = f[u][i];
    return f[u][0];
}

bool check(const int &u)
{
    int cnt = 0;
    for(auto v : _adj[u])
    {
        if (terror[u] == test)
        {
            if (terror[v] == test && f[v][0] == u)
            {
                res = -1;
                return -1;
            }
            bool x = check(v);
            if (res == -1) return -1;
            res += x;
        }
        else
        {
            bool x = check(v);
            if (res == -1) return -1;
            cnt += x;
        }
    }
    if (terror[u] == test || cnt == 1) return 1;
    if (cnt > 1) res++;
    return 0;
}

bool cmp(const int &x, const int &y)
{
    return tin[x] < tin[y];
}

void query()
{
    cin >> m;
    for(int i = 1; i <= m; ++i)
    {
        cin >> a[i];
        _adj[a[i]].clear();
        mark[a[i]] = test;
        terror[a[i]] = test;
    }
    sort(a+1,a+m+1,cmp);
    for(int i = 1; i < m; ++i)
    {
        int tmp = lca(a[i],a[i+1]);
        if (mark[tmp] < test)
        {
            mark[tmp] = test;
            a[++m] = tmp;
            _adj[tmp].clear();
        }
    }
    sort(a+1,a+m+1,cmp);
    while (!stk.empty()) stk.pop();
    stk.push(a[1]);
    for(int i = 2; i <= m; ++i)
    {
        while (tout[stk.top()] < tout[a[i]]) stk.pop();
        _adj[stk.top()].push_back(a[i]);
        stk.push(a[i]);
    }
    res = 0;
    check(a[1]);
    cout << res << "\n";
}

int main()
{
    freopen("chk.inp", "r", stdin);
    cin >> n;
    for(int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    l = log2(n);
    cin >> q;
    f[1][0] = 1;
    visit(1);
    for(test = 1; test <= q; ++test) query();
}

