#include <iostream>
#include <queue>
#include <string>

using namespace std;

bool broken[10];
int n;
queue<int> q;
bool is_visit[1000000];

void init() {
    int m, tmp;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> tmp;
        broken[tmp] = true;
    }
    q.push(n);
    is_visit[n] = true;
    return;
}

void solve() {
    string cur;
    bool flag = false;
    while (!q.empty()) {
        cur = to_string(q.front());
        flag = false;
        for (auto a : cur) {
            if (broken[a - '0']) {
                flag = true;
                break;
            }
        }
        if (flag) {
            if (q.front() > 0)
                if (!is_visit[q.front() - 1]) {
                    q.push(q.front() - 1);
                    is_visit[q.front() - 1] = true;
                }
            if (q.front() < 1000000)
                if (!is_visit[q.front() + 1]) {
                    q.push(q.front() + 1);
                    is_visit[q.front() + 1] = true;
                }
        } else {
            cout << min(abs(q.front() - n) + cur.size(), (unsigned long)abs(100 - n));
            break;
        }
        q.pop();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}