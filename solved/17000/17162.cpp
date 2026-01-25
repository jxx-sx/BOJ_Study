#include <iostream>
#include <vector>

using namespace std;

int q, mod;
vector<int> st, v[100];

void query() {
    int ans = st.size();
    for (int i = 0; i < mod; i++) {
        if (v[i].empty()) {
            cout << -1 << '\n';
            return;
        }
        ans = min(ans, v[i].back());
    }
    cout << st.size() - ans << '\n';
}

void init() { cin >> q >> mod; }

void solve() {
    int a, b;
    while (q--) {
        cin >> a;
        if (a == 1) {
            cin >> b;
            b %= mod;
            v[b].push_back(st.size());
            st.push_back(b);
        }
        if (a == 2) {
            if (st.empty())
                continue;
            v[st.back()].pop_back();
            st.pop_back();
        }
        if (a == 3)
            query();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}