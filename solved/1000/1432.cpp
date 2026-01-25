#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool matrix[50][50];
int out_degree[50];
int m[50];
int n, ord;
priority_queue<int> pq;

void bfs() {
    int cur;
    for (int i = 0; i < n; i++)
        if (out_degree[i] == 0) {
            pq.push(i);
        }

    while (!pq.empty()) {
        cur = pq.top();
        pq.pop();
        m[cur] = ord;
        ord--;
        for (int i = 0; i < n; i++)
            if (matrix[i][cur]) {
                out_degree[i]--;
                if (out_degree[i] == 0) {
                    pq.push(i);
                }
            }
    }
}

void init() {
    char ch;
    cin >> n;
    ord = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> ch;
            matrix[i][j] = ch == '1';
            if (matrix[i][j])
                out_degree[i] += 1;
        }

    return;
}

void solve() {
    bfs();
    if (ord)
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