#include <cmath>
#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

ll pow_mod(ll a, ll x, ll mod) {
    __int128 _a = a % mod;
    __int128 ret = 1;
    while (x) {
        if (x & 1)
            ret = ret * _a % mod;
        _a = _a * _a % mod;
        x >>= 1;
    }
    return ret;
}

bool miller(ll x, ll a) {
    if (x == a)
        return true;
    ll tmp = x - 1;
    while (tmp) {
        ll mod = pow_mod(a, tmp, x);
        if (mod == x - 1)
            return true;
        if (tmp & 1)
            return mod == 1 || mod == x - 1;
        tmp >>= 1;
    }
    return false;
}

bool is_prime(ll x) {
    if (x <= 2)
        return x == 2;
    if ((x & 1) == 0)
        return false;
    for (auto a : {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41}) {
        if (!miller(x, a))
            return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    ll a, b;
    cin >> a >> b;
    for (ll i = (a | 1ll); i <= b; i += 2) {
        if (is_prime(i)) {
            cout << i << ' ';
            continue;
        }
        if (i >= 25)
            continue;
        ll sq = sqrt(i);
        if (sq * sq != i)
            continue;
        if (is_prime(sq))
            cout << i << ' ';
    }

    return 0;
}