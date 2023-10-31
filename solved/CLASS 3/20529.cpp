#include <iostream>
#include <memory.h>
#include <string>

#define ESTJ "ESTJ"

using namespace std;

int n, cnt[16];

int get_dist(int a, int b) {
    int ret = 0;
    for (int i = 0; i < 4; i++) {
        if ((1 << i) & (a ^ b))
            ret++;
    }
    return ret;
}

int normalize(string st) {
    int ret = 0;
    for (int i = 0; i < 4; i++)
        ret |= (ESTJ[i] != st[i] ? (1 << i) : 0);
    return ret;
}

void init() {
    string mbti;
    cin >> n;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) {
        cin >> mbti;
        cnt[normalize(mbti)]++;
    }
}

void solve() {
    int ans = 12;
    for (int i = 0; i < 16; i++) {
        if (cnt[i] >= 3) {
            cout << "0\n";
            return;
        }
        if (cnt[i] == 2) {
            for (int j = 0; j < 16; j++) {
                if (cnt[j] and i != j)
                    ans = min(ans, 2 * get_dist(i, j));
            }
        }
    }
    for (int i = 0; i < 16; i++)
        for (int j = i + 1; j < 16; j++)
            for (int k = j + 1; k < 16; k++) {
                if (cnt[i] and cnt[j] and cnt[k])
                    ans = min(ans, get_dist(i, j) + get_dist(j, k) + get_dist(k, i));
            }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    for (int i = 0; i < tc; i++) {
        init();
        solve();
    }

    return 0;
}