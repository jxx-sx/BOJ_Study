#include <iostream>

using namespace std;

int n, s, r;
bool arr[11];
void init() {
    int a;
    cin >> n >> s >> r;
    for (int i = 0; i < s; i++) {
        cin >> a;
        arr[a] = true;
    }
    return;
}

void solve() {
    int a;
    for (int i = 0; i < r; i++) {
        cin >> a;
        if (arr[a]) {
            arr[a] = false;
            continue;
        }
        if (a > 0)
            if (arr[a - 1]) {
                arr[a - 1] = false;
                continue;
            }
        if (a < 10)
            if (arr[a + 1]) {
                arr[a + 1] = false;
                continue;
            }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++)
        if (arr[i])
            ans += 1;
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}