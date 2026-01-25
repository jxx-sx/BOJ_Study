#include <iostream>
#include <vector>

using namespace std;
int V, E, v1, v2;
vector<vector<int>> edges;

void f_w() {
    for (int k = 1; k <= V; k++)
        for (int i = 1; i <= V; i++)
            for (int j = 1; j <= V; j++)
                if (edges[i][k] != -1 and edges[k][j] != -1) {
                    if (edges[i][j] == -1)
                        edges[i][j] = edges[i][k] + edges[k][j];
                    else
                        edges[i][j] = min(edges[i][j], edges[i][k] + edges[k][j]);
                }
}

void init() {
    int s, e, t;
    cin >> V >> E;
    for (int i = 0; i <= V; i++) {
        edges.push_back(vector<int>(V + 1, -1));
        edges[i][i] = 0;
    }
    for (int i = 0; i < E; i++) {
        cin >> s >> e >> t;
        edges[s][e] = edges[e][s] = t;
    }
    cin >> v1 >> v2;
    f_w();

    return;
}

void solve() {
    int arr1[] = {edges[1][v1], edges[v1][v2], edges[v2][V]};
    int arr2[] = {edges[1][v2], edges[v2][v1], edges[v1][V]};
    bool flag1 = false, flag2 = false;
    for (int i = 0; i < 3; i++) {
        if (arr1[i] == -1)
            flag1 = true;
        if (arr2[i] == -1)
            flag2 = true;
    }
    if (flag1 and flag2)
        cout << -1;
    else if (flag1)
        cout << arr2[0] + arr2[1] + arr2[2];
    else if (flag2)
        cout << arr1[0] + arr1[1] + arr1[2];
    else
        cout << min(arr1[0] + arr1[1] + arr1[2], arr2[0] + arr2[1] + arr2[2]);
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}