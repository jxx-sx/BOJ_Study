#include <iostream>

using namespace std;
int arr[503][503];
int n, m;
int ans = 0;

void I_block(int x, int y) {
    ans = max(ans, arr[x][y] + arr[x][y + 1] + arr[x][y + 2] + arr[x][y + 3]);
    ans = max(ans, arr[x][y] + arr[x + 1][y] + arr[x + 2][y] + arr[x + 3][y]);
}

void O_block(int x, int y) { ans = max(ans, arr[x][y] + arr[x + 1][y] + arr[x][y + 1] + arr[x + 1][y + 1]); }

void T_block(int x, int y) {
    ans = max(ans, arr[x][y] + arr[x][y + 1] + arr[x][y + 2] + arr[x + 1][y + 1]);
    ans = max(ans, arr[x + 1][y] + arr[x + 1][y + 1] + arr[x + 1][y + 2] + arr[x][y + 1]);
    ans = max(ans, arr[x][y] + arr[x + 1][y] + arr[x + 2][y] + arr[x + 1][y + 1]);
    ans = max(ans, arr[x][y + 1] + arr[x + 1][y + 1] + arr[x + 2][y + 1] + arr[x + 1][y]);
}

void S_block(int x, int y) {
    ans = max(ans, arr[x + 1][y] + arr[x + 1][y + 1] + arr[x][y + 1] + arr[x][y + 2]);
    ans = max(ans, arr[x][y] + arr[x + 1][y] + arr[x + 1][y + 1] + arr[x + 2][y + 1]);
}

void Z_block(int x, int y) {
    ans = max(ans, arr[x][y] + arr[x][y + 1] + arr[x + 1][y + 1] + arr[x + 1][y + 2]);
    ans = max(ans, arr[x][y + 1] + arr[x + 1][y + 1] + arr[x + 1][y] + arr[x + 2][y]);
}

void J_block(int x, int y) {
    ans = max(ans, arr[x][y] + arr[x + 1][y] + arr[x + 1][y + 1] + arr[x + 1][y + 2]);
    ans = max(ans, arr[x][y] + arr[x][y + 1] + arr[x][y + 2] + arr[x + 1][y + 2]);
    ans = max(ans, arr[x][y] + arr[x + 1][y] + arr[x + 2][y] + arr[x][y + 1]);
    ans = max(ans, arr[x][y + 1] + arr[x + 1][y + 1] + arr[x + 2][y + 1] + arr[x + 2][y]);
}

void L_block(int x, int y) {
    ans = max(ans, arr[x][y + 2] + arr[x + 1][y] + arr[x + 1][y + 1] + arr[x + 1][y + 2]);
    ans = max(ans, arr[x][y] + arr[x][y + 1] + arr[x][y + 2] + arr[x + 1][y]);
    ans = max(ans, arr[x][y] + arr[x + 1][y] + arr[x + 2][y] + arr[x + 2][y + 1]);
    ans = max(ans, arr[x][y + 1] + arr[x + 1][y + 1] + arr[x + 2][y + 1] + arr[x][y]);
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> arr[i][j];
    return;
}

void solve() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            I_block(i, j);
            O_block(i, j);
            T_block(i, j);
            S_block(i, j);
            Z_block(i, j);
            J_block(i, j);
            L_block(i, j);
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