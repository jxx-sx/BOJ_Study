#include <cmath>
#include <iostream>

using namespace std;
int n;
long long xx[10001], yy[10001];

void solve() {
    long long ans = 0;

    for (int i = 0; i < n; i++)
        ans += xx[i] * yy[i + 1];

    for (int i = 0; i < n; i++)
        ans -= xx[i + 1] * yy[i];

    ans = abs(ans);
    cout << fixed;
    cout.precision(1);
    cout << ans / 2.0;
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> xx[i] >> yy[i];
    xx[n] = xx[0];
    yy[n] = yy[0];
    solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
}