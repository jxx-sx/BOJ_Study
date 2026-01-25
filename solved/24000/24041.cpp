#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<pair<long long, int>> v1, v2;
int n, g, k;
int ans;

void search() {
    long long l = 0;
    long long r = 2000000000;
    while (l <= r) {
        long long sum = 0;
        int mid = (l + r) / 2;
        priority_queue<long long> pq;
        for (auto a : v1)
            sum += a.first * max(1, mid - a.second);
        for (auto a : v2) {
            pq.push(a.first * max(1, mid - a.second));
            sum += a.first * max(1, mid - a.second);
        }
        for (int i = 0; i < k; i++) {
            if (pq.empty())
                break;
            sum -= pq.top();
            pq.pop();
        }

        if (sum <= g) {
            ans = max(mid, ans);
            l = mid + 1;
        } else
            r = mid - 1;
    }
}

void init() {
    long long s, l, o;
    cin >> n >> g >> k;
    for (int i = 0; i < n; i++) {
        cin >> s >> l >> o;
        if (o)
            v2.push_back({s, l});
        else
            v1.push_back({s, l});
    }
}

void solve() {
    search();
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}