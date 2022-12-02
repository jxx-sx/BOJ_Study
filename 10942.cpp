#include <iostream>

using namespace std;

int n;
int *arr;
bool **dp;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    arr = new int[n];
    dp = new bool *[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        dp[i] = new bool[n];
        dp[i][i] = true;
    }

    for (int i = 0; i < n - 1; i++) {
        dp[i][i + 1] = arr[i] == arr[i + 1];
    }

    for (int j = 2; j < n - 1; j++) {
        for (int i = 0; i < n - j; i++) {
            dp[i][i + j] = dp[i + 1][i + j - 1] and (arr[i] == arr[i + j]);
        }
    }
    int k, s, e;
    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> s >> e;
        if (dp[s - 1][e - 1])
            cout << "1\n";
        else
            cout << "0\n";
    }
}