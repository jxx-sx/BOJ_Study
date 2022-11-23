#include <iostream>

using namespace std;

int N, mm = 0;

void init() {
    cin >> N;
    int a;
    pair<int, int> arr[N];
    int max1 = 0;
    for (int i = 0; i < N; i++) {
        cin >> a;
        arr[i] = {a, 0};
        for (int j = 0; j < i; j++) {
            if (arr[j].first < a && arr[i].second < arr[j].second)
                arr[i].second = arr[j].second;
        }
        arr[i].second += 1;
        max1 = (max1 > arr[i].second) ? max1 : arr[i].second;
    }
    cout << max1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
}