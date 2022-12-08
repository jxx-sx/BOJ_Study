#include <iostream>
#include <vector>

using namespace std;

int n, s;
vector<int> v;
int ans;

void solve() {
    ans = s;
    int lp = 0, rp = 0;
    int sum = 0;
    while (true) {
        if (sum >= s) {
            ans = min(ans, rp - lp);
            if (lp == v.size())
                break;
            sum -= v[lp];
            lp += 1;
        } else {
            if (rp == v.size())
                break;
            sum += v[rp];
            rp += 1;
        }
    }
}

void init() {
    int tmp;
    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        v.push_back(tmp);
    }

    solve();
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
}