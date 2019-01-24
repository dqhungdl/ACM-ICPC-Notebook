#include <bits/stdc++.h>
using namespace std;

int n,m,T,f[50005][20];

int Query(int l,int r)
{
	int k=log2(r-l+1);
	return max(f[l][k],f[r-(1<<k)+1][k]);
}

int main()
{
	cin>>n>>m;
	int l,r,w;
	while(m--)
	{
		cin>>l>>r>>w;
		f[l][0]+=w;
		f[r+1][0]-=w;
	}
	for(int i=1;i<=n;i++)
		f[i][0]+=f[i-1][0];
	for(int k=1;(1<<k)<=n;k++)
		for(int i=1;i+(1<<k)-1<=n;i++)
			f[i][k]=max(f[i][k-1],f[i+(1<<(k-1))][k-1]);
	cin>>T;
	while(T--)
	{
		cin>>l>>r;
		cout<<Query(l,r)<<"\n";
	}
}
