7.Twosat.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX=8005;
int n,m,cnt=0,col[2*MAX],Num[2*MAX],Low[2*MAX];
vector<int> rs,g[2*MAX];
stack<int> S;

int Not(int u)
{
    if(u<=n)
        return u+n;
    return u-n;
}

void SetColor(int u,int c)
{
    if(col[u]==(c^3)||col[Not(u)]==c)
    {
        cout<<"NO";
        exit(0);
    }
    col[u]=c;
    col[Not(u)]=c^3;
}

void DFS(int u)
{
    Num[u]=Low[u]=++cnt;
    S.push(u);
    for(auto v:g[u])
    {
        if(Num[v]==0)
        {
            DFS(v);
            Low[u]=min(Low[u],Low[v]);
        }
        else
            Low[u]=min(Low[u],Num[v]);
        if(col[v]==2)
            SetColor(u,2);      // False
    }
    if(Num[u]==Low[u])
    {
        if(col[u]==0)
            SetColor(u,1);      // True
        int v;
        do
        {
            v=S.top();
            S.pop();
            Num[v]=Low[v]=1e9;
            SetColor(v,col[u]);
        }while(u!=v);
    }
}

int main()
{
    cin>>m>>n;
    int u,v;
    while(m--)
    {
        cin>>u>>v;
        if(u<0)
            u=-u+n;
        if(v<0)
            v=-v+n;
        g[Not(u)].push_back(v);
        g[Not(v)].push_back(u);
    }
    for(int i=1;i<=2*n;i++)
        if(Num[i]==0)
            DFS(i);
    for(int i=1;i<=n;i++)
        if(col[i]==1)
            rs.push_back(i);
    cout<<"YES\n"<<rs.size()<<"\n";
    for(auto tmp:rs)
        cout<<tmp<<' ';
}
