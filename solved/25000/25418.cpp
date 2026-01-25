#include <iostream>
#include <queue>

using namespace std;
queue<pair<int, int>> q;

int a, k;
bool arr[1000001];

void init() {
    cin >> a >> k;
    q.push({a, 0});
}

void solve() {
    while (true) {
        if (q.front().first + 1 == k or q.front().first * 2 == k) {
            cout << q.front().second + 1;
            break;
        }
        if (q.front().first * 2 < k and !arr[q.front().first * 2]) {
            q.push({q.front().first * 2, q.front().second + 1});
            arr[q.front().first * 2] = true;
        }
        if (!arr[q.front().first + 1]) {
            q.push({q.front().first + 1, q.front().second + 1});
            arr[q.front().first + 1] = true;
        }
        q.pop();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}