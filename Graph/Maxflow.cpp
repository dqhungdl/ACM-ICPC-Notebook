#include <bits/stdc++.h>
using namespace std;

int n,m,S,T,d[1005],Free[1005],c[1005][1005],f[1005][1005];
queue<int> Q;
vector<int> g[1005];

bool BFS()
{
    for(int i=1;i<=n;i++)
        d[i]=0;
    d[S]=1;
    while(Q.size()>0)
        Q.pop();
    Q.push(S);
    while(Q.size()>0)
    {
        int u=Q.front();
        Q.pop();
        if(u==T)
            return true;
        for(int i=0;i<g[u].size();i++)
        {
            int v=g[u][i];
            if(d[v]==0&&f[u][v]<c[u][v])
            {
                Q.push(v);
                d[v]=d[u]+1;
            }
        }
    }
    return false;
}

int DFS(int u,int minn,int kk)
{
    if(Free[u]==kk)
        return 0;
    Free[u]=kk;
    if(u==T)
        return minn;
    for(int i=0;i<g[u].size();i++)
    {
        int v=g[u][i];
        if(d[v]==d[u]+1&&f[u][v]<c[u][v])
        {
            int tmp=DFS(v,min(minn,c[u][v]-f[u][v]),kk);
            if(tmp>0)
            {
                f[u][v]+=tmp;
                f[v][u]-=tmp;
                return tmp;
            }
        }
    }
    return 0;
}

int main()
{
    cin>>n>>m>>S>>T;
    int u,v,w;
    while(m--)
    {
        cin>>u>>v>>w;
        g[u].push_back(v);
        g[v].push_back(u);
        c[u][v]=w;
    }
    int cnt=0,res=0;
    while(BFS()==true)
    {
        int tmp=DFS(S,1e9,++cnt);
        while(tmp>0)
        {
            res+=tmp;
            tmp=DFS(S,1e9,++cnt);
        }
    }
    cout<<res;
}
