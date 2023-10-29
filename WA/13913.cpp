#include <iostream>
#include <queue>
#include <vector>

using namespace std;

pair<int, int> arr[100001]; // depth, origin
queue<int> q;
int n, k;

void query(int x, int cur) {
    if (x < 0)
        return;
    if (x > 100000)
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
        if (k < q.front()) {
            q.pop();
            continue;
        }
        query(2 * q.front(), q.front());
        query(q.front() + 1, q.front());
        q.pop();
    }
    cout << arr[k].first << '\n';
    vector<int> st;
    st.push_back(k);
    while (st.back() != n)
        st.push_back(arr[st.back()].second);
    while (st.size()) {
        cout << st.back() << ' ';
        st.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}