#include <bits/stdc++.h>
#define fo(i,m,n) for(int i = m; i <= n; i++)
#define fod(i,m,n) for(int i = m; i >= n; i--)
using namespace std;
typedef int64_t i64;
i64 a[] = {2,3,5,7,11,13,17,19,23,29};
vector <i64> b;
i64 gcd(i64 x, i64 y)
{
    if(x < y) swap(x,y);
    while(y)
    {
        x %= y;
        swap(x,y);
    }
    return x;
}
i64 modu(i64 x, i64 y, i64 p)
{
    i64 temp = x % p;
    i64 ans = 0;
    while(y)
    {
        if(y&1) ans = (ans+temp) % p;
        temp = (temp << 1) % p;
        y >>= 1;
    }
    return ans;
}
i64 pow_mod(i64 x, i64 n, i64 p)
{
    // x^n mod p
    i64 temp = x % p;
    i64 ans = 1;
    while(n)
    {
        if(n & 1) ans = modu(ans,temp,p);
        temp = modu(temp,temp,p);
        n >>= 1;
    }
    return ans;
}
bool Rabin_Miller(i64 n)
{
    fo(i,0,9)
    {
        if(n == a[i]) return true;
        if(gcd(a[i],n) != 1) return false;
        if(pow_mod(a[i],n-1,n) != 1) return false;
        i64 k = 0,q,_n = n-1;
        while((_n & 1) == 0)
        {
            k++;
            _n >>= 1;
        }
        q = n / (1 << k);
        vector <i64> p(k+1);
        p[0] = pow_mod(a[i],q,n);
        if(p[0] == 1) continue;
        fo(j,1,k)
        {
            p[j] = pow_mod(p[j-1],2,n);
            if(p[j] == 1)
            {
                if(p[j-1] == n-1) break;
                else return false;
            }
        }
    }
    return true;
}
i64 f(i64 x,i64 n)
{
    return pow_mod(x,2,n) + 1;
}
i64 RHO(i64 n)
{
    i64 x,y,p = 0;
    x = (rand()*rand()) % n;
    y = x;
    while(p <= 1 || p == n)
    {
        x = f(x,n);
        y = f(f(y,n),n);
        p = gcd(abs(x-y),n);
    }
    return p;
}
void Fast_Fact(i64 n)
{
    if(n % 2 == 0)
    {
        b.push_back(2);
        while(n % 2 == 0) n/= 2;
    }
    for(i64 i = 3; i * i <= n; i += 2)
    {
        if(n % i == 0)
        {
            b.push_back(i);
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) b.push_back(n);
}
void Fact(i64 n)
{
    if(Rabin_Miller(n))
    {
        b.push_back(n);
        return;
    }
    if(n <= 1e9) Fast_Fact(n);
    else
    {
        i64 p = RHO(n);
        Fact(p); Fact(n/p);
    }
}
i64 phi(i64 n)
{
    b.clear();
    if(Rabin_Miller(n)) return n-1;
    Fact(n);
    sort(b.begin(),b.end());
    i64 k = unique(b.begin(),b.end()) - b.begin();
    i64 ans = n;
    fo(i,0,k-1)
    {
        ans -= (ans/b[i]);
    }
    return ans;
}
int main()
{
    //freopen("PHI.INP","r",stdin);
    //freopen("PHI.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	i64 n,_k;
	n = 23743668478530; _k = 1;
	//cin >> n >> _k;
    while(_k--)
    {
        if(n == 1) break;
        n = phi(n);
    }
    cout << n;
    return 0;
}
