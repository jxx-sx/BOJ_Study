#include <iostream>
#include <queue>

using namespace std;
int n;
priority_queue<int> pq;

void solve() {
    int inp;
    for (int i = 0; i < n; i++) {
        cin >> inp;
        if (inp == 0) {
            if (pq.empty())
                cout << "0\n";
            else {
                cout << -pq.top() << '\n';
                pq.pop();
            }
        } else {
            pq.push(-inp);
        }
    }
}

void init() { cin >> n; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}