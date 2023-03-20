#include <iostream>

using namespace std;

int arr[1000001];
int n, l;

void init() {
    cin >> n >> l;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    return;
}

void solve() {
    int ans = 0;
    bool flag = false;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += arr[i];
        if (i > l)
            sum -= arr[i - l];
        if (sum <= 138 and 129 <= sum)
            ans++;
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