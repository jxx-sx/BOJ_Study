#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n, m;
vector<string> v1, v2, v3;

void solve() {
    int i, j;
    i = j = 0;
    while (i != n && j != m) {
        if (v1[i] == v2[j]) {
            v3.push_back(v1[i]);
            i += 1;
            j += 1;
        } else if (v1[i] < v2[j]) {
            i += 1;
        } else {
            j += 1;
        }
    }
    cout << v3.size() << '\n';
    for (i = 0; i < v3.size(); i++) {
        cout << v3[i] << '\n';
    }
}

void init() {
    string tmp;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        v1.push_back(tmp);
    }

    for (int i = 0; i < m; i++) {
        cin >> tmp;
        v2.push_back(tmp);
    }
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}