#include <iostream>

using namespace std;
int r, c;
char **arr;
bool check[26];
int ans = 0, dep = 0;
void solve(int x, int y) {
    if (check[arr[x][y] - 'A'])
        return;
    dep++;
    ans = max(ans, dep);
    check[arr[x][y] - 'A'] = true;
    if (x > 0)
        solve(x - 1, y);
    if (y > 0)
        solve(x, y - 1);
    if (x + 1 < r)
        solve(x + 1, y);
    if (y + 1 < c)
        solve(x, y + 1);

    check[arr[x][y] - 'A'] = false;
    dep--;
    return;
}

void init() {
    cin >> r >> c;
    arr = new char *[r];
    for (int i = 0; i < 26; i++)
        check[i] = false;
    for (int i = 0; i < r; i++) {
        arr[i] = new char[c];
        for (int j = 0; j < c; j++)
            cin >> arr[i][j];
    }
    solve(0, 0);
    cout << ans;

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();

    return 0;
}