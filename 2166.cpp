#include <cmath>
#include <iostream>

using namespace std;
int n;
int xx[10001], yy[10001];

void solve() {
    long long ans = 0;

    for (int i = 0; i < n; i++) {
        ans += xx[i] * yy[i + 1];
        ans -= xx[i + 1] * yy[i];
    }
    ans = abs(ans);
    int tmp = 0;
    if (ans % 2 == 1)
        tmp = 5;
    round(ans);
    cout << ans / 2 << '.' << tmp;
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