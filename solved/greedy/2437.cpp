#include <algorithm>
#include <iostream>
#include <vector>

#define N 1
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, prv = 1;
vector<int> v;

void init() {
    cin >> n;
    v.resize(n);
    for (auto &a : v)
        cin >> a;
    sort(v.begin(), v.end());
}

void solve() {
    if (v[0] != 1) {
        cout << 1;
        return;
    }
    for (int i = 1; i < n; i++) {
        if (v[i] > prv + 1)
            break;
        prv += v[i];
    }
    cout << prv + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}