#include <iostream>

using namespace std;

int x1, x2, x3;
int y1, y2, y3;

void init() { cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3; }

void solve() {
    int ans = x1 * y2 + x2 * y3 + x3 * y1 - x2 * y1 - x3 * y2 - y3 * x1;
    cout << (ans > 0 ? 1 : (ans == 0 ? 0 : -1));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}