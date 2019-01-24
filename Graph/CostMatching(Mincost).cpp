#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
int n,m,S,T,res=0,d[405],Trace[405],f[405][405],c[405][405],cost[405][405];
bool Inqueue[405];
vector<ii> g[405];
queue<int> Q;

bool FordBellman()
{
    for(int i=1;i<=2*n+2;i++)
        d[i]=1e9;
    d[S]=0;
    Inqueue[S]=true;
    Q.push(S);
    while(Q.size()>0)
    {
        int u=Q.front();
        Q.pop();
        Inqueue[u]=false;
        for(int i=0;i<g[u].size();i++)
        {
            int v=g[u][i].first;
            int w=g[u][i].second;
            if(f[u][v]<c[u][v]&&d[v]>d[u]+(f[u][v]>=0?w:-w))
            {
                d[v]=d[u]+(f[u][v]>=0?w:-w);
                Trace[v]=u;
                if(Inqueue[v]==false)
                {
                    Inqueue[v]=true;
                    Q.push(v);
                }
            }
        }
    }
    return (d[T]<1e9);
}

int Enlarge(int delta)
{
    int u=T;
    while(u!=S)
    {
        if(f[Trace[u]][u]<0)
            delta=min(delta,-f[Trace[u]][u]);
        else
            delta=min(delta,c[Trace[u]][u]-f[Trace[u]][u]);
        u=Trace[u];
    }
    u=T;
    while(u!=S)
    {
        f[Trace[u]][u]+=delta;
        f[u][Trace[u]]-=delta;
        u=Trace[u];
    }
    res+=delta*d[T];
    return delta;
}

int main()
{
    ios_base::sync_with_stdio(false);
    //freopen("MATCHCOST.INP","r",stdin);
    cin>>n;
    int u,v,w;
    while(cin>>u>>v>>w)
    {
        g[u].push_back(ii(v+n,w));
        c[u][v+n]=1;
        cost[u][v+n]=w;
        g[v+n].push_back(ii(u,w));
    }
    S=2*n+1;
    T=2*n+2;
    for(int i=1;i<=n;i++)
    {
        g[S].push_back(ii(i,0));
        c[S][i]=1;
        g[i].push_back(ii(S,0));
    }
    for(int i=n+1;i<=2*n;i++)
    {
        g[i].push_back(ii(T,0));
        c[i][T]=1;
        g[T].push_back(ii(i,0));
    }
    int C=n;
    while(FordBellman()==true)
    {
        if(C==0)
            break;
        C-=Enlarge(C);
    }
    cout<<res<<"\n";
    for(int i=1;i<=n;i++)
        for(int j=n+1;j<=2*n;j++)
            if(f[i][j]==1)
                cout<<i<<' '<<j-n<<"\n";
}
