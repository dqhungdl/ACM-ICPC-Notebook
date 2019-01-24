#include <bits/stdc++.h>
using namespace std;

int T,top=1,val[2000005],num[2000005],kmp[2000005],tree[2000005][52];
string s;
queue<int> Q;
vector<int> g[2000005];

int Get(char c)
{
    if('a'<=c&&c<='z')
        return c-'a';
    return c-'A'+26;
}

void Add(int id,string str)
{
    int tmp=1;
    for(auto c:str)
    {
        if(tree[tmp][Get(c)]==0)
            tree[tmp][Get(c)]=++top;
        tmp=tree[tmp][Get(c)];
    }
    num[id]=tmp;
}

void BuildAho()
{
    Q.push(1);
    while(Q.size()>0)
    {
        int u=Q.front();
        Q.pop();
        for(int i=0;i<52;i++)
            if(tree[u][i]!=0)
            {
                int v=tree[u][i];
                int tmp=kmp[u];
                while(tmp!=0&&tree[tmp][i]==0)
                    tmp=kmp[tmp];
                if(tmp==0)
                    kmp[v]=1;
                else
                    kmp[v]=tree[tmp][i];
                Q.push(v);
            }
    }
}

void BuildGraph()
{
    for(int i=1;i<=top;i++)
        g[kmp[i]].push_back(i);
}

void DFS(int u)
{
    for(auto v:g[u])
    {
        DFS(v);
        val[u]+=val[v];
    }
}

int main()
{
    cin>>s>>T;
    string str;
    for(int i=1;i<=T;i++)
    {
        cin>>str;
        Add(i,str);
    }
    BuildAho();
    BuildGraph();
    int tmp=1;
    for(auto c:s)
    {
        if(tree[tmp][Get(c)]!=0)
            tmp=tree[tmp][Get(c)];
        else
        {
            tmp=kmp[tmp];
            while(tmp!=0&&tree[tmp][Get(c)]==0)
                tmp=kmp[tmp];
            if(tmp==0)
                tmp=1;
            else
                tmp=tree[tmp][Get(c)];
        }
        val[tmp]++;
    }
    DFS(1);
    for(int i=1;i<=T;i++)
        cout<<(val[num[i]]>0?'Y':'N')<<"\n";
}
