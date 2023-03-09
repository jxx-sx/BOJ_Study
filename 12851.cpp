#include <iostream>
#include <queue>

using namespace std;

int n, k;
int arr[100100];
bool is_visit[100100];
queue<int> q;
int ans;

void solve() {
    while (!q.empty()) {
        if (q.front() * 2 < 100100)
            if (!is_visit[q.front() * 2]) {
                is_visit[q.front() * 2] = true;
                arr[q.front() * 2] = arr[q.front()] + 1;
                q.push(q.front() * 2);
            }
        if (q.front() - 1 >= 0)
            if (!is_visit[q.front() - 1]) {
                is_visit[q.front() - 1] = true;
                arr[q.front() - 1] = arr[q.front()] + 1;
                q.push(q.front() - 1);
            }
        if (q.front() + 1 < 100100)
            if (!is_visit[q.front() + 1]) {
                is_visit[q.front() + 1] = true;
                arr[q.front() + 1] = arr[q.front()] + 1;
                q.push(q.front() + 1);
            }
        q.pop();
    }

    if (arr[k] == arr[k - 1] + 1)
        ans++;
    if (arr[k] == arr[k + 1] + 1)
        ans++;
    if ((k & 1) == 0 and arr[k] == arr[k >> 1] + 1)
        ans++;
    cout << arr[k] << '\n' << ans;
}

void init() {
    cin >> n >> k;
    q.push(n);
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}