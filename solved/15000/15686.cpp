#include <iostream>

using namespace std;

int n, m;
int dist[100][13];
pair<int, int> home[100], chicken[13];
int home_cnt, chicken_cnt;
int ans = 10001;
int m_cnt, select_chicken[13];

inline int chicken_distance(int h, int c) { return abs(home[h].first - chicken[c].first) + abs(home[h].second - chicken[c].second); }

void dfs(int x, int *b) {
    int tmp_arr[100];
    if (m_cnt == m) {
        int tmp = 0;
        for (int i = 0; i < home_cnt; i++)
            tmp += b[i];
        ans = min(ans, tmp);
        return;
    }

    // select
    if (m_cnt == 0)
        for (int i = 0; i < home_cnt; i++)
            tmp_arr[i] = dist[i][x];
    else
        for (int i = 0; i < home_cnt; i++)
            tmp_arr[i] = min(b[i], dist[i][x]);
    if (x < chicken_cnt) {
        m_cnt++;
        dfs(x + 1, tmp_arr);
        m_cnt--;
    }

    // none select
    if (x < chicken_cnt)
        dfs(x + 1, b);
}

void init() {
    cin >> n >> m;
    int stat;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> stat;
            if (stat == 1)
                home[home_cnt++] = {i, j};
            else if (stat == 2)
                chicken[chicken_cnt++] = {i, j};
        }
    for (int i = 0; i < home_cnt; i++)
        for (int j = 0; j < chicken_cnt; j++)
            dist[i][j] = dist[i][j] == 0 ? chicken_distance(i, j) : min(dist[i][j], chicken_distance(i, j));
    return;
}

void solve() {
    dfs(0, nullptr);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}