#include <iostream>
#include <queue>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

priority_queue<int> pq;
int n, x, a, ans;

void init() {
    cin >> n >> x;
    for (int i = 1; i < n; i++) {
        cin >> a;
        pq.push(a);
    }
}

void solve() {
    if (n == 1) {
        cout << 0;
        return;
    }
    while (x <= pq.top()) {
        a = pq.top();
        pq.pop();
        pq.push(a - 1);
        x++;
        ans++;
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    init(), solve();

    return 0;
}