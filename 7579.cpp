#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m, sumM = 0, sumC = 0;
vector<int> vM, vC;

void solve() {
    int arr[n + 1][sumM - m + 1];
    for (int i = 0; i < n + 1; i++)
        for (int j = 0; j <= sumM - m; j++)
            arr[i][j] = sumC;

    for (int i = 1; i < n + 1; i++) {
        for (int j = vM[i - 1]; j <= sumM - m; j++) {
            arr[i][j] = min(arr[i - 1][j - vM[i - 1]] - vC[i - 1], arr[i - 1][j]);
        }
    }

    cout << arr[n][sumM - m];
}

void init() {
    int inp;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> inp;
        vM.push_back(inp);
        sumM += inp;
    }
    for (int i = 0; i < n; i++) {
        cin >> inp;
        vC.push_back(inp);
        sumC += inp;
    }

    solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
}