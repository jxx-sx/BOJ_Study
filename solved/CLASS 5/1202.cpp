#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
int n, k;
vector<pair<int, int>> v;
vector<int> bag;
priority_queue<int> pq;
long long ans = 0;

void solve() {
    int i = 0;
    for (auto a : bag) {
        while (i < v.size()) {
            if (v[i].first <= a) {
                pq.push(v[i].second);
                i++;
            } else
                break;
        }
        if (!pq.empty()) {
            ans += pq.top();
            pq.pop();
        }
    }
    cout << ans;
    return;
}

void init() {
    int s, e;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> s >> e;
        v.push_back({s, e});
    }
    for (int i = 0; i < k; i++) {
        cin >> s;
        bag.push_back(s);
    }

    sort(v.begin(), v.end());
    sort(bag.begin(), bag.end());
    solve();
    return;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    return 0;
}