#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    bool arr[20] = {false};
    int n, tmp;
    cin >> n;
    string inp;
    for (int i = 0; i < n; i++) {
        cin >> inp;
        if (inp == "add") {
            cin >> tmp;
            arr[tmp - 1] = true;
        } else if (inp == "remove") {
            cin >> tmp;
            arr[tmp - 1] = false;
        } else if (inp == "check") {
            cin >> tmp;
            if (arr[tmp - 1]) {
                cout << "1\n";
            } else {
                cout << "0\n";
            }
        } else if (inp == "toggle") {
            cin >> tmp;
            arr[tmp - 1] = !arr[tmp - 1];
        } else if (inp == "all") {
            for (int j = 0; j < 20; j++) {
                arr[j] = true;
            }
        } else if (inp == "empty") {
            for (int j = 0; j < 20; j++) {
                arr[j] = false;
            }
        }
    }
}