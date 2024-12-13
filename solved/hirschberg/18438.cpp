#include <iostream>
#include <string>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

string str1, str2, ans;

void hirschberg(int s1, int e1, int s2, int e2) {
    if (s1 == e1) {
        for (int i = s2; i <= e2; i++) {
            if (str1[s1] == str2[i]) {
                ans += str1[s1];
                break;
            }
        }
        return;
    }
    int m = (s1 + e1) >> 1;
    int len = e2 - s2 + 1;
    vector<int> upper(len + 2), lower(len + 2), prev(len + 2);
    for (int i = s1; i <= m; i++) {
        for (int j = s2; j <= e2; j++) {
            if (str1[i] == str2[j])
                upper[j - s2 + 1] = prev[j - s2] + 1;
            else
                upper[j - s2 + 1] = max(prev[j - s2 + 1], upper[j - s2]);
        }
        prev = upper;
    }
    prev = vector<int>(len + 2);
    for (int i = e1; i >= m + 1; i--) {
        for (int j = e2; j >= s2; j--) {
            if (str1[i] == str2[j])
                lower[j - s2 + 1] = prev[j - s2 + 2] + 1;
            else
                lower[j - s2 + 1] = max(prev[j - s2 + 1], lower[j - s2 + 2]);
        }
        prev = lower;
    }

    int mxv = -1;
    int h = 0;
    for (int i = s2 - 1; i <= e2; i++) {
        if (mxv <= upper[i - s2 + 1] + lower[i - s2 + 2]) {
            mxv = upper[i - s2 + 1] + lower[i - s2 + 2];
            h = i;
        }
    }
    hirschberg(s1, m, s2, h);
    hirschberg(m + 1, e1, h + 1, e2);
}

void init() { cin >> str1 >> str2; }

void solve() {
    hirschberg(0, str1.size() - 1, 0, str2.size() - 1);
    cout << ans.size() << '\n' << ans;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    init();
    solve();

    return 0;
}