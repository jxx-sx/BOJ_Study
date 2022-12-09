#include <iostream>
#include <vector>

using namespace std;

int n;
vector<pair<int, int>> v, b;
int v_ind = 0;
int ans = 0, dep = 0;

void solve(int x, int y) {
    if (v.size() - v_ind + dep <= ans) {
        v_ind--;
        return;
    }
    bool flag = false;
    for (auto cur : b) {
        if (abs(cur.first - x) == abs(cur.second - y)) {
            flag = true;
            break;
        }
    }

    if (!flag) {
        b.push_back({x, y});
        dep++;
        ans = max(ans, dep);

        if (v_ind != v.size()) {
            v_ind++;
            solve(v[v_ind].first, v[v_ind].second);
        }

        b.pop_back();
        dep--;
    }

    if (v_ind != v.size()) {
        v_ind++;
        solve(v[v_ind].first, v[v_ind].second);
    }

    v_ind--;
    return;
}

void init() {
    int inp;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> inp;
            if (inp == 1) {
                v.push_back({i, j});
            }
        }
    }
    solve(0, 0);

    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
}