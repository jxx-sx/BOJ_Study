#include <cmath>
#include <iostream>

using namespace std;
int n;
int xx[10000], yy[10000];

void solve() {
    long long tmp = 0;

    for (int i = 0; i < n - 1; i++) {
        tmp += xx[i] * yy[i + 1] - xx[i + 1] * yy[i];
    }
    tmp += xx[n - 1] * yy[0] - xx[0] * yy[n - 1];

    long double ans = abs(tmp) * 5.0;
    round(ans);
    cout << fixed;
    cout.precision(1);
    cout << ans / 10.0;
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> xx[i] >> yy[i];
    solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
}