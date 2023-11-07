#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

priority_queue<int> pq;
vector<pair<int, int>> v;
int n, l, p;

void init() {
    cin >> n;
    v.resize(n);
    for (auto &a : v)
        cin >> a.first >> a.second;
    cin >> l >> p;
    sort(v.begin(), v.end());
}

void solve() {
    int cur = 0, cnt = 0;
    for (; cur < n; cur++) {
        if (v[cur].first > p)
            break;
        pq.push(v[cur].second);
    }
    while (pq.size()) {
        if (p >= l)
            break;
        p += pq.top();
        pq.pop();
        cnt++;
        for (; cur < n; cur++) {
            if (v[cur].first > p)
                break;
            pq.push(v[cur].second);
        }
    }

    cout << (p < l ? -1 : cnt);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}