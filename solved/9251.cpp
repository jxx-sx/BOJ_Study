#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str1, str2;
    cin >> str1 >> str2;

    int arr[1001][1001];

    for (int i = 1; i < str1.size() + 1; i++) {
        for (int j = 1; j < str2.size() + 1; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                arr[i][j] = arr[i - 1][j - 1] + 1;
            } else {
                arr[i][j] = arr[i - 1][j] > arr[i][j - 1] ? arr[i - 1][j] : arr[i][j - 1];
            }
        }
    }

    cout << arr[str1.size()][str2.size()];
}