#include <iostream>
#include <string>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

string st;
int dp[5001];

void init() {
    cin >> st;
    dp[0] = 1;
    dp[1] = st[0] == '0' ? 0 : 1;
}

void solve() {
    for (int i = 1; i < st.size(); i++) {
        if (st[i] != '0')
            dp[i + 1] += dp[i];
        int x = stoi(st.substr(i - 1, 2));
        if (9 < x and x <= 26)
            dp[i + 1] += dp[i - 1];
        dp[i + 1] %= 1000000;
    }
    cout << dp[st.size()];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}