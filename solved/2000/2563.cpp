#include <iostream>

using namespace std;

bool arr[100][100];
int n;

void init() {
    int x, y;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        for (int j = 0; j < 10; j++)
            for (int k = 0; k < 10; k++)
                arr[x + j][y + k] = true;
    }
}

void solve() {
    int ans = 0;
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            if (arr[i][j])
                ans++;
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}