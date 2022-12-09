#include <iostream>
#include <vector>

using namespace std;

int n;
int **arr;
vector<pair<int, int>> v, b;
int v_ind = 0;
int ans = 0, dep = 0;

void solve(int x, int y) {
    if (v_ind != v.size()) {
        v_ind++;
        solve(v[v_ind].first, v[v_ind].second);
    }

    for (auto cur : b) {
        if (abs(cur.first - x) == abs(cur.second - y)) {
            v_ind--;
            return;
        }
    }

    b.push_back({x, y});
    dep++;

    ans = max(ans, dep);

    if (v_ind != v.size()) {
        v_ind++;
        solve(v[v_ind].first, v[v_ind].second);
    }

    b.pop_back();
    v_ind--;
    dep--;
    return;
}

void init() {
    cin >> n;
    arr = new int *[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 1) {
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