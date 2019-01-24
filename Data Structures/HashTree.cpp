#include <bits/stdc++.h>

using namespace std;

const int nn = 1e5 + 1;

int n, child[nn], res = 0;
long long pp[nn], f[nn], g[nn];
vector<int> adj[nn];
vector<pair<long long, pair<int, int> > > a[nn];
set<long long> mark;

void visit1(const int &u, const int &p)
{
    child[u] = 1;
    for(auto v : adj[u])
    {
        if (v == p) continue;
        visit1(v, u);
        child[u] += child[v];
        a[u].push_back({f[v], {v, child[v]}});
    }
    sort(a[u].begin(),a[u].end());
    f[u] = adj[u].size();
    for(auto t : a[u]) f[u] = f[u] * pp[t.second.second] + t.first;
}

void visit2(const int &u, const int &p)
{
    if (p)
    {
        long long x = adj[p].size();
        for(auto t : a[p])
            if (t.second.first != u) x = x * pp[t.second.second] + t.first;
        a[u].push_back({x, {p, n-child[u]}});
        sort(a[u].begin(),a[u].end());
    }
    g[u] = adj[u].size();
    for(auto t : a[u]) g[u] = g[u] * pp[t.second.second] + t.first;
    if (adj[u].size() < 4 && mark.find(g[u]) == mark.end())
    {
        mark.insert(g[u]);
        res++;
    }
    for(auto v : adj[u])
    {
        if (v == p) continue;
        visit2(v,u);
    }
}

#define task "718d"

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //srand(time(NULL));
    //freopen(task".inp","r",stdin);
    //freopen(task".out","w",stdout);
    cin >> n;
    pp[0] = 1;
    for(int i = 1; i < n; ++i)
    {
        pp[i] = pp[i-1] * 5;
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    visit1(1,0);
    visit2(1,0);
    cout << res;
}
