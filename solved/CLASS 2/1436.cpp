#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b = 0;
    cin >> a;
    for (int i = 666; b != a; i++) {
        if (to_string(i).find("666") != std::string::npos) {
            b++;
        }
        if (a == b) {
            cout << i;
        }
    }
}