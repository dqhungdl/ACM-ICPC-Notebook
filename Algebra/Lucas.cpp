vector<int64_t> Extract(int64_t x)
{
    vector<int64_t> V;
    while(x>0)
    {
        V.push_back(x%mod);
        x/=mod;
    }
    return V;
}

int64_t Mul(int64_t x,int64_t k)
{
    if(k==0)
        return 1;
    int64_t tmp=Mul(x,k/2);
    if(k%2==0)
        return tmp*tmp%mod;
    return tmp*tmp%mod*x%mod;
}

int64_t Cal(int64_t n,int64_t k)
{
    if(n<k)
        return 0;
    int64_t A=fact[n];
    int64_t B=fact[k]*fact[n-k]%mod;
    return A*Mul(B,mod-2)%mod;
}

int64_t C(int64_t n,int64_t k)
{
    vector<int64_t> N=Extract(n);
    vector<int64_t> K=Extract(k);
    int64_t rs=1;
    for(int64_t i=0;i<K.size();i++)
        rs=rs*Cal(N[i],K[i])%mod;
    return rs;
}
