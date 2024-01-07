#include <iostream>
#include <queue>
#include <vector>

using namespace std;

queue<int> q;
vector<int> edges[26];
int c[100][100];
int f[100][100];
int level[26];
int work[100];
int s, t = 25;

bool bfs() {
    for (int i = 0; i < 26; i++)
        level[i] = -1;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        for (auto a : edges[q.front()])
            if (level[a] == -1 and c[q.front()][a] - f[q.front()][a] > 0) {
                level[a] = level[q.front()] + 1;
                q.push(a);
            }
        q.pop();
    }
    return level[t] != -1;
}

int dfs(int x, int d) {}

void init() {}

void solve() {}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}