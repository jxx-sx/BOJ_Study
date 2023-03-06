#include <iostream>
#include <queue>

using namespace std;

priority_queue<pair<int, int>> pq;
int a, b;

void init() { cin >> a >> b; }

void solve() {
    int cnt = 0;
    while (b >= a) {
        if (a == b) {
            cout << cnt + 1;
            return;
        }
        if (b & 1)
            b /= 10;
        else
            b >>= 1;
        cnt++;
    }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}