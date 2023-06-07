#include <iostream>

using namespace std;

int wine[10001];
int arr[3][10001];
int n;

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> wine[i];

    arr[2][1] = arr[1][1] = wine[1];
    for (int i = 2; i <= n; i++) {
        arr[0][i] = max(arr[0][i - 1], max(arr[1][i - 1], arr[2][i - 1]));
        arr[1][i] = wine[i] + arr[0][i - 1];
        arr[2][i] = wine[i] + arr[1][i - 1];
    }
}

void solve() { cout << max(arr[0][n], max(arr[1][n], arr[2][n])); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}