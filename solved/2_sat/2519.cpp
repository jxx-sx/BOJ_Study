#include <iostream>
#include <vector>

using namespace std;

struct stick {
    int x1, y1, x2, y2;
};

vector<int> edges[6000];
int scc[6000];
int l[6000];
int o[6000];
int dfs_cnt;
int scc_cnt;
int n;
int k;
vector<int> ans;
vector<stick> sticks;
vector<int> st;
int arr[12];
long long ccw[4];

void ccw_init(int a, int b) {
    arr[0] = sticks[a].x1 * sticks[a].y2;
    arr[1] = sticks[a].x2 * sticks[b].y1;
    arr[2] = sticks[a].y1 * sticks[b].x1;
    arr[3] = sticks[a].y1 * sticks[a].x2;
    arr[4] = sticks[a].y2 * sticks[b].x1;
    arr[5] = sticks[a].x1 * sticks[b].y1;
    arr[6] = sticks[a].x2 * sticks[b].y2;
    arr[7] = sticks[a].y1 * sticks[b].x2;
    arr[8] = sticks[a].y2 * sticks[b].x2;
    arr[9] = sticks[a].x1 * sticks[b].y2;
    arr[10] = sticks[b].x1 * sticks[b].y2;
    arr[11] = sticks[b].y1 * sticks[b].x2;
}

void get_ccw() {
    ccw[0] = arr[0] + arr[1] + arr[2] - arr[3] - arr[4] - arr[5];
    ccw[1] = arr[0] + arr[6] + arr[7] - arr[3] - arr[8] - arr[9];
    ccw[2] = arr[5] + arr[7] + arr[10] - arr[2] - arr[9] - arr[11];
    ccw[3] = arr[1] + arr[8] + arr[10] - arr[4] - arr[6] - arr[11];
}

bool is_cross(int a, int b) {
    ccw_init(a, b);
    get_ccw();
    if (ccw[0] * ccw[1] > 0)
        return false;
    if (ccw[2] * ccw[3] > 0)
        return false;
    return true;
}

int dfs(int x) {
    dfs_cnt++;
    l[x] = o[x] = dfs_cnt;
    st.push_back(x);
    for (auto a : edges[x]) {
        if (o[a] == 0)
            l[x] = min(l[x], dfs(a));
        else if (scc[a] == 0)
            l[x] = min(l[x], l[a]);
    }

    if (l[x] == o[x]) {
        scc_cnt++;
        while (true) {
            scc[st.back()] = scc_cnt;
            if (st.back() == x) {
                st.pop_back();
                break;
            }
            st.pop_back();
        }
    }

    return l[x];
}

void tarjan() {
    for (int i = 0; i < 3 * n; i++) {
        if (o[i] == 0)
            dfs(i);
        if (o[i + 3000] == 0)
            dfs(i + 3000);
    }
}

void init() {
    cin >> n;
    for (int i = 0; i < 1000; i++) {
        edges[3 * i + 3000].push_back(3 * i + 1);
        edges[3 * i + 3000].push_back(3 * i + 2);

        edges[3 * i + 3001].push_back(3 * i);
        edges[3 * i + 3001].push_back(3 * i + 2);

        edges[3 * i + 3002].push_back(3 * i);
        edges[3 * i + 3002].push_back(3 * i + 1);
    }

    int x1, y1, x2, y2;
    stick tmp;

    for (int i = 0; i < 3 * n; i++) {
        cin >> tmp.x1 >> tmp.y1 >> tmp.x2 >> tmp.y2;
        sticks.push_back(tmp);
    }

    for (int i = 0; i < 3 * n; i++)
        for (int j = i + 1; j < 3 * n; j++)
            if (is_cross(i, j)) {
                edges[i].push_back(j + 3000);
                edges[j].push_back(i + 3000);
            }
}

void solve() {
    tarjan();

    for (int i = 0; i < 3 * n; i++) {
        if (scc[i] == scc[i + 3000]) {
            cout << -1;
            return;
        }
        if (scc[i + 3000] < scc[i]) {
            k++;
            ans.push_back(i + 1);
        }
    }

    cout << k << '\n';
    for (auto a : ans)
        cout << a << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}