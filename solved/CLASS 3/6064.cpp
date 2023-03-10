#include <iostream>
#include <numeric>

using namespace std;

int t;
int m, n, x, y;

void solve() {
    int the_end = lcm(m, n);
    for (int i = 0; m * i + x <= the_end; i++) {
        if ((m * i + x) % n == y % n) {
            cout << m * i + x << '\n';
            return;
        }
    }
    cout << -1 << '\n';
}

void init() {
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> m >> n >> x >> y;
        solve();
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();

    return 0;
}