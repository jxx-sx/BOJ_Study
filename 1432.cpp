#include <iostream>
#include <queue>

using namespace std;

bool matrix[50][50];
int in_degree[50];
int m[50];
char ch;
int n;
priority_queue<int> pq;

int bfs() {
    int rtn = 0;
    int cur;
    for (int i = 0; i < n; i++)
        if (in_degree[i] == 0)
            pq.push(-i);
    while (!pq.empty()) {
        cur = -pq.top();
        pq.pop();
        rtn++;
        m[cur] = rtn;
        for (int i = 0; i < n; i++) {
            if (matrix[cur][i]) {
                in_degree[i]--;
                if (in_degree[i] == 0)
                    pq.push(-i);
            }
        }
    }
    return rtn;
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> ch;
            matrix[i][j] = ch == '1';
            if (matrix[i][j])
                in_degree[j] += 1;
        }

    return;
}

void solve() {
    if (n != bfs())
        cout << -1;
    else
        for (int i = 0; i < n; i++)
            cout << m[i] << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}