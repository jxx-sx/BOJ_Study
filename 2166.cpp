#include <cmath>
#include <iostream>

using namespace std;
int n;
int xx[10000], yy[10000];

void solve() {
    int x = xx[n - 1];
    int y = yy[n - 1];
    int a, b, c; // a*x + b*y + c = 0
    double dis;
    double ans = 0.0;
    for (int i = 0; i < n - 2; i++) {
        a = yy[i + 1] - yy[i];
        b = xx[i] - xx[i + 1];
        c = (-a) * xx[i] + (-b) * yy[i];
        dis = abs(a * x + b * y + c) / sqrt(a * a + b * b);
        ans += dis * sqrt(pow(xx[i + 1] - xx[i], 2) + pow(yy[i + 1] - yy[i], 2)) * 5;
    }
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