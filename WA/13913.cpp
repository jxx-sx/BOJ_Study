#include <iostream>
#include <queue>
#include <vector>

using namespace std;

pair<int, int> arr[200001]; // depth, origin
queue<int> q;
int n, k;

void query(int x, int cur) {
    if (x < 0)
        return;
    if (x > 200000)
        return;
    if (arr[x].second)
        return;
    arr[x].first = arr[cur].first + 1;
    arr[x].second = cur;
    q.push(x);
}

void init() {
    cin >> n >> k;
    arr[n].second = n;
    q.push(n);
}

void solve() {
    while (q.front() != k) {
        query(q.front() - 1, q.front());
        query(2 * q.front(), q.front());
        query(q.front() + 1, q.front());
        q.pop();
    }

    int cur = k;
    cout << arr[k].first << '\n';
    vector<int> st(arr[k].first);
    for (auto &a : st) {
        a = arr[cur].second;
        cur = a;
    }
    while (st.size()) {
        cout << st.back() << ' ';
        st.pop_back();
    }
    cout << k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}