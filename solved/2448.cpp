#include <iostream>

using namespace std;
int n;
bool **tri;

void init() {
    cin >> n;
    tri = new bool *[n];

    for (int i = 0; i < n; i++) {
        tri[i] = new bool[2 * n - 1];
        for (int j = 0; j < 2 * n - 1; j++) {
            tri[i][j] = false;
        }
        for (int j = 0; j < 2 * i + 1; j++) {
            tri[i][n - i - 1 + j] = true;
        }
    }
}

void solve(int x, int y, int s) {
    if (s == 3) {
        tri[x + 1][y + 2] = false;
        return;
    } else {
        int tmp = s;
        for (int i = 0; i < s / 2; i++) {
            for (int j = 0; j < 2 * i + 1; j++) {
                tri[x + s - i - 1][y + tmp - 1 + j] = false;
            }
            tmp -= 1;
        }
        solve(x, y + s / 2, s / 2);
        solve(x + s / 2, y, s / 2);
        solve(x + s / 2, y + s, s / 2);
    }
}

void print() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * n - 1; j++) {
            if (tri[i][j])
                cout << '*';
            else
                cout << ' ';
        }
        cout << '\n';
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve(0, 0, n);
    print();
}