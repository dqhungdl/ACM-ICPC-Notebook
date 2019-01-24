#include <bits/stdc++.h>
using namespace std;

int T,n,Q,h[1005],P[1005][15];
vector<int> g[1005];

void DFS(int u,int high)
{
    h[u]=high;
    for(int i=0;i<g[u].size();i++)
        DFS(g[u][i],high+1);
}

int LCA(int u,int v)
{
    for(int k=10;k>=0;k--)
        if(h[P[u][k]]>=h[v])
            u=P[u][k];
        else
        if(h[P[v][k]]>=h[u])
            v=P[v][k];
    for(int k=10;k>=0;k--)
        if(P[u][k]!=P[v][k])
        {
            u=P[u][k];
            v=P[v][k];
        }
    while(u!=v)
    {
        u=P[u][0];
        v=P[v][0];
    }
    return u;
}

int main()
{
    cin>>T;
    for(int test=1;test<=T;test++)
    {
        cout<<"Case "<<test<<":\n";
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            h[i]=0;
            P[i][0]=0;
            g[i].clear();
        }
        int deg,x;
        for(int i=1;i<=n;i++)
        {
            cin>>deg;
            while(deg--)
            {
                cin>>x;
                g[i].push_back(x);
                P[x][0]=i;
            }
        }
        for(int i=1;i<=n;i++)
            if(P[i][0]==0)
            {
                DFS(i,1);
                break;
            }
        for(int k=1;k<=10;k++)
            for(int i=1;i<=n;i++)
                P[i][k]=P[P[i][k-1]][k-1];
        cin>>Q;
        int u,v;
        while(Q--)
        {
            cin>>u>>v;
            cout<<LCA(u,v)<<"\n";
        }
    }
}
