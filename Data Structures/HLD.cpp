#include <bits/stdc++.h>

using namespace std;

const int nn = 1e5 + 1;

int n, q, cnt, a[nn], pa[nn], d[nn], drt[nn], child[nn], start[nn], node[nn], p[nn];
vector<int> adj[nn];
set<pair<int, int> > s[nn];

void visit(int u)
{
    drt[u] = 0;
    child[u] = 1;
    for(auto v : adj[u])
    {
        if (v == pa[u]) continue;
        pa[v] = u;
        d[v] = d[u] + 1;
        visit(v);
        child[u] += child[v];
        if (child[v] > child[drt[u]]) drt[u] = v;
    }
}

void decomp(int u)
{
    node[p[u]=++cnt] = u;
    if (drt[u])
    {
        start[drt[u]] = start[u];
        decomp(drt[u]);
    }
    for(auto v : adj[u])
        if (!start[v])
        {
            start[v] = v;
            decomp(v);
        }
}

//void update(int u, const int &w)
//{
//    while (!anc(start[u],w))
//    {
//        update(1,1,n,p[start[u]],p[u]);
//        u = f[start[u]][0];
//    }
//    if (w != u) update(1,1,n,p[w]+1,p[u]);
//}
//
//int get(int u, const int &w)
//{
//    int res = 0;
//    while (!anc(start[u],w))
//    {
//        res += get(1,1,n,p[start[u]],p[u]);
//        u = f[start[u]][0];
//    }
//    if (w != u) res += get(1,1,n,p[w]+1,p[u]);
//    return res;
//}

int main()
{
    cin >> n >> q;
    for(int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    visit(1);
    start[1] = 1;
    decomp(1);
    while(q--)
    {
        int i, u;
        cin >> i >> u;
        if (i)
        {
            int res = -1;
            while (u)
            {
                if (!s[start[u]].empty() && (*s[start[u]].begin()).first <= d[u]) res = (*s[start[u]].begin()).second;
                u = pa[start[u]];
            }
            cout << res << "\n";
        }
        else
        {
            a[u] = !a[u];
            if (a[u]) s[start[u]].insert({d[u], u});
            else s[start[u]].erase({d[u], u});
        }
    }
}
