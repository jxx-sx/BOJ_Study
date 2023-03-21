#include <iostream>
#include <stack>

using namespace std;
stack<bool> s;
stack<int> st;

void init() { return; }

void solve() {
    char ch;
    while (cin >> ch) {
        if (ch == 'P') {
            if (st.empty()) {
                st.push(1);
                s.push(true);
            } else if (st.top() == 3) {
                st.pop();
                s.pop();
                st.pop();
                s.pop();
            } else {
                st.push(2);
                s.push(true);
            }
        } else {
            if (st.empty()) {
                cout << "NP";
                return;
            }
            if (st.top() != 2) {
                cout << "NP";
                return;
            }
            st.push(3);
            s.push(false);
        }
    }
    if (s.size() == 1 and s.top())
        cout << "PPAP";
    else
        cout << "NP";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}