#include <iostream>
#include <vector>

using namespace std;

int n, *arr;
vector<int> *v;

void solve(int a) {
    for (int i = 0; i < v[a].size(); i++) {
        if (arr[v[a][i]] == -1) {
            arr[v[a][i]] = a;
            solve(v[a][i]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    arr = new int[n + 1];
    for (int i = 2; i < n + 1; i++)
        arr[i] = -1;
    arr[0] = arr[1] = 1;
    v = new vector<int>[n + 1];
    int a, b;
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    solve(1);
    for (int i = 2; i < n + 1; i++) {
        cout << arr[i] << '\n';
    }
}