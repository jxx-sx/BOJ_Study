#include <iostream>

using namespace std;

int n;

void init() { cin >> n; }

void solve() {
    int tmp = 1;
    while (tmp < n) {
        tmp <<= 1;
    }
    cout << tmp << ' ';
    int cnt = 0;
    if (tmp == n) {
        n = 0;
    }
    while (n) {
        tmp >>= 1;
        cnt++;
        if (tmp & n) {
            n -= tmp;
        }
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}