#include <iostream>

using namespace std;

int arr[9][9];

void print() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << arr[i][j];
        }
        cout << '\n';
    }
}
bool solve(int a) {
    if (a == 81) {
        print();
        return true;
    }
    int x = a / 9;
    int y = a % 9;
    if (arr[x][y] != 0) {
        return solve(a + 1);
    }
    bool check[9];
    for (int i = 0; i < 9; i++) {
        check[i] = false;
    }
    for (int i = 0; i < 9; i++) {
        if (arr[x][i] != 0) {
            check[arr[x][i] - 1] = true;
        }
        if (arr[i][y] != 0) {
            check[arr[i][y] - 1] = true;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[(x / 3) * 3 + i][(y / 3) * 3 + j] != 0) {
                check[arr[(x / 3) * 3 + i][(y / 3) * 3 + j] - 1] = true;
            }
        }
    }

    for (int i = 0; i < 9; i++) {
        if (!check[i]) {
            arr[x][y] = i + 1;
            if (solve(a + 1)) {
                return true;
            }
            arr[x][y] = 0;
        }
    }
    return false;
}

void init() {
    char ch;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> ch;
            if (ch == '0') {
                arr[i][j] = 0;
            } else {
                arr[i][j] = ch - '0';
            }
        }
    }
    solve(0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
}