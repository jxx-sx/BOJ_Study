#include <iostream>
#include <string>

using namespace std;

int arr[4001][4001];
string a, b;
int ans;

void init() { cin >> a >> b; }

void solve() {
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b.size(); j++) {
            arr[i + 1][j + 1] = a[i] == b[j] ? arr[i][j] + 1 : 0;
            ans = max(arr[i + 1][j + 1], ans);
        }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}