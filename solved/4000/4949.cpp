#include <iostream>
#include <stack>
#include <string>

using namespace std;

string inp;
void solve(string s) {
    stack<char> sc;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '[' or s[i] == '(') {
            sc.push(s[i]);
        }
        if (s[i] == ']') {
            if (sc.empty()) {
                cout << "no\n";
                return;
            }
            if (sc.top() != '[') {
                cout << "no\n";
                return;
            }
            sc.pop();
        }
        if (s[i] == ')') {
            if (sc.empty()) {
                cout << "no\n";
                return;
            }
            if (sc.top() != '(') {
                cout << "no\n";
                return;
            }
            sc.pop();
        }
    }
    if (sc.empty())
        cout << "yes\n";
    else
        cout << "no\n";

    return;
}

void init() {
    while (true) {
        getline(cin, inp);
        if (inp == ".")
            break;
        solve(inp);
    }
    return;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    return 0;
}