//Given two arrays A and B
//Calculate get(i)=sigma(A(j)*B(i-j)) with 0<=j<=i
// O(nlogn)

#include <algorithm>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int N = 200000;
const double PI = 3.14159265358979323846264338327950288;

struct point
{
    using T = double;

    T real;
    T imag;

    point(T real = 0, T imag = 0)
        : real(real)
        , imag(imag) {}

    friend point operator*(const point& lhs, const point& rhs)
    {
        return point(lhs.real * rhs.real - lhs.imag * rhs.imag,
                     lhs.real * rhs.imag + lhs.imag * rhs.real);
    }

    friend point operator+(const point& lhs, const point& rhs)
    {
        return point(lhs.real + rhs.real, lhs.imag + rhs.imag);
    }

    friend point operator-(const point& lhs, const point& rhs)
    {
        return point(lhs.real - rhs.real, lhs.imag - rhs.imag);
    }

    void operator/=(int32_t n)
    {
        real /= n;
    }
};

bool mark[N * 2 + 1];
int T,n,a[N * 2 + 1], b[N * 2 + 1], rev[1 << 20];
long long cnt[N * 2 + 1];
point pa[1 << 20], pb[1 << 20], x[1 << 20];

long long get(int i)
{
    if (!mark[i])
    {
        mark[i] = true;
        cnt[i] = (long long)(pa[i].real + 0.5);
    }
    return cnt[i];
}

void fft(point input[], int n, bool invert)
{
    int dig = 0;
    while ((1 << dig) < n)
    {
        ++dig;
    }
    for (int i = 0; i < n; ++i)
    {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (dig - 1));
        if (rev[i] > i)
        {
            swap(input[i], input[rev[i]]);
        }
    }
    for (int len = 2; len <= n; len <<= 1)
    {
        double angle = 2 * PI / len;
        if (invert)
        {
            angle *= -1;
        }
        point w(cos(angle), sin(angle));
        x[0] = point(1);
        for (int i = 1; i < len / 2; ++i)
        {
            x[i] = x[i - 1] * w;
        }
        for (int i = 0; i < n; i += len)
        {
            for (int j = 0; j < len / 2; ++j)
            {
                point a = input[i + j];
                point b = x[j] * input[i + j + len / 2];
                input[i + j] = a + b;
                input[i + j + len / 2] = a - b;
            }
        }
    }
    if (invert)
    {
        for (int i = 0; i < n; ++i)
        {
            input[i] /= n;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    //freopen("C.INP","r",stdin);
    cin>>n;
    int v,a_deg = 0, b_deg = 0;
    a[0]=1;
    b[0]=1;
    for (int i = 0; i < n; ++i)
    {
        cin>>v;
        a[v]=1;
        b[v]=1;
        a_deg = max(a_deg, v);
        b_deg = max(b_deg, v);
    }
    for (int i = 0; i <= a_deg; ++i)
    {
        pa[i] = point(a[i], 0);
    }
    for (int i = 0; i <= b_deg; ++i)
    {
        pb[i] = point(b[i], 0);
    }
    int deg = a_deg + b_deg;
    int size = 1;
    while (size < deg + 1)
        size <<= 1;
    fft(pa, size, false);
    fft(pb, size, false);
    for (int i = 0; i < size; ++i)
        pa[i] = pa[i] * pb[i];
    fft(pa, size, true);
    cin>>T;
    long long answer = 0;
    for (int i = 0; i < T; ++i)
    {
        cin>>v;
        answer += (get(v)>0);
    }
    cout<<answer;
}
