#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector<int> edges[300001]; // r: 1~ 50000, g: 50001 ~ 100000, b: 100001 ~ 1500000
vector<int> st;
int n, m;
int scc[300001];
int scc_cnt, dfs_cnt;
int l[300001];
int ord[300001];

int color2num(string s) { // RGB
    if (s == "BLUE")
        return 1; // 001
    if (s == "GREEN")
        return 2; // 010
    if (s == "CYAN")
        return 3; // 011
    if (s == "RED")
        return 4; // 100
    if (s == "PURPLE")
        return 5; // 101
    if (s == "YELLOW")
        return 6; // 110
    if (s == "WHITE")
        return 7; // 111
    return 0;     // 000
}

int dfs(int x) {
    dfs_cnt++;
    ord[x] = l[x] = dfs_cnt;
    st.push_back(x);
    for (auto a : edges[x]) {
        if (ord[a] == 0)
            l[x] = min(l[x], dfs(a));
        else if (scc[a] == 0)
            l[x] = min(l[x], l[a]);
    }

    if (l[x] == ord[x]) {
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
    for (int i = 1; i <= 3 * n; i++) {
        if (ord[i] == 0)
            dfs(i);
        if (ord[i + 150000] == 0)
            dfs(i + 150000);
    }
}

void init() {
    cin >> n >> m;
    int a, b, n1, n2;
    char k;
    string c1, c2;
    for (int j = 0; j < m; j++) {
        cin >> a >> b >> k >> c1 >> c2;
        n1 = color2num(c1);
        n2 = color2num(c2);
        if (k == 'H') { // high
            for (int i = 0; i < 3; i++) {
                if ((1 << i) & n1) {     // 입력된 색인 경우
                    if ((1 << i) & n2) { // 둘다 색이 존재해야함
                        edges[a + i * 50000 + 150000].push_back(a + i * 50000);
                        edges[b + i * 50000 + 150000].push_back(b + i * 50000);
                    } else { // 둘 중 하나가 존재한다면 다른 하나가 없어야함
                        edges[a + i * 50000].push_back(b + i * 50000 + 150000);
                        edges[b + i * 50000].push_back(a + i * 50000 + 150000);
                    }
                }
            }
        } else { // low
            for (int i = 0; i < 3; i++) {
                if ((1 << i) & n1) {     // 입력된 색인 경우
                    if ((1 << i) & n2) { // 둘 중 하나가 없다면 다른 하나가 존재해야함
                        edges[a + i * 50000 + 150000].push_back(b + i * 50000);
                        edges[b + i * 50000 + 150000].push_back(a + i * 50000);
                    } else { // 둘 다 없어야함
                        edges[a + i * 50000].push_back(a + i * 50000 + 150000);
                        edges[b + i * 50000].push_back(b + i * 50000 + 150000);
                    }
                }
            }
        }
    }

    tarjan();
    return;
}

void solve() {
    for (int i = 1; i <= n; i++)
        if (scc[i] == scc[i + 150000]) {
            cout << "THINKINGFACE";
            return;
        }

    cout << "ALIEN";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}