#include <iostream>

using namespace std;

int arr[10][1000];
int n;

void init() {
    cin >> n;
    for (int i = 0; i < 10; i++)
        arr[i][0] = 1;
}

void solve() {
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k <= j; k++)
                arr[j][i] += arr[k][i - 1];
            arr[j][i] %= 10007;
        }
    }

    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += arr[i][n - 1];
        sum %= 10007;
    }
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}