#include <iostream>
#include <vector>

using namespace std;

int n, ans = 0;
vector<int> odd;

void solve() {
    int lp = 0, rp = 0;
    int sum = 0;
    while (1) {
        if (sum == n) {
            ans += 1;
        }
        if (sum <= n) {
            if (rp == odd.size())
                break;
            sum += odd[rp];
            rp += 1;
        } else {
            if (lp == odd.size())
                break;
            sum -= odd[lp];
            lp += 1;
        }
    }
    return;
}

void make_odd_num() {
    bool check[n + 1];
    for (int i = 0; i <= n; i++)
        check[i] = true;
    for (int i = 2; i <= n; i++)
        if (check[i]) {
            odd.push_back(i);
            for (int j = 2; i * j <= n; j++)
                check[i * j] = false;
        }

    return;
}

void init() {
    cin >> n;
    make_odd_num();
    solve();
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
}