#include <iostream>

using namespace std;

int n, s;
int arr[20];
int tmp;
int ans;

void dfs(int x) {
    tmp += arr[x];
    if (tmp == s)
        ans++;

    for (int i = x + 1; i < n; i++)
        dfs(i);

    tmp -= arr[x];
}

void init() {
    cin >> n >> s;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void solve() {
    for (int i = 0; i < n; i++)
        dfs(i);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}