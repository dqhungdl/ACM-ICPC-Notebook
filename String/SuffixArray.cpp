#include <bits/stdc++.h>
using namespace std;

int n,mul,ra[100005],rb[100005],sa[100005];
char s[100005];

bool cmp(int x1,int x2)
{
    if(ra[x1]==ra[x2])
        return ra[x1+mul]<ra[x2+mul];
    return ra[x1]<ra[x2];
}

int main()
{
    cin>>s+1;
    n=strlen(s+1);
    for(int i=1;i<=n;i++)
    {
        sa[i]=i;
        ra[i]=s[i];
    }
    for(mul=1;mul<=n;mul*=2)
    {
        sort(sa+1,sa+n+1,cmp);
        for(int i=1;i<=n;i++)
            rb[sa[i]]=rb[sa[i-1]]+cmp(sa[i-1],sa[i]);
        for(int i=1;i<=n;i++)
            ra[i]=rb[i];
        if(ra[sa[n]]==n)
            break;
    }
    for(int i=1;i<=n;i++)
        cout<<sa[i]-1<<"\n";
}
