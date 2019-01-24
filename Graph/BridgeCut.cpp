#include <bits/stdc++.h>
using namespace std;

int n,m,cnt=0,Cut=0,Bridge=0,Num[10005],Low[10005];
vector<int> g[10005];

void DFS(int u,int root)
{
    Num[u]=Low[u]=++cnt;
    int Child=0;
    bool check=false;
    for(int i=0;i<g[u].size();i++)
    {
        int v=g[u][i];
        if(Num[v]==0)
        {
            DFS(v,u);
            Child++;
            if(Low[v]>=Num[v])
                Bridge++;
            if((u!=root&&Low[v]>=Num[u])||(u==root&&Child>=2))
                check=true;
            Low[u]=min(Low[u],Low[v]);
        }
        else
        if(v!=root)
            Low[u]=min(Low[u],Num[v]);
    }
    Cut+=check;
}

int main()
{
    cin>>n>>m;
    int u,v;
    while(m--)
    {
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i=1;i<=n;i++)
        if(Num[i]==0)
            DFS(i,i);
    cout<<Cut<<' '<<Bridge;
}
