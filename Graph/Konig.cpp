#include <bits/stdc++.h>
using namespace std;

int m,n,k,Free[200005],rs[200005];
bool Choose[200005];
vector<int> rs1,rs2,g[200005];
queue<int> Q;

bool DFS(int u,int kk)
{
    if(Free[u]==kk)
        return false;
    Free[u]=kk;
    for(int i=0;i<g[u].size();i++)
        if(rs[g[u][i]]==0||DFS(rs[g[u][i]],kk)==true)
        {
            rs[g[u][i]]=u;
            rs[u]=g[u][i];
            return true;
        }
    return false;
}
void Konig()
{
    for(int i=1;i<=m+n;i++)
        if(rs[i]==0)
            Q.push(i);
    while(Q.size()>0)
    {
        int u=Q.front();
        Q.pop();
        for(int i=0;i<g[u].size();i++)
            if(Choose[g[u][i]]==false)
            {
                Choose[g[u][i]]=true;
                Q.push(rs[g[u][i]]);
            }
    }
    for(int i=1;i<=m;i++)
        if(rs[i]>0&&Choose[i]==false&&Choose[rs[i]]==false)
            Choose[i]=true;
    for(int i=1;i<=m;i++)
        if(Choose[i]==true)
            rs1.push_back(i);
    for(int i=m+1;i<=m+n;i++)
        if(Choose[i]==true)
            rs2.push_back(i-m);
    cout<<rs1.size()<<' '<<rs2.size()<<"\n";
    for(int i=0;i<rs1.size();i++)
        cout<<rs1[i]<<' ';
    for(int i=0;i<rs2.size();i++)
        cout<<rs2[i]<<' ';
}

int main()
{
    cin>>m>>n>>k;
    int u,v;
    while(k--)
    {
        cin>>u>>v;
        g[u].push_back(v+m);
        g[v+m].push_back(u);
    }
    int cnt=0;
    for(int i=1;i<=m;i++)
        DFS(i,++cnt);
    Konig();
}
