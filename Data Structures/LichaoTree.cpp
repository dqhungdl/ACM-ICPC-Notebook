//f[i]=min(f[j]+a[j+1].second*a[i].first)

#include <bits/stdc++.h>
using namespace std;

typedef pair<int64_t,int64_t> ii;
int64_t nn,n=0,F[50005];
ii a[50005],b[50005],tree[4000005];

int64_t f(ii line,int64_t x)
{
    return line.first*x+line.second;
}

void Update(int64_t k,int64_t l,int64_t r,ii line)
{
    int64_t mid=(l+r)/2;
    bool cleft=(f(line,l)<f(tree[k],l));
    bool cmid=(f(line,mid)<f(tree[k],mid));
    if(cmid==true)
        swap(tree[k],line);
    if(r-l==1)
        return;
    if(cleft!=cmid)
        Update(2*k,l,mid,line);
    else
        Update(2*k+1,mid,r,line);
}

int64_t Query(int64_t k,int64_t l,int64_t r,int64_t x)
{
    if(r-l==1)
        return 1e15;
    int64_t mid=(l+r)/2;
    if(x<=mid)
        return min(Query(2*k,l,mid,x),f(tree[k],x));
    return min(Query(2*k+1,mid,r,x),f(tree[k],x));
}

int main()
{
    cin>>nn;
    for(int64_t i=1;i<=nn;i++)
        cin>>b[i].first>>b[i].second;
    sort(b+1,b+nn+1);
    int64_t maxn=0;
    for(int64_t i=nn;i>=1;i--)
        if(maxn<b[i].second)
        {
            maxn=b[i].second;
            a[++n]=b[i];
        }
    reverse(a+1,a+n+1);
    for(int64_t i=1;i<=4e6;i++)
        tree[i]=ii(0,1e15);
    Update(1,0,1e6,ii(a[1].second,0));
    for(int64_t i=1;i<=n;i++)
    {
        F[i]=Query(1,0,1e6,a[i].first);
        Update(1,0,1e6,ii(a[i+1].second,F[i]));
    }
    cout<<F[n];
}
