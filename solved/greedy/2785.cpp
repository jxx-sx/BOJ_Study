#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<long long> v;
deque<long long> dq;

void init() {
    cin >> n;
    v.resize(n);
    for (auto &a : v)
        cin >> a;
    sort(v.begin(), v.end());
    for (auto a : v)
        dq.push_back(a);
}

void solve() {
    int ans = 0;
    while (dq.size() > 2) {
        int cur = dq.front();
        dq.pop_front();
        auto tmp = dq.back();
        dq.pop_back();
        tmp += dq.back();
        dq.pop_back();
        dq.push_back(tmp);
        ans++;
        if (cur > 1)
            dq.push_front(cur - 1);
    }
    if (dq.size() == 2)
        ans++;
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}