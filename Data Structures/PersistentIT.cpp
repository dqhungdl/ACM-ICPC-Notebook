#include <bits/stdc++.h>
using namespace std;

struct data
{
    int l,r,s;
};

typedef pair<int,int> ii;
int n,m,T,nNode=0,ver[100005];
ii a[100005];
data tree[2000000];

int Update(int k,int l,int r,int pos)
{
    if(l==r)
    {
        tree[++nNode]={0,0,1};
        return nNode;
    }
    int mid=(l+r)/2,cur=++nNode;
    if(pos<=mid)
    {
        tree[cur].l=Update(tree[k].l,l,mid,pos);
        tree[cur].r=tree[k].r;
    }
    else
    {
        tree[cur].l=tree[k].l;
        tree[cur].r=Update(tree[k].r,mid+1,r,pos);
    }
    tree[cur].s=tree[tree[cur].l].s+tree[tree[cur].r].s;
    return cur;
}

int Query(int k,int l,int r,int L,int R)
{
    if(l>R||L>r)
        return 0;
    if(L<=l&&r<=R)
        return tree[k].s;
    int mid=(l+r)/2;
    return Query(tree[k].l,l,mid,L,R)+Query(tree[k].r,mid+1,r,L,R);
}

int main()
{
    cin>>n>>T;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].first;
        a[i].second=i;
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
        ver[i]=Update(ver[i-1],1,n,a[i].second);
    int L,R,k;
    while(T--)
    {
        cin>>L>>R>>k;
        int rs,l=1,r=n;
        while(l<=r)
        {
            int mid=(l+r)/2;
            if(Query(ver[mid],1,n,L,R)>=k)
            {
                rs=a[mid].first;
                r=mid-1;
            }
            else
                l=mid+1;
        }
        cout<<rs<<"\n";
    }
}
