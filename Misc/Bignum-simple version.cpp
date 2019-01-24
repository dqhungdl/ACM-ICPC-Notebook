#include <bits/stdc++.h>
using namespace std;

#define f1(i,n) for (int64_t i=1; i<=n; i++)
#define f0(i,n) for (int64_t i=0; i<n; i++)

typedef vector<int64_t> vi;
const int64_t BASE=1e4;

void fix(vi &a){
    a.push_back(0);
    f0(i,a.size()-1) {
        a[i+1]+=a[i]/BASE; a[i]%=BASE;
        if (a[i]<0) { a[i]+=BASE; a[i+1]--; }
    }
    while (a.size()>=2 && a.back()==0) a.pop_back();
}

void operator += (vi &a, const vi &b) {
    a.resize(max(a.size(), b.size()));
    f0(i,b.size()) a[i]+=b[i];
    fix(a);
}

vi operator * (const vi &a, const vi &b){
    vi c(a.size()+b.size());
    f0(i,a.size()) f0(j,b.size()) c[i+j]+=a[i]*b[j];
    return fix(c), c;
}

vi to_vi(int64_t x) // x<BASE
    { return vi(1,x); }

void operator -= (vi &a, const vi &b)
    { f0(i,b.size()) a[i]-=b[i]; fix(a); }
void operator *= (vi &a, int64_t x) // x<BASE
    { f0(i,a.size()) a[i]*=x; fix(a); }
vi operator + (vi a, const vi &b)
    { a+=b; return a; }
vi operator - (vi a, const vi &b)
    { a-=b; return a; }
vi operator * (vi a, int64_t x) // x<BASE
    { a*=x; return a; }

bool operator < (const vi &a, const vi &b){
    if (a.size() != b.size()) return a.size()<b.size();
    for (int64_t i=a.size()-1; i>=0; i--)
    if (a[i]!=b[i]) return a[i]<b[i];
    return false;
}

void divide(const vi &a, int64_t x, vi &q, int64_t &r) {
    q.clear(); r=0;
    for (int64_t i=a.size()-1; i>=0; i--) {
        r=r*BASE+a[i];
        q.push_back(r/x); r%=x;
    }
    reverse(q.begin(), q.end());
    fix(q);
}

vi operator / (const vi &a, int64_t x)
    { vi q; int64_t r; divide(a, x, q, r); return q; }
int64_t operator % (const vi &a, int64_t x)
    { vi q; int64_t r; divide(a, x, q, r); return r; }

istream& operator >> (istream& cin, vi &a){
    string s; cin >> s;
    a.clear(); a.resize(s.size()/4+1);
    f0(i,s.size()) {
        int64_t x = (s.size()-1-i)/4; // <- log10(BASE)=4
        a[x]=a[x]*10+(s[i]-'0');
    }
    return fix(a), cin;
}

ostream& operator << (ostream& cout, const vi &a){
    printf("%d", a.back());
    for (int64_t i=(int64_t)a.size()-2; i>=0; i--)
    printf("%04d", a[i]);
    return cout;
}
