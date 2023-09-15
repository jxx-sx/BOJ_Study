#include <iostream>
#include <stack>

using namespace std;

stack<pair<char, long long>> st;

void init() { st.push({0, 0}); }

void solve() {
    char ch;
    while (cin >> ch) {
        if (ch == '(' or ch == '[') {
            st.push({ch, 0});
            continue;
        }
        if (st.size() == 1 or ch - (ch > 90 ? 2 : 1) != st.top().first) {
            cout << 0;
            return;
        }
        if (st.top().second == 0) {
            st.pop();
            st.top().second += ch == ')' ? 2 : 3;
        } else {
            auto tmp = st.top().second * (ch == ')' ? 2 : 3);
            st.pop();
            st.top().second += tmp;
        }
    }

    cout << (st.size() != 1 ? 0 : st.top().second);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}