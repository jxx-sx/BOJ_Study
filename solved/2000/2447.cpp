#include <cmath>
#include <iostream>

using namespace std;

bool arr[6561][6561];
int n;

void recursive(int x, int y, int d) {
    int div = d / 3;
    for (int i = 0; i < div; i++)
        for (int j = 0; j < div; j++)
            arr[x + div + i][y + div + j] = true;

    if (d == 3)
        return;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            recursive(x + div * i, y + div * j, div);
}

void init() {
    cin >> n;

    return;
}

void solve() {
    recursive(0, 0, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << (arr[i][j] ? ' ' : '*');
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}