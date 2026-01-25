#include <algorithm>
#include <iostream>

using namespace std;

int n;
int arr[100000];
long long ans;

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n, greater());
    return;
}

void solve() {
    for (int i = 0; i < n; i++)
        ans = max((long long)(i + 1) * arr[i], ans);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}