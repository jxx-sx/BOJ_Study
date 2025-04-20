#include <algorithm>
#include <iostream>

#define N 1
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, m;
int a6 = 2000, a1 = 2000;

void init() {
    int a, b;
    cin >> n >> m;
    while (m--) {
        cin >> a >> b;
        a6 = min({a6, a, b * 6});
        a1 = min(a1, b);
    }
}

void solve() { cout << min({a1 * n, a6 * (n / 6) + a1 * (n % 6), a6 * ((n + 5) / 6)}); }

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    init();
    solve();

    return 0;
}