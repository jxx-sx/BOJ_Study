#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m, ans = 0;
vector<pair<int, int>> v;

void solve() {
    int lp = 0, rp = 0;
    int sum = 0, c_sum = 0;
    while (true) {
        if (sum >= m) {
            ans = min(ans, c_sum);
            if (lp == v.size())
                break;
            sum -= v[lp].first;
            c_sum -= v[lp].second;
            lp += 1;
        } else {
            if (rp == v.size())
                break;
            sum += v[rp].first;
            c_sum += v[rp].second;
            rp += 1;
        }
    }
}

void init() {
    int inp;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> inp;
        v.push_back({inp, 0});
    }
    for (int i = 0; i < n; i++) {
        cin >> inp;
        v[i].second = inp;
        ans += inp;
    }
    sort(v.begin(), v.end());

    solve();
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
}