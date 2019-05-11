#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
const int MAX=1005;
int n,m,S,T,Edge=0,d[MAX],Free[MAX],c[MAX*MAX],f[MAX*MAX];
vector<ii> g[MAX];
queue<int> Q;

void AddEdge(int u,int v,int w)
{
    g[u].push_back(ii(v,++Edge));
    c[Edge]=w;
    g[v].push_back(ii(u,++Edge));
}

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
        for(auto tmp:g[u])
        {
            int v=tmp.first;
            int id=tmp.second;
            if(d[v]==0&&f[id]<c[id])
            {
                d[v]=d[u]+1;
                Q.push(v);
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
    for(auto tmp:g[u])
    {
        int v=tmp.first;
        int id=tmp.second;
        if(d[v]==d[u]+1&&f[id]<c[id])
        {
            int tmp=DFS(v,min(minn,c[id]-f[id]),kk);
            if(tmp>0)
            {
                f[id]+=tmp;
                id=(id%2==0?id-1:id+1);
                f[id]-=tmp;
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
        AddEdge(u,v,w);
    }
    int res=0,cnt=0;
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
