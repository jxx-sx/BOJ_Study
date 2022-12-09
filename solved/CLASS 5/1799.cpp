#include <iostream>
#include <vector>

using namespace std;

int n;
vector<pair<int, int>> v1, v2;
int v_ind1 = 0, v_ind2 = 0;
int ans = 0, ans1 = 0, ans2 = 0, dep = 0;
bool *check1, *check2;

void solve1(int x, int y) {
    if (v1.size() - v_ind1 + dep > ans1) {
        if (!check1[x - y + n - 1] and !check2[x + y]) {
            check1[x - y + n - 1] = true;
            check2[x + y] = true;
            dep++;
            ans1 = max(ans1, dep);

            if (v_ind1 != v1.size()) {
                v_ind1++;
                solve1(v1[v_ind1].first, v1[v_ind1].second);
            }
            check1[x - y + n - 1] = false;
            check2[x + y] = false;
            dep--;
        }

        if (v_ind1 != v1.size()) {
            v_ind1++;
            solve1(v1[v_ind1].first, v1[v_ind1].second);
        }
    }

    v_ind1--;
    return;
}

void solve2(int x, int y) {
    if (v2.size() - v_ind2 + dep > ans2) {
        if (!check1[x - y + n - 1] and !check2[x + y]) {
            check1[x - y + n - 1] = true;
            check2[x + y] = true;
            dep++;
            ans2 = max(ans2, dep);

            if (v_ind2 != v2.size()) {
                v_ind2++;
                solve2(v2[v_ind2].first, v2[v_ind2].second);
            }
            check1[x - y + n - 1] = false;
            check2[x + y] = false;
            dep--;
        }

        if (v_ind2 != v2.size()) {
            v_ind2++;
            solve2(v2[v_ind2].first, v2[v_ind2].second);
        }
    }

    v_ind2--;
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
                if ((i + j) % 2 == 1)
                    v1.push_back({i, j});
                else
                    v2.push_back({i, j});
            }
        }
    }
    if (!v1.empty())
        solve1(v1.front().first, v1.front().second);
    if (!v2.empty())
        solve2(v2.front().first, v2.front().second);

    cout << ans1 + ans2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
}