#include <iostream>

#define N 10000
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n;
double arr[N];

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void solve() {
    double ans = arr[0];
    for (int i = 1; i < n; i++) {
        arr[i] = max(arr[i], arr[i] * arr[i - 1]);
        ans = max(ans, arr[i]);
    }
    cout << fixed;
    cout.precision(3);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}