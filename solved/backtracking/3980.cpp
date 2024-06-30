#include <iostream>

#define N 1
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int arr[11][11], ans, tc;
bool visited[11];

void dfs(int x = 0, int sum = 0) {
    if (x == 11)
        ans = max(ans, sum);
    for (int i = 0; i < 11; i++) {
        if (arr[x][i] && !visited[i]) {
            visited[i] = true;
            dfs(x + 1, sum + arr[x][i]);
            visited[i] = false;
        }
    }
}

void init() { cin >> tc; }

void solve() {
    while (tc--) {
        ans = 0;
        for (int i = 0; i < 11; i++)
            for (int j = 0; j < 11; j++)
                cin >> arr[i][j];
        dfs();
        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}