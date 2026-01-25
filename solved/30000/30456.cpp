#include <iostream>

using namespace std;

int n, l;

void init() { cin >> n >> l; }

void solve() {
    cout << max(n, 1);
    for (int i = 1; i < l; i++)
        cout << (n ? 1 : 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}