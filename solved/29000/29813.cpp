#include <iostream>
#include <queue>
#include <string>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
queue<pair<string, int>> q;
int n;

void init() {
    cin >> n;
    string st;
    int x;
    for (int i = 0; i < n; i++) {
        cin >> st >> x;
        q.push({st, x});
    }
}

void solve() {
    while (q.size() > 1) {
        int cnt = q.front().second - 1;
        q.pop();
        while (cnt--) {
            q.push(q.front());
            q.pop();
        }
        q.pop();
    }
    cout << q.front().first;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    init(), solve();

    return 0;
}
