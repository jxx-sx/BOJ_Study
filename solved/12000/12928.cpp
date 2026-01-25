#include <iostream>

using namespace std;

int n, s, dp[51][1010];

void get_tree(int x, int y) {
    if (dp[n - x][y])
        return;
    if (s < y)
        return;
    dp[n - x][y] = 1;
    for (int i = 1; i <= x; i++)
        get_tree(x - i, y + ((i * (i + 1)) >> 1));
}

void init() { cin >> n >> s; }

void solve() {
    get_tree(n - 2, 0);
    cout << dp[n][s];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}