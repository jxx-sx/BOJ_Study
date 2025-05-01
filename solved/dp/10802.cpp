#include <iostream>
#include <string>

#define N 100001
#define M 20150523

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;
ll dp[N][4];
string a, b;

int is_include() {
    int ret = 0;
    for (auto i : a) {
        if (i == '3' || i == '6' || i == '9')
            return 1;
        ret += i - '0';
    }
    return ret % 3 ? 0 : 1;
}

ll mod(string num) {
    ll ret = 0;
    for (auto i : num)
        ret = (ret * 10 + i - '0') % M;
    return ret;
}

ll g(string num) {
    ll ret = 0;
    ll cur_mod = 0;
    for (int i = 0; i < num.size() - 1; i++) {
        for (int j = 0; j < num[i] - '0'; j++) {
            if (j && j % 3 == 0)
                continue;
            ret += dp[num.size() - i - 1][3] - dp[num.size() - i - 1][(3 - (j + cur_mod) % 3) % 3];
        }
        ret %= M;
        cur_mod = (cur_mod + num[i] - '0') % 3;
        if (num[i] == '3' || num[i] == '6' || num[i] == '9')
            return ret;
    }
    for (int i = 0; i <= num.back() - '0'; i++) {
        if (i && i % 3 == 0)
            continue;
        if ((cur_mod + i) % 3)
            ret++;
    }
    return ret % M;
}

void init() {
    dp[1][0] = 1;
    dp[1][1] = 3;
    dp[1][2] = 3;
    dp[1][3] = 7;
    for (int i = 2; i < N; i++) {
        dp[i][0] = (dp[i - 1][0] + dp[i - 1][1] * 3 + dp[i - 1][2] * 3) % M;
        dp[i][1] = (dp[i - 1][0] * 3 + dp[i - 1][1] + dp[i - 1][2] * 3) % M;
        dp[i][2] = (dp[i - 1][0] * 3 + dp[i - 1][1] * 3 + dp[i - 1][2]) % M;
        dp[i][3] = (dp[i][0] + dp[i][1] + dp[i][2]) % M;
    }
    cin >> a >> b;
}

void solve() {
    ll ans = ((mod(b) - g(b)) - (mod(a) - g(a)) + is_include()) % M;
    cout << (ans + M) % M;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    init();
    solve();

    return 0;
}