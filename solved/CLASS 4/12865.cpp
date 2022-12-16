#include <iostream>
#include <vector>
using namespace std;
int n, m;
int arr[101][100001];
vector<pair<int, int>> v;

void solve() {
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            if (v[i - 1].first <= j) {
                arr[i][j] = max(arr[i - 1][j], arr[i - 1][j - v[i - 1].first] + v[i - 1].second);
            } else
                arr[i][j] = arr[i - 1][j];
        }
    }
    cout << arr[n][m];
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        v.push_back({0, 0});
        cin >> v[i].first >> v[i].second;
        arr[i][0] = 0;
    }
    arr[n][0] = 0;
    for (int i = 0; i <= m; i++)
        arr[0][i] = 0;

    solve();
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
}