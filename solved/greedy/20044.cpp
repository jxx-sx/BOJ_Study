#include <algorithm>
#include <iostream>

using namespace std;
int n;
int arr[10000];
void init() {
    cin >> n;
    for (int i = 0; i < (n << 1); i++)
        cin >> arr[i];

    sort(arr, arr + (n << 1));
    return;
}

void solve() {
    int ans = 10000000;
    for (int i = 0; i < n; i++) {
        ans = min(ans, arr[i] + arr[(n << 1) - i - 1]);
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