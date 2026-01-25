#include <iostream>
#include <queue>

using namespace std;

struct compare {
    bool operator()(int a, int b) {
        if (abs(a) == abs(b))
            return a > b;
        return abs(a) > abs(b);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    priority_queue<int, vector<int>, compare> pq;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int inp;
        cin >> inp;
        if (inp) {
            pq.push(inp);
        } else {
            if (pq.empty())
                cout << "0\n";
            else {
                cout << pq.top() << '\n';
                pq.pop();
            }
        }
    }
}