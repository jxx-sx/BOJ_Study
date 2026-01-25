#include <iostream>
#include <stack>
#include <string>

using namespace std;

stack<bool> st;
long long ans;

void init() {}

void solve() {
    string s;
    bool is_lazer = false;
    cin >> s;
    for (auto a : s) {
        if (a == '(') {
            is_lazer = true;
            st.push(true);
            ans++;
        } else {
            st.pop();
            if (is_lazer) {
                ans--;
                ans += st.size();
            }
            is_lazer = false;
        }
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