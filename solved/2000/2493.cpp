#include <iostream>
#include <vector>

using namespace std;

vector<int> v, ans;
vector<pair<int, int>> st;
int n;

void init() {
    cin >> n;
    v.resize(n);
    ans.resize(n + 1);
    for (auto &a : v)
        cin >> a;
}

void solve() {
    while (v.size()) {
        while (st.size()) {
            if (st.back().first > v.back())
                break;
            ans[st.back().second] = v.size();
            st.pop_back();
        }
        st.push_back({v.back(), v.size()});
        v.pop_back();
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}