#include <iostream>

using namespace std;

int n, m;
int arr[101];

void init() { cin >> n >> m; }

void solve() {
    int l, r, k;
    while (m--) {
        cin >> l >> r >> k;
        for (int i = l; i <= r; i++)
            arr[i] = k;
    }
    for (int i = 1; i <= n; i++)
        cout << arr[i] << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}