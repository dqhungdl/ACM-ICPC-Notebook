#include <bits/stdc++.h>
using namespace std;

const int MAX=1e5+5;
int n,m,cnt=0,Child[MAX],par[MAX],dsu[MAX],label[MAX];
int64_t res;
int sdom[MAX],dom[MAX];
int arr[MAX],rev[MAX];
vector<int> g[MAX],rg[MAX],tree[MAX],bucket[MAX];

int Find(int u,int x=0)
{
    if(u==dsu[u])
        return ((x>0)?-1:u);
    int v=Find(dsu[u],x+1);
    if(v<0)
        return u;
    if(sdom[label[dsu[u]]]<sdom[label[u]])
        label[u]=label[dsu[u]];
    dsu[u]=v;
    return ((x>0)?v:label[u]);
}

void DFS(int u)
{
    arr[u]=++cnt;
    rev[cnt]=u;
    label[cnt]=sdom[cnt]=dsu[cnt]=cnt;
    for(auto v:g[u])
    {
        if(arr[v]==0)
        {
            DFS(v);
            par[arr[v]]=arr[u];
        }
        rg[arr[v]].push_back(arr[u]);
    }
}

void DFSTree(int u,int par)
{
    Child[u]=0;
    for(auto v:tree[u])
        if(v!=par)
        {
            DFSTree(v,u);
            Child[u]+=Child[v]+1;
        }
    if(u!=1)
        res-=Child[u];
}

int main()
{
    cin>>n>>m;
    int u,v;
    while(m--)
    {
        cin>>u>>v;
        g[u].push_back(v);
    }
    DFS(1);
    for(int i=1;i<=n;i++)
        dsu[i]=i;
    for(int u=n;u>=1;u--)
    {
        for(auto v:rg[u])
            sdom[u]=min(sdom[u],sdom[Find(v)]);
        if(u>1)
            bucket[sdom[u]].push_back(u);
        for(auto v:bucket[u])
        {
            int w=Find(v);
            if(sdom[v]==sdom[w])
                dom[v]=sdom[v];
            else
                dom[v]=w;
        }
        if(u>1)
            dsu[u]=par[u];
    }
    for(int i=2;i<=n;i++)
    {
        if(dom[i]!=sdom[i])
            dom[i]=dom[dom[i]];
        tree[rev[i]].push_back(rev[dom[i]]);
        tree[rev[dom[i]]].push_back(rev[i]);
    }
    res=int64_t(n)*int64_t(n-1)/2;
    DFSTree(1,1);
    cout<<res;
}
