#include <iostream>

using namespace std;

long long q3 = 0;
int q4 = 0;
int m;

void init() { cin >> m; }

void solve() {
    int q, n;
    for (int i = 0; i < m; i++) {
        cin >> q;
        if (q == 1) {
            cin >> n;
            q3 += n;
            q4 ^= n;
        }
        if (q == 2) {
            cin >> n;
            q3 -= n;
            q4 ^= n;
        }
        if (q == 3)
            cout << q3 << '\n';
        if (q == 4)
            cout << q4 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}