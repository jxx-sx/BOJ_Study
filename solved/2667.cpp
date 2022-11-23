#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n, count = 0;
bool **arr;

int dfs(int x, int y, int z) {
    if (!arr[x][y])
        return z;
    arr[x][y] = false;
    z += 1;
    if (y >= 1) {
        z = dfs(x, y - 1, z);
    }
    if (x >= 1) {
        z = dfs(x - 1, y, z);
    }
    if (x <= n - 2) {
        z = dfs(x + 1, y, z);
    }
    if (y <= n - 2) {
        z = dfs(x, y + 1, z);
    }
    return z;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    string inp;
    arr = new bool *[n];

    for (int i = 0; i < n; i++) {
        arr[i] = new bool[n];
        cin >> inp;
        for (int j = 0; j < n; j++) {
            if (inp[j] == '0') {
                arr[i][j] = false;
            } else {
                arr[i][j] = true;
            }
        }
    }
    vector<int> v;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j]) {
                v.push_back(dfs(i, j, 0));
            }
        }
    }
    sort(v.begin(), v.end());
    cout << v.size() << '\n';
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << '\n';
    }
}