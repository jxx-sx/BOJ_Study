//최소 스패닝 트리
//정렬
//그래프 이론
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;
typedef pair<int, pair<int, int>> edge;

int n;
int *parent;
vector<edge> edges;
vector<pair<int, int>> xx;
vector<pair<int, int>> yy;
vector<pair<int, int>> zz;

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
    for (int i = 0;; i++) {
        cur_edge = edges[i];

        int f = cur_edge.second.first;
        int s = cur_edge.second.second;

        if (find_root(f) == find_root(s))
            continue;
        mst.push_back(cur_edge);
        union_root(f, s);
        if (mst.size() == n - 1)
            return mst;
    }
    return mst;
}

void init() {
    double a, b, c;
    cin >> n;
    parent = new int[n + 1]{0};
    for (int i = 1; i < n + 1; i++) {
        cin >> a >> b >> c;
        xx.push_back({a, i});
        yy.push_back({b, i});
        zz.push_back({c, i});
    }
    sort(xx.begin(), xx.end());
    sort(yy.begin(), yy.end());
    sort(zz.begin(), zz.end());

    for (int i = 0; i < n - 1; i++) {
        edges.push_back({abs(xx[i].first - xx[i + 1].first), {xx[i].second, xx[i + 1].second}});
        edges.push_back({abs(yy[i].first - yy[i + 1].first), {yy[i].second, yy[i + 1].second}});
        edges.push_back({abs(zz[i].first - zz[i + 1].first), {zz[i].second, zz[i + 1].second}});
    }
    sort(edges.begin(), edges.end());

    for (int i = 1; i < n + 1; i++)
        parent[i] = i;
}

int main() {
    int answer = 0;
    init();
    vector<edge> mst = kruskal();
    for (int i = 0; i < mst.size(); i++) {
        answer += mst[i].first;
    }
    cout << answer;
}