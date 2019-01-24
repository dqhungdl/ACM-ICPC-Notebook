#include <bits/stdc++.h>
using namespace std;

struct data
{
    int m,n;
    int64_t a[3][3];
};

const int64_t mod=111539786;
int T,n;

data operator *(data A,data B)
{
    data C;
    C.m=A.m;
    C.n=B.n;
    for(int i=1;i<=C.m;i++)
        for(int j=1;j<=C.n;j++)
        {
            C.a[i][j]=0;
            for(int k=1;k<=A.n;k++)
                C.a[i][j]=(C.a[i][j]+A.a[i][k]*B.a[k][j])%mod;
        }
    return C;
}

data Mul(data A,int k)
{
    if(k==1)
        return A;
    data tmp=Mul(A,k/2);
    if(k%2==0)
        return tmp*tmp;
    return tmp*tmp*A;
}

int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n;
        if(n==1)
            cout<<1<<"\n";
        else
        {
            data A,B;
            A.m=2;
            A.n=2;
            A.a[1][1]=0;
            A.a[1][2]=1;
            A.a[2][1]=1;
            A.a[2][2]=1;
            B.m=2;
            B.n=1;
            B.a[1][1]=1;
            B.a[2][1]=2;
            A=Mul(A,n-1);
            A=A*B;
            cout<<A.a[1][1]<<"\n";
        }
    }
}
