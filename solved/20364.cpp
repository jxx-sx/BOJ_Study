#include <iostream>

using namespace std;

int n, q;
bool visited[1 << 20];

void init() { cin >> n >> q; }

void solve() {
    int x, tmp;
    while (q--) {
        cin >> x;
        tmp = x;
        int ans = 0;
        while (x) {
            if (visited[x])
                ans = x;
            x >>= 1;
        }
        if (!ans)
            visited[tmp] = true;
        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}