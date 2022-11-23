#include <iostream>

using namespace std;

int main() {
    string str;
    while (1) {
        cin >> str;
        if (str == "0")
            break;
        for (int i = 0; i <= str.size() / 2; i++) {
            if (str[i] != str[str.size() - i - 1]) {
                cout << "no" << endl;
                break;
            }
            if (i == str.size() / 2)
                cout << "yes" << endl;
        }
    }
}