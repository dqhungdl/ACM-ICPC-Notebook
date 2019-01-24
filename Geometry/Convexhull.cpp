#include <bits/stdc++.h>
using namespace std;

typedef pair<int64_t,int64_t> ii;
int64_t n,top=2;
ii a[100005],S[100005];

int64_t Area(int64_t u1,int64_t v1,int64_t u2,int64_t v2,int64_t u3,int64_t v3)
{
    return (u2-u1)*(v2+v1)+(u3-u2)*(v3+v2)+(u1-u3)*(v1+v3);
}

bool cmp(ii x1,ii x2)
{
    if(Area(0,0,x1.first,x1.second,x2.first,x2.second)<0)
        return true;
    if(Area(0,0,x1.first,x1.second,x2.first,x2.second)>0)
        return false;
    int64_t d1=x1.first*x1.first+x1.second*x1.second;
    int64_t d2=x2.first*x2.first+x2.second*x2.second;
    return d1<d2;
}

int main()
{
    cin>>n;
    int64_t X,Y=2e9;
    for(int64_t i=1;i<=n;i++)
    {
        cin>>a[i].first>>a[i].second;
        if(Y>a[i].second)
        {
            X=a[i].first;
            Y=a[i].second;
        }
        else
        if(Y==a[i].second)
            X=min(X,a[i].first);
    }
    for(int64_t i=1;i<=n;i++)
    {
        a[i].first-=X;
        a[i].second-=Y;
    }
    sort(a+1,a+n+1,cmp);
    S[1]=a[1];
    S[2]=a[2];
    for(int64_t i=3;i<=n;i++)
    {
        while(top>=2&&Area(S[top-1].first,S[top-1].second,S[top].first,S[top].second,a[i].first,a[i].second)>=0)
            top--;
        S[++top]=a[i];
    }
    int64_t area=0;
    for(int64_t i=3;i<=top;i++)
        area+=abs(Area(S[1].first,S[1].second,S[i-1].first,S[i-1].second,S[i].first,S[i].second));
    cout<<top<<"\n"<<area/2;
    if(area%2==0)
        cout<<".0\n";
    else
        cout<<".5\n";
    for(int64_t i=1;i<=top;i++)
        cout<<S[i].first+X<<' '<<S[i].second+Y<<"\n";
}
