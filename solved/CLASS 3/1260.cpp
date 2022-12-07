#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
int n, m, v;

struct Node {
    int data;
    vector<int> connected;
    bool visited;
};

Node *nodes;

void BFS(int x) {
    queue<int> bfs;
    bfs.push(x);
    nodes[x].visited = true;
    while (!bfs.empty()) {
        int cur = bfs.front();
        cout << cur << ' ';
        bfs.pop();
        for (int i = 0; i < nodes[cur].connected.size(); i++) {
            if (!nodes[nodes[cur].connected[i]].visited) {
                bfs.push(nodes[nodes[cur].connected[i]].data);
                nodes[nodes[cur].connected[i]].visited = true;
            }
        }
    }
}

void visit(int x) {}

void DFS(int x) {
    if (!nodes[x].visited) {
        cout << nodes[x].data << ' ';
        nodes[x].visited = true;

        for (int i = 0; i < nodes[x].connected.size(); i++) {
            DFS(nodes[x].connected[i]);
        }
    }
} //깊이

bool compare(Node *a, Node *b) { return a->data < b->data; }
void init() {
    int a, b;
    cin >> n >> m >> v;
    nodes = new Node[n + 1];
    for (int i = 0; i <= n; i++) {
        nodes[i].data = i;
        nodes[i].visited = false;
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        Node tmp;
        nodes[a].connected.push_back(b);
        nodes[b].connected.push_back(a);
    }

    for (int i = 0; i <= n; i++) {
        stable_sort(nodes[i].connected.begin(), nodes[i].connected.end());
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    DFS(v);
    cout << '\n';

    for (int i = 0; i <= n; i++) {
        nodes[i].visited = false;
    }

    BFS(v);
}