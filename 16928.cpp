#include <iostream>
#include <queue>

using namespace std;

int n, m, arr[101];
bool check[101];

void solve() {
    priority_queue<int> pq;
    int next, cur, cnt = 0;
    pq.push(1);
    while (true) {
        priority_queue<int> tmp;
        while (!pq.empty()) {
            cur = pq.top();

            pq.pop();
            if (cur == 100) {
                cout << cnt;
                return;
            }
            for (int i = 1; i <= 6; i++) {
                if (cur + i <= 100) {
                    next = cur + i;
                    if (arr[next])
                        next = arr[next];
                    tmp.push(next);
                }
            }
        }
        pq = tmp;
        cnt += 1;
    }

    return;
}

void init() {
    for (int i = 0; i < 101; i++) {
        arr[i] = 0;
        check[i] = false;
    }

    int s, e;
    cin >> n >> m;
    for (int i = 0; i < n + m; i++) {
        cin >> s >> e;
        arr[s] = e;
    }

    solve();
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    init();

    return 0;
}