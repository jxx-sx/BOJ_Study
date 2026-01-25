#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long ans = 0;
int n, parents[201], c = 0;
vector<pair<int, pair<int, int>>> edges;
int find_root(int x) {
    if (parents[x] == x) {
        return x;
    }
    return parents[x] = find_root(parents[x]);
}

void union_root(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    parents[y] = x;
    return;
}

void kruskal() {
    vector<pair<int, int>> mst;
    sort(edges.begin(), edges.end());
    if (c != n - 1) {
        for (int i = 0; i < edges.size(); i++) {
            int s = edges[i].second.first;
            int e = edges[i].second.second;
            int t = edges[i].first;
            if (find_root(s) != find_root(e)) {
                union_root(s, e);
                ans += t;
                mst.push_back({s, e});
                c += 1;
            }
            if (c == n - 1)
                break;
        }
    }
    cout << ans << ' ' << mst.size() << '\n';
    for (int i = 0; i < mst.size(); i++) {
        cout << mst[i].first << ' ' << mst[i].second << '\n';
    }
    return;
}

void init() {
    for (int i = 0; i < 201; i++) {
        parents[i] = i;
    }
    int tmp;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> tmp;
            if (i < j) {
                if (tmp < 0) {
                    ans -= tmp;
                    if (find_root(i + 1) != find_root(j + 1))
                        c += 1;
                    union_root(i + 1, j + 1);
                } else {
                    edges.push_back({tmp, {i + 1, j + 1}});
                }
            }
        }
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    kruskal();
}