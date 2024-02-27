#include <iostream>
#include <queue>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int s;
int dp[2000][2000];
queue<pair<int, int>> q;

void init() { cin >> s; }

void solve() {
    q.push({1, 0});
    dp[1][0] = 1;
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (cur.first == s) {
            cout << dp[cur.first][cur.second] - 1;
            break;
        }
        if (cur.first < s) {
            if (!dp[cur.first][cur.first]) {
                dp[cur.first][cur.first] = dp[cur.first][cur.second] + 1;
                q.push({cur.first, cur.first});
            }
            if (cur.first + cur.second < 2000 and !dp[cur.first + cur.second][cur.second]) {
                dp[cur.first + cur.second][cur.second] = dp[cur.first][cur.second] + 1;
                q.push({cur.first + cur.second, cur.second});
            }
        }
        if (cur.first > 0 and !dp[cur.first - 1][cur.second]) {
            dp[cur.first - 1][cur.second] = dp[cur.first][cur.second] + 1;
            q.push({cur.first - 1, cur.second});
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}