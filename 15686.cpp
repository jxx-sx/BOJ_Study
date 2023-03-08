#include <iostream>

using namespace std;

int n, m;
int dist[100][13];
pair<int, int> home[100], chicken[13];
int home_cnt, chicken_cnt;
int ans = 10001, tmp;
int m_cnt, select_chicken[13];

inline int chicken_distance(int h, int c) { return abs(home[h].first - chicken[c].first) + abs(home[h].second - chicken[c].second); }

void dfs(int x) {
    if (x == home_cnt) {
        ans = min(ans, tmp);
        return;
    }
    for (int i = 0; i < chicken_cnt; i++) {
        if (select_chicken[i] == 0) {
            if (m_cnt == m)
                continue;
            m_cnt++;
        }
        select_chicken[i]++;
        tmp += dist[x][i];
        dfs(x + 1);
        tmp -= dist[x][i];
        select_chicken[i]--;
        if (select_chicken[i] == 0)
            m_cnt--;
    }
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
    dfs(0);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}