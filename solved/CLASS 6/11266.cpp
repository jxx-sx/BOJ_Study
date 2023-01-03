#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int v, e, visitCount = 1;
vector<int> edges[10001], type[10001], cut_vertex;
vector<bool> isVisit = vector<bool>(10001, false);
int L[10001];
int order[10001];

void dfs(int cur, int p) {
    order[cur] = visitCount++;
    isVisit[cur] = true;
    for (auto next : edges[cur]) {
        if (next == p) {
            type[cur].push_back(0); // p
        } else if (isVisit[next]) {
            type[cur].push_back(1); // etc
        } else {
            type[cur].push_back(2); // child
            dfs(next, cur);
        }
    }
    return;
}

int dfs2(int cur, int p) {
    L[cur] = order[cur];
    for (int i = 0; i < edges[cur].size(); i++) {
        if (type[cur][i] == 1) {
            L[cur] = min(L[cur], order[edges[cur][i]]);
        }
        if (type[cur][i] == 2) {
            L[cur] = min(L[cur], dfs2(edges[cur][i], cur));
        }
    }

    if (p == 0) {
        bool root = false;
        for (auto edge : type[cur]) {
            if (edge == 2) {
                if (root) {
                    cut_vertex.push_back(cur);
                    break;
                }
                root = true;
            }
        }
    } else {
        for (int i = 0; i < edges[cur].size(); i++) {
            if (type[cur][i] == 2) {
                if (L[edges[cur][i]] >= order[cur]) {
                    cut_vertex.push_back(cur);
                    break;
                }
            }
        }
    }

    return L[cur];
}

void init() {
    cin >> v >> e;
    int a, b;
    for (int i = 0; i < e; i++) {
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    return;
}

void print() {
    cout << cut_vertex.size() << '\n';
    for (auto a : cut_vertex)
        cout << a << ' ';
}

void solve() {
    for (int i = 1; i <= v; i++) {
        if (!isVisit[i]) {
            dfs(i, 0);
            dfs2(i, 0);
        }
    }

    sort(cut_vertex.begin(), cut_vertex.end());
    print();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}