#include <algorithm>
#include <iostream>

using namespace std;

int arr[500000];
int n;

void init() {

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n);

    return;
}

void solve() {
    long long ans = 0;

    for (int i = 0; i < n; i++) {
        ans += abs(i + 1 - arr[i]);
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}