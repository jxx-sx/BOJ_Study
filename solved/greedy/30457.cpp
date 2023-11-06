#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n;
vector<int> v;
deque<int> dq;
void init() {
    cin >> n;
    v.resize(n);
    for (auto &a : v)
        cin >> a;
    sort(v.begin(), v.end());
}

void solve() {
    while (v.size()) {
        if (dq.size() < 2) {
            dq.push_back(v.back());
        } else if (dq.front() > v.back()) {
            dq.push_front(v.back());

        } else if (dq.back() > v.back()) {
            dq.push_back(v.back());
        }
        v.pop_back();
    }
    cout << dq.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}