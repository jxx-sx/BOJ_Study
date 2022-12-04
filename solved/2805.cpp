#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> v;
long long ans = 0;

long long cut(long long a) {
    long long ret = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] > a)
            ret += v[i] - a;
    }
    return ret;
}

void solve() {
    long long lo = 1, hi = v.back();
    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        long long tmp = cut(mid);
        if (tmp >= m) {
            lo = mid + 1;
            ans = max(mid, ans);
        } else {
            hi = mid - 1;
        }
    }
    cout << ans;
}

void init() {
    int tmp;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        v.push_back(tmp);
    }
    sort(v.begin(), v.end());
    solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
}