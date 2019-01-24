#include <bits/stdc++.h>
using namespace std;

ifstream fi("CAPGHEP.INP");
ofstream fo("CAPGHEP.OUT");

const int maxn=1000000;
int n,Start,Finish=0,res=0,Trace[201],X[201],Y[201],fx[201],fy[201],c[201][201];
queue<int> Queue;
bool VisitedX[201],VisitedY[201];

int Get(int i,int j)
{
    return c[i][j]-fx[i]-fy[j];
}

void BFS()
{
    memset(Trace,0,sizeof(Trace));
    while(Queue.size()>0)
        Queue.pop();
    Queue.push(Start);
    while(Queue.size()>0)
    {
        int i=Queue.front();
        Queue.pop();
        for(int j=1;j<=n;j++)
            if(Trace[j]==0&&Get(i,j)==0)
            {
                Trace[j]=i;
                if(Y[j]==0)
                {
                    Finish=j;
                    return;
                }
                Queue.push(Y[j]);
            }
    }
}

void Turn()
{
    memset(VisitedX,false,sizeof(VisitedX));
    memset(VisitedY,false,sizeof(VisitedY));
    VisitedX[Start]=true;
    for(int i=1;i<=n;i++)
        if(Trace[i]!=0)
        {
            VisitedX[Y[i]]=true;
            VisitedY[i]=true;
        }
    int Delta=maxn;
    for(int i=1;i<=n;i++)
        if(VisitedX[i]==true)
            for(int j=1;j<=n;j++)
                if(VisitedY[j]==false)
                    Delta=min(Delta,Get(i,j));
    for(int i=1;i<=n;i++)
    {
        if(VisitedX[i]==true)
            fx[i]+=Delta;
        if(VisitedY[i]==true)
            fy[i]-=Delta;
    }
}

void Enlarge()
{
    while(Finish!=0)
    {
        int x=Trace[Finish];
        int Next=X[x];
        X[x]=Finish;
        Y[Finish]=x;
        Finish=Next;
    }
}

void Enter()
{
    cin>>n;
    int u,v;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            c[i][j]=maxn;
    while(cin>>u>>v)
        cin>>c[u][v];
}

void Process()
{
    for(int i=1;i<=n;i++)
    {
        fx[i]=maxn;
        fy[i]=maxn;
        for(int j=1;j<=n;j++)
            fx[i]=min(fx[i],c[i][j]);
        for(int j=1;j<=n;j++)
            fy[i]=min(fy[i],c[i][j]-fx[i]);
    }
    for(int i=1;i<=n;i++)
    {
        Start=i;
        while(Finish==0)
        {
            BFS();
            if(Finish==0)
                Turn();
        }
        Enlarge();
    }
    for(int i=1;i<=n;i++)
        if(X[i]!=0)
            res+=c[i][X[i]];
    cout<<res<<endl;
    for(int i=1;i<=n;i++)
        if(X[i]!=0)
            cout<<i<<" "<<X[i]<<endl;
}

int main()
{
    Enter();
    Process();
}
