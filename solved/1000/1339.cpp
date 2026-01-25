#include <algorithm>
#include <iostream>
#include <string>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n;
int arr[26];
string st[10];

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> st[i];
}

void solve() {
    for (int i = 0; i < n; i++)
        for (int j = st[i].size() - 1, cur = 1; j >= 0; j--, cur *= 10)
            arr[st[i][j] - 'A'] -= cur;
    sort(arr, arr + 26);
    int sum = 0;
    for (int i = 0; i < 9; i++)
        sum -= arr[i] * (9 - i);
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}