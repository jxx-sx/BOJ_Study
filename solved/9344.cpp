#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int *parent;

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int N, M, p, q;
        cin >> N >> M >> p >> q;
        vector<pair<int, pair<int, int>>> edges;
        parent = new int[N + 1];
        edges.clear();

        for (int j = 0; j < N + 1; j++) {
            parent[j] = j;
        }

        int a, b, c;
        for (int j = 0; j < M; j++) {
            cin >> a >> b >> c;
            edges.push_back({c, {a, b}});
        }
        sort(edges.begin(), edges.end());
        int count = 0;
        for (int j = 0; j < edges.size(); j++) {
            int s = edges[j].second.first;
            int e = edges[j].second.second;
            if (find_root(s) != find_root(e)) {
                if (s == p && e == q) {
                    cout << "YES\n";
                    break;
                }
                count += 1;
                union_root(s, e);
            }
            if (count == N - 1) {
                cout << "NO\n";
                break;
            }
        }
    }
}