#include <iostream>

using namespace std;

int n, m;

int main() {
    cin >> n >> m;
    int arr[n], answer = 0;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int l = j + 1; l < n; l++) {
                int temp = arr[i] + arr[j] + arr[l];
                if (temp <= m)
                    answer = (m - answer > m - temp) ? temp : answer;
            }
        }
    }
    cout << answer;
}