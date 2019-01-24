//Calculate c(i or j) = a(i) * b(j)

#include <bits/stdc++.h>
using namespace std;

ifstream fi("LONCON.INP");
ofstream fo("LONCON.OUT");

int n,m,sum=0,a[2100000],b[2100000],fa[2100000],fb[2100000];
bool Free[25];
vector<int> g[25];

int GetBit(int x,int k)
{
    return (x>>k)&1;
}

void Try(int i)
{
    for(int j=0;j<=1;j++)
    {
        if(j==1)
        {
            for(int t=0;t<g[i].size();t++)
                if(Free[g[i][t]]==true)
                    return;
            sum+=1<<i;
            Free[i]=true;
        }
        if(i==n-1)
        {
            a[sum]=1;
            b[sum]=1;
            fa[sum]=1;
            fb[sum]=1;
        }
        else
            Try(i+1);
        if(j==1)
        {
            sum-=1<<i;
            Free[i]=false;
        }
    }
}

int main()
{
    fi>>n>>m;
    int u,v;
    while(m--)
    {
        fi>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    Try(0);
    for(int i=0;i<n;i++)
        for(int j=0;j<(1<<n);j++)
            if(GetBit(j,i)==1)
            {
                fa[j]+=fa[j-(1<<i)];
                fb[j]+=fb[j-(1<<i)];
            }
    int res=1;
    while(a[(1<<n)-1]==0)
    {
        res++;
        for(int i=0;i<(1<<n);i++)
        {
            fa[i]*=fb[i];
            a[i]=fa[i];
        }
        for(int i=0;i<n;i++)
            for(int j=0;j<(1<<n);j++)
                if(GetBit(j,i)==1)
                    a[j]-=a[j-(1<<i)];
    }
    fo<<res;
}
