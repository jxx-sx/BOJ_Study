#include <iostream>

using namespace std;
struct Cheeze {
    int air_cnt;
    bool is_cheeze;
};

Cheeze cheeze[100][100];
bool is_visit[100][100];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int n, m;
int new_x, new_y;

bool isValid(int x, int y) {
    if (x < 0 or n <= x)
        return false;
    if (y < 0 or m <= y)
        return false;
    return true;
}

inline void update_cheeze(int x, int y) { ++cheeze[x][y].air_cnt; }

void dfs(int x, int y) {
    is_visit[x][y] = true;
    for (int i = 0; i < 4; i++) {
        new_x = x + dx[i];
        new_y = y + dy[i];
        if (isValid(new_x, new_y)) {
            if (cheeze[new_x][new_y].is_cheeze)
                update_cheeze(new_x, new_y);
            else if (!is_visit[new_x][new_y])
                dfs(new_x, new_y);
        }
    }
}

bool check() {
    bool ret = false;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            is_visit[i][j] = false;
            if (cheeze[i][j].air_cnt > 1)
                cheeze[i][j].is_cheeze = false;
            cheeze[i][j].air_cnt = 0;
            if (cheeze[i][j].is_cheeze)
                ret = true;
        }
    return ret;
}

void init() {
    int inp;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> inp;
            cheeze[i][j].air_cnt = 0;
            cheeze[i][j].is_cheeze = inp == 1;
        }
}

void solve() {
    int cnt = 0;
    while (check()) {
        dfs(0, 0);
        cnt++;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}