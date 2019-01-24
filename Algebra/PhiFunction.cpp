#include <bits/stdc++.h>
using namespace std;

int T,n;

int Mul(int x,int k)
{
    if(k==0)
        return 1;
    int tmp=Mul(x,k/2);
    if(k%2==0)
        return tmp*tmp;
    return tmp*tmp*x;
}

int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n;
        int rs=1;
        for(int i=2;i*i<=n;i++)
        {
            int Count=0;
            while(n%i==0)
            {
                n/=i;
                Count++;
            }
            if(Count>0)
                rs*=(i-1)*Mul(i,Count-1);
        }
        if(n>1)
            rs*=(n-1);
        cout<<rs<<"\n";
    }
}
