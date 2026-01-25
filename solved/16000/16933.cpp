#include <iostream>
#include <queue>

using namespace std;
struct Node {
    int b;
    int x;
    int y;
    int depth;
};
struct compare {
    bool operator()(Node a, Node b) {
        if (a.depth == b.depth)
            return a.b > b.b;
        return a.depth > b.depth;
    }
};

bool wall[1000][1000];
bool is_visit[11][1000][1000];
int n, m, k;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
priority_queue<Node, vector<Node>, compare> q;

bool valid(int x, int y) {
    if (x < 0 or n <= x)
        return false;
    if (y < 0 or m <= y)
        return false;
    return true;
}

void init() {
    char ch;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> ch;
            wall[i][j] = ch == '1';
        }

    for (int i = 0; i <= k; i++)
        is_visit[i][0][0] = true;

    Node first;
    first.x = first.y = first.b = 0;
    first.depth = 1;
    q.push(first);

    return;
}

void solve() {
    while (!q.empty()) {
        if (q.top().x == n - 1 and q.top().y == m - 1) {
            cout << q.top().depth;
            return;
        }
        for (int i = 0; i < 4; i++) {
            int tmp_x = q.top().x + dx[i];
            int tmp_y = q.top().y + dy[i];

            if (valid(tmp_x, tmp_y)) {
                if (wall[tmp_x][tmp_y]) {
                    if (q.top().b < k and !is_visit[q.top().b + 1][tmp_x][tmp_y]) {
                        is_visit[q.top().b + 1][tmp_x][tmp_y] = true;
                        Node tmp;
                        tmp.b = q.top().b + 1;
                        tmp.x = tmp_x;
                        tmp.y = tmp_y;
                        tmp.depth = q.top().depth + 1;
                        if (!(q.top().depth & 1))
                            tmp.depth++;

                        q.push(tmp);
                    }
                } else {
                    if (!is_visit[q.top().b][tmp_x][tmp_y]) {
                        is_visit[q.top().b][tmp_x][tmp_y] = true;
                        Node tmp;
                        tmp.b = q.top().b;
                        tmp.x = tmp_x;
                        tmp.y = tmp_y;
                        tmp.depth = q.top().depth + 1;
                        q.push(tmp);
                    }
                }
            }
        }

        q.pop();
    }
    cout << -1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}