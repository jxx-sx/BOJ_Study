#include <iostream>

using namespace std;

int arr[5][5], matrix[5][5];
int a, b;

void print() {
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++)
            cout << matrix[i][j] << ' ';
        cout << '\n';
    }
}

void matrix_mul(int f[5][5], int s[5][5]) {
    int tmp[5][5];
    for (int i = 0; i < a; i++)
        for (int j = 0; j < a; j++) {
            tmp[i][j] = 0;
            for (int k = 0; k < a; k++) {
                tmp[i][j] += f[i][k] * s[k][j];
                tmp[i][j] %= 1000;
            }
        }
    for (int i = 0; i < a; i++)
        for (int j = 0; j < a; j++)
            matrix[i][j] = tmp[i][j];
}

void d_c(int x) {
    if (x <= 1)
        return;
    d_c(x >> 1);
    matrix_mul(matrix, matrix);
    if ((x & 1))
        matrix_mul(matrix, arr);
}

void init() {
    cin >> a >> b;
    for (int i = 0; i < a; i++)
        for (int j = 0; j < a; j++) {
            cin >> arr[i][j];
            matrix[i][j] = arr[i][j];
        }
    return;
}

void solve() {
    d_c(b);
    print();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
    return 0;
}