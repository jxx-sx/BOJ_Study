#include <iostream>

using namespace std;

int n;
bool **arr;
void init() {
    cin >> n;
    arr = new bool *[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new bool[n];
    }

    char tmp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> tmp;
            if (tmp == '1')
                arr[i][j] = true;
            else
                arr[i][j] = false;
        }
    }
}

void solve(int a, int b, int nn) {
    bool flag, tmp = arr[a][b];
    flag = false;
    for (int i = a; i < a + nn; i++) {
        for (int j = b; j < b + nn; j++) {
            if (tmp != arr[i][j]) {
                flag = true;
                break;
            }
        }
        if (flag) {
            break;
        }
    }
    if (flag) {
        cout << '(';

        solve(a, b, nn / 2);
        solve(a, b + nn / 2, nn / 2);
        solve(a + nn / 2, b, nn / 2);
        solve(a + nn / 2, b + nn / 2, nn / 2);
        cout << ')';

    } else {
        cout << tmp;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve(0, 0, n);
}