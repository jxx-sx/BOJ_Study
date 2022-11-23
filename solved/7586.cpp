#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    pair<int, int> data[n];
    for (int i = 0; i < n; i++) {
        data[i] = {1, 1};
        cin >> data[i].first >> data[i].second;
    }
    for (int i = 0; i < n; i++) {
        int tmp = 1;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if (data[i].first < data[j].first and data[i].second < data[j].second)
                    tmp++;
            }
        }
        cout << tmp << ' ';
    }
}