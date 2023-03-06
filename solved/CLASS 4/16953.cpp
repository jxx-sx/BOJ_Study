#include <iostream>
#include <queue>

using namespace std;

priority_queue<pair<int, int>> pq;
int a, b;

void init() { cin >> a >> b; }

void solve() {
    int cnt = 1;
    while (b >= a) {
        if (a == b) {
            cout << cnt;
            return;
        }
        if ((b & 1) == 0)
            b >>= 1;
        else if (b % 10 == 1)
            b /= 10;
        else
            break;
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