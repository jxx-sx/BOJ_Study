#include <iostream>
#include <vector>

using namespace std;

int dfs_cnt;
int cc_cnt[1000000];
bool is_visit[1000][1000];
int arr[1000][1000];
bool wall[1000][1000];
int n, m;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool valid(int x, int y) {
    if (x < 0 or n <= x)
        return false;
    if (y < 0 or m <= y)
        return false;
    return true;
}

void dfs(int x, int y) {
    cc_cnt[dfs_cnt]++;
    is_visit[x][y] = true;
    arr[x][y] = dfs_cnt;
    for (int i = 0; i < 4; i++) {
        int tmp_x = x + dx[i];
        int tmp_y = y + dy[i];
        if (valid(tmp_x, tmp_y))
            if (!is_visit[tmp_x][tmp_y] and !wall[tmp_x][tmp_y])
                dfs(tmp_x, tmp_y);
    }
}

void init() {
    char ch;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> ch;
            wall[i][j] = ch == '1';
        }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (wall[i][j]) {
                is_visit[i][j] = true;
            } else if (!is_visit[i][j]) {
                dfs_cnt++;
                dfs(i, j);
            }
        }
    return;
}

void solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int tmp = 0;
            vector<int> aa;
            if (wall[i][j]) {
                for (int k = 0; k < 4; k++) {
                    if (valid(i + dx[k], j + dy[k])) {
                        int tmp2 = arr[i + dx[k]][j + dy[k]];
                        if (tmp2) {
                            bool flag = false;
                            for (auto a : aa) {
                                if (a == tmp2)
                                    flag = true;
                            }
                            if (flag)
                                continue;
                            else {
                                aa.push_back(tmp2);
                                tmp += cc_cnt[tmp2];
                            }
                        }
                    }
                }
                cout << (tmp + 1) % 10;
            } else
                cout << 0;
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
    return 0;
}