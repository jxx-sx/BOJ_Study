#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> arr;
int a;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> a;
    int inp;
    cin >> inp;
    arr.push_back(inp);
    for (int i = 0; i < a - 1; i++) {
        cin >> inp;
        if (arr.back() < inp) {
            arr.push_back(inp);
        } else {
            *lower_bound(arr.begin(), arr.end(), inp) = inp;
        }
    }
    cout << arr.size();
}