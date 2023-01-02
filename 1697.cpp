#include <iostream>
#include <vector>

using namespace std;
int n, k, ans = 0;
vector<bool> is_visit = vector<bool>(100100, false);
vector<int> v;

void init() {
    cin >> n >> k;
    v.push_back(n);
    is_visit[n] = true;
    return;
}

void solve() {
    while (true) {
        vector<int> tmp;
        for (auto a : v) {
            if (a == k) {
                cout << ans;
                return;
            } else {
                if (!is_visit[a + 1] and a + 1 < 100100) {
                    tmp.push_back(a + 1);
                    is_visit[a + 1] = true;
                }
                if (!is_visit[a - 1] and a > 1) {
                    tmp.push_back(a - 1);
                    is_visit[a - 1] = true;
                }
                if (!is_visit[a * 2] and a * 2 < 100100) {
                    tmp.push_back(a * 2);
                    is_visit[a * 2] = true;
                }
            }
        }
        ans += 1;
        v = tmp;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}