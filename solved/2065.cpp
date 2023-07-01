#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> l, r;

int m, t, n;
long long ans[100000];
bool is_left = true;
long long cur_time;

void init() {
    cin >> m >> t >> n;
    string st;
    long long s;
    for (int i = 0; i < n; i++) {
        cin >> s >> st;
        if (st == "left")
            l.push({s, i});
        else
            r.push({s, i});
    }
}

bool val() {
    if (is_left) {
        if (l.empty())
            return false;
        if (l.top().first > cur_time)
            return false;
    } else {
        if (r.empty())
            return false;
        if (r.top().first > cur_time)
            return false;
    }
    return true;
}

void solve() {
    while (!l.empty() or !r.empty()) {
        if (!val()) {
            if (!l.empty() and !r.empty()) {
                if (l.top().first < r.top().first) {
                    cur_time = max(cur_time, l.top().first);
                    if (!is_left) {
                        is_left = true;
                        cur_time += t;
                    }
                } else if (l.top().first == r.top().first) {
                    cur_time = max(cur_time, l.top().first);
                } else {
                    cur_time = max(cur_time, r.top().first);
                    if (is_left) {
                        is_left = false;
                        cur_time += t;
                    }
                }
            } else if (l.empty()) {
                cur_time = max(cur_time, r.top().first);
                if (is_left) {
                    is_left = false;
                    cur_time += t;
                }
            } else {
                cur_time = max(cur_time, l.top().first);
                if (!is_left) {
                    is_left = true;
                    cur_time += t;
                }
            }
        }
        if (is_left) {
            for (int i = 0; i < m; i++) {
                if (l.empty())
                    break;
                if (l.top().first > cur_time)
                    break;
                ans[l.top().second] = cur_time + t;
                l.pop();
            }
            is_left = false;
        } else {
            for (int i = 0; i < m; i++) {
                if (r.empty())
                    break;
                if (r.top().first > cur_time)
                    break;
                ans[r.top().second] = cur_time + t;
                r.pop();
            }
            is_left = true;
        }
        cur_time += t;
    }

    for (int i = 0; i < n; i++)
        cout << ans[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}