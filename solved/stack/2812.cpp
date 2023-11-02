#include <iostream>
#include <stack>
#include <string>

using namespace std;

string num;
int n, k;
stack<char> st, ans;

void init() { cin >> n >> k >> num; }

void solve() {
    for (auto a : num) {
        while (st.size() and k) {
            if (a <= st.top())
                break;
            k--;
            st.pop();
        }
        st.push(a);
    }
    while (k--)
        st.pop();

    while (!st.empty()) {
        ans.push(st.top());
        st.pop();
    }
    while (!ans.empty()) {
        cout << ans.top();
        ans.pop();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}