#include <iostream>
#include <string>

using namespace std;

int check_priority(char ch) {
    if (ch == '0') {
        return 0;
    } else {
        if (ch > 96)
            return ch - 96;
        else
            return ch - 38;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    string str;
    cin >> n;
    long long temp = 0;
    for (int i = 0; i < n; i++) {
        cin >> str;
        for (int j = 0; j < n; j++) {
            temp += check_priority(str[j]);
        }
    }
}