//그래프 이론
//최소 스패닝 트리
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n;
int *parent;
typedef pair<int, pair<int, int>> edge;
vector<edge> edges;

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

void init() {
    cin >> n;
    int c;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            cin >> c;
            if (j > i) {
                edges.push_back({c, {i, j}});
            }
        }
    sort(edges.begin(), edges.end());
    parent = new int[n + 1]{0};
    for (int i = 0; i < n + 1; i++)
        parent[i] = i;
}

long long kruskal() {
    int count = 0;
    long long answer = 0;
    for (int i = 0; i < edges.size(); i++) {
        edge cur_edge = edges[i];
        int f = cur_edge.second.first;
        int s = cur_edge.second.second;

        if (find_root(f) == find_root(s))
            continue;
        union_root(f, s);
        count++;
        answer += cur_edge.first;

        if (count == n - 1)
            return answer;
    }
    return answer;
}

int main() {
    init();
    cout << kruskal() << endl;
}