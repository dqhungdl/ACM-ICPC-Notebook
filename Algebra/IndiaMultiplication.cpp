#include <bits/stdc++.h>
using namespace std;

int64_t a,b;

int64_t Mul(int64_t a,int64_t b)
{
    int64_t res=0;
    while(a>0)
    {
        if(a%2==1)
            res+=b;
        a/=2;
        b*=2;
    }
    return res;
}

int main()
{
    cin>>a>>b;
    cout<<Mul(a,b);
}
