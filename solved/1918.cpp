#include <iostream>
#include <stack>
#include <string>

using namespace std;

stack<char> oper;
int priority(char c) {
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
}
void custom_push(char c) {
    if (c == ')') {
        while (oper.top() != '(') {
            cout << oper.top();
            oper.pop();
        }
        oper.pop();
    }

    else if (oper.empty() || c == '(') {
        oper.push(c);
    } else {
        while (!oper.empty()) {
            if (priority(oper.top()) < priority(c)) {
                break;
            } else {
                cout << oper.top();
                oper.pop();
            }
        }
        oper.push(c);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string inp;
    cin >> inp;

    for (int i = 0; i < inp.size(); i++) {
        if (inp[i] >= 'A' && inp[i] <= 'Z') {
            cout << inp[i];
        } else {
            custom_push(inp[i]);
        }
    }
    while (!oper.empty()) {
        cout << oper.top();
        oper.pop();
    }
}