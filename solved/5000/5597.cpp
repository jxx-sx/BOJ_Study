#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bool arr[31] = {false};
    for (int i = 0; i < 28; i++) {
        int tmp;
        cin >> tmp;
        arr[tmp] = true;
    }
    for (int i = 1; i < 31; i++) {
        if (!arr[i]) {
            cout << i << endl;
        }
    }
}