#include <iostream>
#include <queue>
#include <stack>
#include <string>

using namespace std;
int a, b;
pair<int, char> arr[10000];
bool is_visit[10000];
queue<int> q;
stack<char> ans;

void init() {
    cin >> a >> b;
    for (int i = 0; i < 10000; i++) {
        arr[i] = {i, 0};
        is_visit[i] = false;
    }
    while (!q.empty()) {
        q.pop();
    }
    arr[a].first = -1;
    is_visit[a] = true;
    q.push(a);
    return;
}

int D(int x) { return (x * 2) % 10000; }

int S(int x) {
    if (x == 0)
        return 9999;
    return x - 1;
}

int L(int x) { return x % 1000 * 10 + x / 1000; }

int R(int x) { return x % 10 * 1000 + x / 10; }

void make_ans(int x) {
    if (arr[x].first == -1)
        return;
    ans.push(arr[x].second);
    make_ans(arr[x].first);
}

void print() {
    while (!ans.empty()) {
        cout << ans.top();
        ans.pop();
    }
    cout << '\n';
}

void solve() {
    int tmp;
    while (!q.empty()) {
        tmp = D(q.front());
        if (!is_visit[tmp]) {
            q.push(tmp);
            is_visit[tmp] = true;
            arr[tmp].first = q.front();
            arr[tmp].second = 'D';
        }
        tmp = S(q.front());
        if (!is_visit[tmp]) {
            q.push(tmp);
            is_visit[tmp] = true;
            arr[tmp].first = q.front();
            arr[tmp].second = 'S';
        }
        tmp = L(q.front());
        if (!is_visit[tmp]) {
            q.push(tmp);
            is_visit[tmp] = true;
            arr[tmp].first = q.front();
            arr[tmp].second = 'L';
        }
        tmp = R(q.front());
        if (!is_visit[tmp]) {
            q.push(tmp);
            is_visit[tmp] = true;
            arr[tmp].first = q.front();
            arr[tmp].second = 'R';
        }
        q.pop();
        if (is_visit[b])
            break;
    }
    make_ans(b);
    print();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        init();
        solve();
    }

    return 0;
}