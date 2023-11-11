#include <iostream>
#include <stack>

using namespace std;

int n;
stack<int> st;

void init() { cin >> n; }

void solve() {
    int a, b;
    while (n--) {
        cin >> a;
        if (a == 1) {
            cin >> b;
            st.push(b);
        }
        if (a == 2) {
            if (st.size()) {
                cout << st.top() << '\n';
                st.pop();
            } else
                cout << "-1\n";
        }
        if (a == 3)
            cout << st.size() << '\n';
        if (a == 4)
            cout << (st.empty() ? "1\n" : "0\n");
        if (a == 5)
            cout << (st.size() ? st.top() : -1) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}