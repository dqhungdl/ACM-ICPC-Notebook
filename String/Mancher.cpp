#include <bits/stdc++.h>
using namespace std;

int nn,n=0,res=0,z[100005];
char s[100005];
string st;

int main()
{
    cin>>nn>>st;
    s[++n]='#';
    for(int i=0;i<st.size();i++)
    {
        s[++n]=st[i];
        s[++n]='#';
    }
    int id=0,r=0;
    for(int i=1;i<=n;i++)
    {
        if(i<=id+r)
        {
            int ii=2*id-i;
            z[i]=min(z[ii],id+r-i);
        }
        while(i-z[i]-1>=1&&i+z[i]+1<=n&&s[i-z[i]-1]==s[i+z[i]+1])
            z[i]++;
        if(i+z[i]>id+r)
        {
            id=i;
            r=z[i];
        }
        res=max(res,z[i]);
    }
    cout<<res;
}
