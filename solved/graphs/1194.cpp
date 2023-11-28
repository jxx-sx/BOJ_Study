#include <iostream>
#include <queue>

using namespace std;
struct Cur {
    int depth;
    int x;
    int y;
    int key;
};

struct compare {
    bool operator()(Cur a, Cur b) {
        if (a.depth == b.depth)
            return a.x == b.x ? a.y > b.y : a.x > b.x;
        return a.depth > b.depth;
    }
};

priority_queue<Cur, vector<Cur>, compare> pq;

bool is_visit[(1 << 6) + 1][50][50];
char arr[50][50];
int n, m;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool valid(int x, int y) {
    if (x < 0 or n <= x)
        return false;
    if (y < 0 or m <= y)
        return false;
    return true;
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == '0') {
                Cur cur;
                cur.depth = 0;
                cur.x = i;
                cur.y = j;
                cur.key = 0;
                pq.push(cur);
            }
        }
    return;
}

void solve() {
    while (!pq.empty()) {
        Cur cur = pq.top();
        pq.pop();
        if (arr[cur.x][cur.y] == '1') {
            cout << cur.depth;
            return;
        }

        for (int i = 0; i < 4; i++) {
            int tmp_x = cur.x + dx[i];
            int tmp_y = cur.y + dy[i];
            if (valid(tmp_x, tmp_y)) {
                if (!is_visit[cur.key][tmp_x][tmp_y]) {
                    // #
                    if (arr[tmp_x][tmp_y] == '#')
                        is_visit[cur.key][tmp_x][tmp_y] = true;
                    // key
                    else if ('a' <= arr[tmp_x][tmp_y] and arr[tmp_x][tmp_y] <= 'f') {
                        Cur tmp_cur;
                        tmp_cur.key = (1 << (arr[tmp_x][tmp_y] - 'a')) | cur.key;
                        if (!is_visit[tmp_cur.key][tmp_x][tmp_y]) {
                            tmp_cur.depth = cur.depth + 1;
                            tmp_cur.x = tmp_x;
                            tmp_cur.y = tmp_y;
                            pq.push(tmp_cur);
                            is_visit[tmp_cur.key][tmp_x][tmp_y] = true;
                        }
                    }
                    // door
                    else if ('A' <= arr[tmp_x][tmp_y] and arr[tmp_x][tmp_y] <= 'F') {
                        if ((1 << (arr[tmp_x][tmp_y] - 'A')) & cur.key) {
                            Cur tmp_cur;
                            tmp_cur.depth = cur.depth + 1;
                            tmp_cur.x = tmp_x;
                            tmp_cur.y = tmp_y;
                            tmp_cur.key = cur.key;
                            pq.push(tmp_cur);
                            is_visit[cur.key][tmp_x][tmp_y] = true;
                        }
                    }

                    //.
                    else {
                        Cur tmp_cur;
                        tmp_cur.depth = cur.depth + 1;
                        tmp_cur.x = tmp_x;
                        tmp_cur.y = tmp_y;
                        tmp_cur.key = cur.key;
                        pq.push(tmp_cur);
                        is_visit[cur.key][tmp_x][tmp_y] = true;
                    }
                }
            }
        }
    }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}