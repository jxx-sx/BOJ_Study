#include <iostream>

#define N 100001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int arr[N], n, q;

void init() {
    cin >> n;
    int cur, prev = 0;
    for (int i = 1; i <= n; i++) {
        cin >> cur;
        if (prev > cur)
            arr[i - 1]++;
        arr[i] = arr[i - 1];
        prev = cur;
    }
    cin >> q;
}

void solve() {
    int x, y;
    while (q--) {
        cin >> x >> y;
        cout << arr[y - 1] - arr[x - 1] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}