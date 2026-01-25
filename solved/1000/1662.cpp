#include <iostream>
#include <string>

using namespace std;

string str;
int x;

int recursive() {
    int cnt = 0;
    while (x < str.size()) {
        if (str[x] == '(') {
            int tmp = str[x - 1] - '0';
            x++;
            cnt += tmp * recursive() - 1;
        } else if (str[x] == ')') {
            x++;
            break;
        } else {
            x++;
            cnt++;
        }
    }
    return cnt;
}

void init() { cin >> str; }

void solve() { cout << recursive(); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}