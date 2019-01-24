#include <bits/stdc++.h>
using namespace std;

int m,n,rs[105],Free[105];
vector<int> g[105];

bool DFS(int u,int kk)
{
    if(Free[u]==kk)
        return false;
    Free[u]=kk;
    for(int i=0;i<g[u].size();i++)
        if(rs[g[u][i]]==0||DFS(rs[g[u][i]],kk)==true)
        {
            rs[g[u][i]]=u;
            return true;
        }
    return false;
}

int main()
{
    cin>>m>>n;
    int u,v;
    while(cin>>u>>v)
        g[u].push_back(v);
    int res=0,cnt=0;
    for(int i=1;i<=m;i++)
        res+=DFS(i,++cnt);
    cout<<res<<"\n";
    for(int i=1;i<=n;i++)
        if(rs[i]!=0)
            cout<<rs[i]<<' '<<i<<"\n";
}
