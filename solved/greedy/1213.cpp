#include <iostream>
#include <string>

using namespace std;
char p[26];
bool odd = false;
int mid;

void init() {
    string st;
    cin >> st;
    for (auto a : st)
        p[a - 'A']++;
}

void solve() {
    for (int i = 0; i < 26; i++) {
        if (p[i] % 2) {
            if (odd) {
                cout << "I'm Sorry Hansoo";
                return;
            } else {
                odd = true;
                mid = i;
            }
        }
    }
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < p[i] / 2; j++)
            cout << (char)('A' + i);
    }
    if (odd)
        cout << (char)('A' + mid);
    for (int i = 25; i >= 0; i--) {
        for (int j = 0; j < p[i] / 2; j++)
            cout << (char)('A' + i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}