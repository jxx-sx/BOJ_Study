//최소 스패닝 트리
//그래프 이론
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef pair<int, pair<int, int>> edge;

int v, e, answer = 0;
int *parent;
vector<edge> edges;

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

vector<edge> kruskal() {
    vector<edge> mst;
    edge cur_edge;
    for (int i = 0; i < e; i++) {
        cur_edge = edges[i];

        int f = cur_edge.second.first;
        int s = cur_edge.second.second;

        if (find_root(f) == find_root(s))
            continue;
        mst.push_back(cur_edge);
        union_root(f, s);
        if (mst.size() == v - 2)
            return mst;
    }
    return mst;
}

void init() {
    int a, b, c;
    cin >> v >> e;
    parent = new int[v + 1]{0};
    for (int i = 0; i < e; i++) {
        cin >> a >> b >> c;
        edges.push_back({c, {a, b}});
    }
    sort(edges.begin(), edges.end());

    for (int i = 1; i < v + 1; i++)
        parent[i] = i;
}

int main() {
    init();
    vector<edge> mst = kruskal();
    for (int i = 0; i < mst.size(); i++) {
        answer += mst[i].first;
    }
    cout << answer;
}