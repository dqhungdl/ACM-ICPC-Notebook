#include <bits/stdc++.h>
using namespace std;

int n,m,cnt=0,res=0,Num[10005],Low[10005];
vector<int> g[10005];
stack<int> S;

void DFS(int u)
{
    Num[u]=Low[u]=++cnt;
    S.push(u);
    for(int i=0;i<g[u].size();i++)
    {
        int v=g[u][i];
        if(Num[v]==0)
        {
            DFS(v);
            Low[u]=min(Low[u],Low[v]);
        }
        else
            Low[u]=min(Low[u],Num[v]);
    }
    if(Num[u]==Low[u])
    {
        res++;
        int v;
        do
        {
            v=S.top();
            S.pop();
            Num[v]=Low[v]=1e9;
        }while(u!=v);
    }
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
    for(int i=1;i<=n;i++)
        if(Num[i]==0)
            DFS(i);
    cout<<res;
}
