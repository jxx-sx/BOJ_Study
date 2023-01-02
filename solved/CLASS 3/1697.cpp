#include <iostream>
#include <queue>
#include <vector>

using namespace std;
int n, k, ans = 0;
vector<bool> is_visit = vector<bool>(100100, false);
queue<pair<int, int>> q;

void init() {
    cin >> n >> k;
    q.push({n, 0});
    is_visit[n] = true;
    return;
}

void solve() {
    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        int a = cur.first;
        if (a == k) {
            cout << cur.second;
            break;
        } else {
            if (a + 1 < 100100)
                if (!is_visit[a + 1]) {
                    q.push({a + 1, cur.second + 1});
                    is_visit[a + 1] = true;
                }
            if (a - 1 >= 0)
                if (!is_visit[a - 1]) {
                    q.push({a - 1, cur.second + 1});
                    is_visit[a - 1] = true;
                }
            if (a * 2 < 100100)
                if (!is_visit[a * 2]) {
                    q.push({a * 2, cur.second + 1});
                    is_visit[a * 2] = true;
                }
        }
    }

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}