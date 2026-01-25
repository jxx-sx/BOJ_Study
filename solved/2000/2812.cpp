#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Node {
    char num;
    int i;
    Node(char num, int i) : num(num), i(i) {}
    bool operator<(const Node &t) const {
        if (num == t.num)
            return i > t.i;
        return num < t.num;
    }
};

string num;
int n, k;
int cur;
priority_queue<Node> pq;

void push(int i) {
    while (cur <= min(i, n - 1)) {
        pq.push(Node(num[cur], cur));
        cur++;
    }
    return;
}

void init() { cin >> n >> k >> num; }

void solve() {
    int cnt = n - k;
    int i = -1;
    push(i + k + 1);
    while (cnt--) {
        while (pq.top().i < i)
            pq.pop();
        auto tmp = pq.top();
        pq.pop();
        cout << tmp.num;
        k -= tmp.i - i - 1;
        i = tmp.i;
        push(i + k + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}