#include <bits/stdc++.h>
using namespace std;

int n,z[2000005];
string s1,s2,s;

int main()
{
    cin>>s1>>s2;
    s=' '+s2+'*'+s1;
    n=s.size()-1;
    int l=1,r=0;
    for(int i=2;i<=n;i++)
    {
        if(i<=r)
            z[i]=min(z[i-l+1],r-i+1);
        while(i+z[i]<=n&&s[i+z[i]]==s[z[i]+1])
            z[i]++;
        if(r<i+z[i]-1)
        {
            l=i;
            r=i+z[i]-1;
        }
    }
    for(int i=s2.size()+2;i<=n;i++)
        if(z[i]==s2.size())
            cout<<i-s2.size()-1<<' ';
}
