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
        vector<int> tmp;
        for (auto a : v) {
            if (a == k) {
                cout << ans;
                return;
            } else {
                tmp.push_back(a + 1);
                tmp.push_back(a - 1);
                tmp.push_back(a * 2);
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