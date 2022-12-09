#include <cmath>
#include <iostream>

using namespace std;
int n;
int xx[10000], yy[10000];

void solve() {
    int x = xx[n - 1]; // fixed
    int y = yy[n - 1]; // fixed
    long double ans = 0.0;

    for (int i = 0; i < n - 2; i++) {
        ans += (xx[i] * yy[i + 1] + xx[i + 1] * y + x * yy[i] - xx[i + 1] * yy[i] - x * yy[i + 1] - xx[i] * y) * 5.0;
    }
    round(ans);

    cout << fixed;
    cout.precision(1);
    cout << round(ans) / 10.0;
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