//그래프 이론
//최소 스패닝 트리

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
typedef pair<double, pair<int, int>> edge;
typedef pair<int, int> starGod;

int n, m;
int *parent;
vector<edge> edges, mst, tempMst;
vector<starGod> gods;

double calDistance(int start, int end) {
    double xx = pow(gods[start].first - gods[end].first, 2);
    double yy = pow(gods[start].second - gods[end].second, 2);
    double distance = sqrt(xx + yy);
    return distance;
}

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
    edge cur_edge;

    for (int i = 0; i < edges.size(); i++) {
        cur_edge = edges[i];

        int f = cur_edge.second.first;
        int s = cur_edge.second.second;

        if (find_root(f) == find_root(s))
            continue;
        mst.push_back(cur_edge);
        union_root(f, s);
        if (mst.size() - m == n - 1)
            return mst;
    }
    return mst;
}

void init() {
    int x, y;
    cin >> n >> m;
    gods.push_back({0, 0});

    parent = new int[n + 1]{0};
    for (int i = 0; i < n + 1; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        gods.push_back({x, y});
    }

    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        union_root(x, y);
    }

    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j < n + 1; j++) {
            edges.push_back({calDistance(i, j), {i, j}});
        }
    }

    sort(edges.begin(), edges.end());
}

int main() {
    double answer = 0.0;
    init();
    kruskal();
    for (int i = 0; i < mst.size(); i++) {
        answer += mst[i].first;
    }
    cout << fixed;
    cout.precision(2);
    cout << answer;
}