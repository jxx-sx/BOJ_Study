//그래프 이론
//최소 스패닝 트리

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
int *parent;
typedef pair<int, pair<int, int>> edge;
vector<edge> edges, mst;
vector<char> sex;

int find_root(int x) {
    if (parent[x] == x)
        return x;
    return parent[x] = find_root(parent[x]);
}

void union_root(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    parent[y] = x;
}

void kruskal() {
    for (int i = 0; i < edges.size(); i++) {
        edge cur_edge = edges[i];
        int f = cur_edge.second.first;
        int s = cur_edge.second.second;
        if (find_root(f) == find_root(s))
            continue;
        union_root(f, s);
        mst.push_back(cur_edge);
        if (mst.size() == n - 1)
            return;
    }
}

void init() {
    cin >> n >> m;
    char temp;
    int u, v, d;
    parent = new int[n + 1]{0};
    for (int i = 0; i < n + 1; i++)
        parent[i] = i;
    sex.push_back('0');

    for (int i = 0; i < n; i++) {
        cin >> temp;
        sex.push_back(temp);
    }

    for (int i = 0; i < m; i++) {
        cin >> u >> v >> d;
        if (sex[u] == sex[v])
            continue;
        edges.push_back({d, {u, v}});
    }
    sort(edges.begin(), edges.end());
}

int main() {
    int answer = 0;
    init();
    kruskal();
    if (mst.size() != n - 1) {
        cout << -1 << endl;
        return 0;
    }
    for (int i = 0; i < mst.size(); i++)
        answer += mst[i].first;
    cout << answer << endl;
}