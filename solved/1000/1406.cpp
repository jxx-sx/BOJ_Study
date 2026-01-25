#include <iostream>
#include <stack>
#include <string>

using namespace std;

int m;
stack<char> l, r;

void init() {
    string st;
    cin >> st;
    for (auto a : st)
        l.push(a);
    cin >> m;
}

void solve() {
    char op;
    while (m--) {
        cin >> op;
        if (op == 'L' and l.size()) {
            r.push(l.top());
            l.pop();
        }
        if (op == 'D' and r.size()) {
            l.push(r.top());
            r.pop();
        }
        if (op == 'B' and l.size())
            l.pop();
        if (op == 'P') {
            cin >> op;
            l.push(op);
        }
    }
    while (l.size()) {
        r.push(l.top());
        l.pop();
    }
    while (r.size()) {
        cout << r.top();
        r.pop();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}