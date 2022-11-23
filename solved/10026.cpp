#include <iostream>

using namespace std;

int n;
char **set;
bool **check;
int ans = 0;
bool is_blue(int x, int y) { return set[x][y] == 'B'; }
void dfs1(int x, int y) {
    if (check[x][y]) {
        return;
    }
    check[x][y] = true;
    if (x - 1 >= 0 && set[x][y] == set[x - 1][y]) {

        dfs1(x - 1, y);
    }
    if (y - 1 >= 0 && set[x][y] == set[x][y - 1]) {
        dfs1(x, y - 1);
    }
    if (x + 1 < n && set[x][y] == set[x + 1][y]) {
        dfs1(x + 1, y);
    }
    if (y + 1 < n && set[x][y] == set[x][y + 1]) {
        dfs1(x, y + 1);
    }
}
void dfs2(int x, int y) {
    if (check[x][y]) {
        return;
    }
    check[x][y] = true;
    if (x - 1 >= 0 && (is_blue(x, y) == is_blue(x - 1, y))) {
        dfs2(x - 1, y);
    }
    if (y - 1 >= 0 && (is_blue(x, y) == is_blue(x, y - 1))) {
        dfs2(x, y - 1);
    }
    if (x + 1 < n && (is_blue(x, y) == is_blue(x + 1, y))) {
        dfs2(x + 1, y);
    }
    if (y + 1 < n && (is_blue(x, y) == is_blue(x, y + 1))) {
        dfs2(x, y + 1);
    }
}
void init() {
    cin >> n;
    set = new char *[n];
    check = new bool *[n];
    for (int i = 0; i < n; i++) {
        set[i] = new char[n];
        check[i] = new bool[n];
        for (int j = 0; j < n; j++) {
            check[i][j] = false;
            cin >> set[i][j];
        }
    }
}
void solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!check[i][j]) {
                ans += 1;
                dfs1(i, j);
            }
        }
    }
    cout << ans;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            check[i][j] = false;
        }
    }
    ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!check[i][j]) {
                ans += 1;
                dfs2(i, j);
            }
        }
    }
    cout << ' ' << ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
}