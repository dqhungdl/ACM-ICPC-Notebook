#include <bits/stdc++.h>
using namespace std;

const int MAX=30005;
typedef pair<int,int> ii;
int n,m,cnt=0,res=1,Num[MAX],Low[MAX];
vector<int> g[MAX];
stack<ii> S;

void DFS(int u)
{
    Num[u]=Low[u]=++cnt;
    for(auto v:g[u])
        if(Num[v]==0)
        {
            S.push(ii(u,v));
            DFS(v);
            Low[u]=min(Low[u],Low[v]);
            if(Low[v]>=Num[u])
            {
                int Count=1;
                ii tmp;
                do
                {
                    tmp=S.top();
                    S.pop();
                    Count++;
                }while(tmp!=ii(u,v));
                res=max(res,Count);
            }
        }
        else
            Low[u]=min(Low[u],Num[v]);
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
            DFS(i);
    cout<<res;
}
