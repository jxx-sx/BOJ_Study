#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n, arr[26];
vector<string> v;

void init() {
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
}

void solve() {
    for (auto a : v)
        arr[a[0] - 'a']++;
    bool flag = false;
    for (int i = 0; i < 26; i++)
        if (arr[i] >= 5) {
            cout << (char)('a' + i);
            flag = true;
        }
    if (!flag)
        cout << "PREDAJA";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}