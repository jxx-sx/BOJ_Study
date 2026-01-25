#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N, M, ans = 0;
vector<int> *v;
bool *check;
queue<int> q;

void solve() {
    for (int i = 1; i < N + 1; i++) {
        if (!check[i]) {
            ans += 1;

            for (int j = 0; j < v[i].size(); j++) {
                q.push(v[i][j]);
            }
            check[i] = true;
            while (!q.empty()) {
                int cur = q.front();
                q.pop();
                if (!check[cur]) {
                    for (int j = 0; j < v[cur].size(); j++) {
                        q.push(v[cur][j]);
                    }
                    check[cur] = true;
                }
            }
        }
    }
    cout << ans;
}

void init() {
    int a, b;
    cin >> N >> M;
    v = new vector<int>[N + 1];
    check = new bool[N + 1];
    for (int i = 0; i < N + 1; i++) {
        check[i] = false;
    }

    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }

    for (int i = 1; i < N + 1; i++) {
        sort(v[i].begin(), v[i].end());
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}