#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

string str1, str2;

void hirschberg(int s1 = 0, int e1 = str1.size() - 1, int s2 = 0, int e2 = str2.size() - 1) {
    if (s1 == e1) {
        if (e2 < s2) {
            cout << "d " << str1[s1] << '\n';
            return;
        }
        int idx = -1;
        for (int i = s2; i <= e2; i++) {
            if (str1[s1] == str2[i]) {
                idx = i;
                break;
            }
        }
        for (int i = s2; i < e2; i++)
            cout << (idx == i ? "c " : "a ") << str2[i] << '\n';
        cout << (idx == -1 ? "m " : (idx == e2 ? "c " : "a ")) << str2[e2] << '\n';
        return;
    }
    int m = (s1 + e1) >> 1;
    int len = e2 - s2 + 1;
    vector<int> upper(len + 2), lower(len + 2), prev(len + 2);
    for (int i = 1; i <= len + 1; i++)
        prev[i] = i;
    for (int i = s1; i <= m; i++) {
        upper[0] = i - s1 + 1;
        for (int j = s2; j <= e2; j++)
            upper[j - s2 + 1] = min({prev[j - s2 + 1] + 1, upper[j - s2] + 1, prev[j - s2] + (str1[i] == str2[j] ? 0 : 1)});
        prev = upper;
    }
    for (int i = 0; i <= len + 1; i++)
        prev[len - i + 1] = i;
    for (int i = e1; i >= m + 1; i--) {
        lower[len + 1] = e1 - i + 1;
        for (int j = e2; j >= s2; j--)
            lower[j - s2 + 1] = min({prev[j - s2 + 1] + 1, lower[j - s2 + 2] + 1, prev[j - s2 + 2] + (str1[i] == str2[j] ? 0 : 1)});
        prev = lower;
    }

    int mnv = 1'000'000'000;
    int h = 0;
    for (int i = s2 - 1; i <= e2; i++) {
        if (mnv >= upper[i - s2 + 1] + lower[i - s2 + 2]) {
            mnv = upper[i - s2 + 1] + lower[i - s2 + 2];
            h = i;
        }
    }
    hirschberg(s1, m, s2, h);
    hirschberg(m + 1, e1, h + 1, e2);
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    cin >> str1 >> str2;
    hirschberg();

    return 0;
}