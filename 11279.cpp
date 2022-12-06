#include <iostream>
#include <queue>

using namespace std;

int n;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    priority_queue<int> pq;
    int inp;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> inp;
        if (inp == 0) {
            if (pq.empty())
                cout << 0;
            else {
                cout << pq.top() << '\n';
                pq.pop();
            }
        } else
            pq.push(inp);
    }
}