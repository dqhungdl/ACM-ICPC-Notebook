///Nghiem pt la x va y
///Goi p=b/g,q=a/g
///Tap nghiem (x+k*p,y-k*q),k thuoc Z
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
int a,b,c;

ii Diophante(int a,int b)
{
    if(b==0)
        return ii(1,0);
    ii tmp=ii(a/b,a%b);
    ii tmp1=Diophante(b,tmp.second);
    return ii(tmp1.second,tmp1.first-tmp1.second*tmp.first);
}

int main()
{
    cin>>a>>b>>c;
    int g=__gcd(a,b);
    if(c%g!=0)
    {
        cout<<-1;
        return 0;
    }
    ii tmp=Diophante(a,b);
    int x=c/g*tmp.first;
    int y=c/g*tmp.second;
    cout<<x<<' '<<y;
}
