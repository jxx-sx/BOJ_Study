#include <iostream>

using namespace std;

long long arr[2][90];
int n;

void init() {
    arr[1][0] = 1;
    cin >> n;
}

void solve() {
    for (int i = 1; i < n; i++) {
        arr[1][i] = arr[0][i - 1];
        arr[0][i] = arr[1][i - 1] + arr[0][i - 1];
    }
    cout << arr[0][n - 1] + arr[1][n - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}