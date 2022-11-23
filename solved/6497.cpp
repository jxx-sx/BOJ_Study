//그래프 이론
//최소 스패닝 트리
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int m, n, sum = 0;
int *parent;
typedef pair<int, pair<int, int>> edge;

int find_root(int x) {
    if (parent[x] == x)
        return x;
    return parent[x] = find_root(parent[x]);
}

void union_root(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    if (x != y)
        parent[y] = x;
}

void kruskal(vector<edge> edges) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        edge cur_edge = edges[i];
        int f = cur_edge.second.first;
        int s = cur_edge.second.second;

        if (find_root(f) == find_root(s))
            continue;
        union_root(f, s);
        count += 1;
        sum -= cur_edge.first;
        if (count == m - 1)
            return;
    }
}
vector<edge> init() {
    vector<edge> edges;
    int x, y, z;
    sum = 0;
    parent = new int[m]{0};
    for (int i = 0; i < m; i++)
        parent[i] = i;

    for (int i = 0; i < n; i++) {
        cin >> x >> y >> z;
        edges.push_back({z, {x, y}});
        sum += z;
    }
    sort(edges.begin(), edges.end());

    return edges;
}

int main() {
    while (1) {
        cin >> m >> n;
        if (m == 0 && n == 0)
            return 0;
        kruskal(init());
        cout << sum << endl;
    }
}