#include <cmath>
#include <iostream>

using namespace std;
int N, r, c, now = 0;

void solve() {
    for (int i = N - 1; i >= 0; i--) {
        int tmp = pow(2, i);
        int ttmp = pow(4, i);
        if (r < tmp && c < tmp) {
        } else if (r < tmp) {
            now += ttmp;
            c -= tmp;

        } else if (c < tmp) {
            now += 2 * ttmp;
            r -= tmp;

        } else {
            now += 3 * ttmp;
            c -= tmp;
            r -= tmp;
        }
    }
    cout << now;
}

void init() { cin >> N >> r >> c; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
}