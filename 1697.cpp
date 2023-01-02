#include <iostream>
#include <vector>

using namespace std;
int n, k, ans = 0;
vector<int> v;

void init() {
    cin >> n >> k;
    v.push_back(n);

    return;
}

void solve() {
    while (true) {
        ans += 1;
        vector<int> tmp;
        for (auto a : v) {
            if (a + 1 == k) {
                cout << ans;
                return;
            } else {
                tmp.push_back(a + 1);
            }
            if (a - 1 == k) {
                cout << ans;
                return;
            } else {
                tmp.push_back(a - 1);
            }
            if (a * 2 == k) {
                cout << ans;
                return;
            } else {
                tmp.push_back(a * 2);
            }
        }
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