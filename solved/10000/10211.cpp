#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, mx;
int arr[1000];

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    mx = arr[0];
}

void solve() {
    for (int i = 1; i < n; i++) {
        arr[i] = max(arr[i - 1], 0) + arr[i];
        mx = max(arr[i], mx);
    }
    cout << mx << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    while (tc--) {
        init();
        solve();
    }

    return 0;
}