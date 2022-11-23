#include <iostream>

using namespace std;

struct node {
    int node_num;
    pair<int, int> first;
    pair<int, int> second;
};
int n;
node *tr;
int max = 0;
int solve(int a) {
    if (tr[a].first == pair(0, 0) && tr[a].second == pair(0, 0)) {
        return 0;
    } else if (tr[a].second == pair(0, 0)) {
        return tr[a].first.second + solve(tr[a].first.first);
    } else {
        int left = tr[a].first.second + solve(tr[a].first.first);
        int right = tr[a].second.second + solve(tr[a].second.first);
        return ((left > right) ? left : right);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    tr = new node[n + 1];
    for (int i = 0; i < n + 1; i++) {
        tr[i].first = {0, 0};
        tr[i].second = {0, 0};
        tr[i].node_num = i;
    }
    
    int s, e, t;
    for (int i = 0; i < n - 1; i++) {
        cin >> s >> e >> t;
        if (tr[s].first == pair(0, 0)) {
            tr[s].first = {e, t};
        } else {
            tr[s].second = {e, t};
        }
    }
    int left = solve(tr[3].first.first) + tr[3].first.second;
    int right = solve(tr[3].second.first) + tr[3].second.second;
    

}