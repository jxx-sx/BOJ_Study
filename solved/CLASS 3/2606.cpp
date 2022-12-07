#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N, ans = 0;
vector<int> *v;
bool *check;
queue<int> q;

void solve() {
    for (int i = 0; i < v[1].size(); i++) {
        q.push(v[1][i]);
    }
    check[1] = true;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (!check[cur]) {
            for (int i = 0; i < v[cur].size(); i++) {
                q.push(v[cur][i]);
            }
            check[cur] = true;
            ans += 1;
        }
    }
    cout << ans;
}

void init() {
    int a, b, tmp;
    cin >> N >> tmp;
    v = new vector<int>[N + 1];
    check = new bool[N + 1];
    for (int i = 0; i < N; i++) {
        check[i] = false;
    }

    for (int i = 0; i < tmp; i++) {
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}