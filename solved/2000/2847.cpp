#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

vector<int> v;
int n, ans;

void init() {
    cin >> n;
    v.resize(n);
    for (auto &a : v)
        cin >> a;
}

void solve() {
    int prv = v.back();
    v.pop_back();
    while (v.size()) {
        if (v.back() >= prv) {
            ans += v.back() - prv + 1;
            v.back() = prv - 1;
        }
        prv = v.back();
        v.pop_back();
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    init(), solve();

    return 0;
}