#include <iostream>
#include <queue>

using namespace std;

priority_queue<long long> pq;
int n;
void init() {
    long long inp;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> inp;
        pq.push(-inp);
    }
    return;
}

void solve() {
    long long ans = 0;
    while (pq.size() != 1) {
        long long a = pq.top();
        pq.pop();
        a += pq.top();
        pq.pop();
        pq.push(a);
        ans -= a;
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
