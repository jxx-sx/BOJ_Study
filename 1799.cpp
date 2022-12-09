#include <iostream>
#include <vector>

using namespace std;

int n;
vector<pair<int, int>> v;
int v_ind = 0;
int ans = 0, dep = 0;
bool *check1, *check2;

void solve(int x, int y) {
    if (v.size() - v_ind + dep <= ans) {
        v_ind--;
        return;
    }

    if (!check1[x - y + n - 1] and !check2[x + y]) {
        check1[x - y + n - 1] = true;
        check2[x + y] = true;
        dep++;
        ans = max(ans, dep);

        if (v_ind != v.size()) {
            v_ind++;
            solve(v[v_ind].first, v[v_ind].second);
        }
        check1[x - y + n - 1] = false;
        check2[x + y] = false;
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
    check1 = new bool[2 * n - 2];
    check2 = new bool[2 * n - 2];

    for (int i = 0; i < n; i++) {
        check1[i] = check2[i] = false;
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