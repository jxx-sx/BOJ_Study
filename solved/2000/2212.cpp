#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> v, vv;
int n, k;

void init() {
    cin >> n >> k;
    v.resize(n);
    for (auto &a : v)
        cin >> a;
    sort(v.begin(), v.end());
}

void solve() {
    for (int i = 1; i < n; i++)
        vv.push_back(v[i] - v[i - 1]);
    sort(vv.begin(), vv.end());
    for (int i = 1; i < k and vv.size(); i++)
        vv.pop_back();

    int sum = 0;
    for (auto a : vv)
        sum += a;

    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}