#include <iostream>

using namespace std;
int arr[2187][2187];
int ans[3], n;

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> arr[i][j];

    return;
}

void recursive(int x, int y, int s) {
    int first_tile = arr[x][y];
    for (int i = x; i < x + s; i++)
        for (int j = y; j < y + s; j++)
            if (first_tile != arr[i][j]) {
                int new_size = s / 3;
                for (int k   = 0; k < 3; k++)
                    for (int l = 0; l < 3; l++)
                        recursive(x + new_size * k, y + new_size * l, new_size);
                return;
            }

    ans[first_tile + 1]++;
    return;
}

void solve() {
    recursive(0, 0, n);
    for (int i = 0; i < 3; i++)
        cout << ans[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}