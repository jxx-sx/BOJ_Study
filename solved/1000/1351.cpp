#include <iostream>
#include <map>

#define N 1
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;
map<ll, ll> m;
ll n, p, q;

void dfs(ll x) {
    if (m[x])
        return;
    dfs(x / p), dfs(x / q);
    m[x] = m[x / p] + m[x / q];
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    cin >> n >> p >> q;
    m[0] = 1;
    dfs(n);
    cout << m[n];

    return 0;
}