#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
typedef pair<double, pair<int, int>> edge;
typedef pair<double, double> star;

int n;
int *parent;
vector<star> stars;
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

double calDistance(int j, int i) {
    double temp;
    temp = sqrt(pow(stars[j].first - stars[i].first, 2) + pow(stars[j].second - stars[i].second, 2));

    return temp;
}

void init() {
    double a, b, distance;
    stars.push_back({0.0, 0.0});
    cin >> n;
    parent = new int[n + 1]{0};
    for (int i = 1; i < n + 1; i++) {
        cin >> a >> b;
        stars.push_back({a, b});
        for (int j = 1; j < i; j++) {
            edges.push_back({calDistance(j, i), {j, i}});
        }
    }
    sort(edges.begin(), edges.end());

    for (int i = 1; i < n + 1; i++)
        parent[i] = i;
}

int main() {
    double answer = 0.0;
    init();
    vector<edge> mst = kruskal();
    for (int i = 0; i < mst.size(); i++) {
        answer += mst[i].first;
    }
    cout << answer;
}