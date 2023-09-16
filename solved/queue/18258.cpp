#include <iostream>
#include <queue>
#include <string>

using namespace std;

queue<int> q;
int n;

void init() { cin >> n; }

void solve() {
    string op;
    int num;
    while (n--) {
        cin >> op;
        if (op == "push") {
            cin >> num;
            q.push(num);
        }
        if (op == "pop") {
            cout << (q.empty() ? -1 : q.front()) << '\n';
            if (q.size())
                q.pop();
        }
        if (op == "size")
            cout << q.size() << '\n';
        if (op == "empty")
            cout << q.empty() << '\n';
        if (op == "front")
            cout << (q.empty() ? -1 : q.front()) << '\n';
        if (op == "back")
            cout << (q.empty() ? -1 : q.back()) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}