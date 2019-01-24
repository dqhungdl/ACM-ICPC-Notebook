#include <bits/stdc++.h>
using namespace std;

int m,n,kmp[1000005];
char s1[1000005],s2[1000005];

int main()
{
    cin>>s1+1>>s2+1;
    m=strlen(s1+1);
    n=strlen(s2+1);
    int tmp=0;
    for(int i=2;i<=n;i++)
    {
        while(tmp!=0&&s2[i]!=s2[tmp+1])
            tmp=kmp[tmp];
        if(s2[i]==s2[tmp+1])
            tmp++;
        kmp[i]=tmp;
    }
    tmp=0;
    for(int i=1;i<=m;i++)
    {
        while(tmp!=0&&s1[i]!=s2[tmp+1])
            tmp=kmp[tmp];
        if(s1[i]==s2[tmp+1])
            tmp++;
        if(tmp==n)
            cout<<i-n+1<<' ';
    }
}
