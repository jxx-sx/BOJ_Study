#include <iostream>
#define MAX 1000

using namespace std;
int **arr;
int n, m;

void solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int l = j + 1; l < n; l++) {
                if (j != i && l != i) {
                    int tmp = arr[i][j] + arr[i][l];
                    arr[j][l] = arr[l][j] = (tmp < arr[j][l]) ? tmp : arr[j][l];
                }
            }
        }
    }

    pair<int, int> ans = {0, MAX};
    for (int i = 0; i < n; i++) {
        int tmp = 0;
        for (int j = 0; j < n; j++) {
            tmp += arr[i][j];
        }
        if (tmp < ans.second) {
            ans = {i + 1, tmp};
        }
    }
    cout << ans.first;
}

void init() {
    cin >> n >> m;
    arr = new int *[n];

    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
        for (int j = 0; j < n; j++) {
            arr[i][j] = 1000;
        }
        arr[i][i] = 0;
    }
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        arr[a - 1][b - 1] = arr[b - 1][a - 1] = 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
}