#include <iostream>

using namespace std;

int arr[1000][1000];
int n, m;
int ans;

bool init() {
    cin >> n >> m;
    if (n == 0 and m == 0)
        return false;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> arr[i][j];
    return true;
}

void solve() {
    ans = 0;
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
            if (arr[i][j]) {
                arr[i][j] = min(arr[i - 1][j - 1], min(arr[i][j - 1], arr[i - 1][j])) + 1;
            }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ans = max(arr[i][j], ans);
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (init())
        solve();

    return 0;
}