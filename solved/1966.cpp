#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        queue<pair<int, int>> pq;
        int a, b, c;
        cin >> a >> b;
        priority_queue<int> priority;
        for (int j = 0; j < a; j++) {
            cin >> c;
            priority.push(c);
            pq.push({c, j});
        }
        int j = 1;
        while (!pq.empty()) {
            pair<int, int> cur = pq.front();
            pq.pop();
            if (cur.first == priority.top()) {
                if (cur.second == b) {
                    cout << j << endl;
                    break;
                } else {
                    j++;
                    priority.pop();
                }
            } else {
                pq.push(cur);
            }
        }
    }
}
