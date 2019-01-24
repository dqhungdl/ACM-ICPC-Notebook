#include <bits/stdc++.h>
using namespace std;

int n,a[10005],b[10005];
vector<int> A,B,C;

bool cmp1(int x1,int x2)
{
    return a[x1]<a[x2];
}

bool cmp2(int x1,int x2)
{
    return b[x1]>b[x2];
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n;i++)
        cin>>b[i];
    for(int i=1;i<=n;i++)
        if(a[i]<=b[i])
            A.push_back(i);
        else
            B.push_back(i);
    sort(A.begin(),A.end(),cmp1);
    sort(B.begin(),B.end(),cmp2);
    int timeA=0,timeB=0;
    for(int i=0;i<A.size();i++)
    {
        C.push_back(A[i]);
        timeA+=a[A[i]];
        timeB=max(timeA,timeB)+b[A[i]];
    }
    for(int i=0;i<B.size();i++)
    {
        C.push_back(B[i]);
        timeA+=a[B[i]];
        timeB=max(timeA,timeB)+b[B[i]];
    }
    cout<<timeB<<"\n";
    for(int i=0;i<C.size();i++)
        cout<<C[i]<<' ';
}
