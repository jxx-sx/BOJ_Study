#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int arr[8001] = {0};
    int tmp;
    double sum = 0.0;
    double mod = n;

    for (int i = 0; i < n; i++) {
        cin >> tmp;
        arr[tmp + 4000] += 1;
        sum += tmp / mod;
        
    }
}