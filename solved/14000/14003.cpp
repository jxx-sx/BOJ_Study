#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> arr;
int *arrIndex;
int *original;
int a;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> a;
    arrIndex = new int[a];
    original = new int[a];
    int inp;
    for (int i = 0; i < a; i++) {
        cin >> inp;
        original[i] = inp;
        if (arr.empty() || arr.back() < inp) {
            arr.push_back(inp);
            arrIndex[i] = arr.size() - 1;
        } else {
            int tmp = lower_bound(arr.begin(), arr.end(), inp) - arr.begin();
            arr[tmp] = inp;
            arrIndex[i] = tmp;
        }
    }

    int tmp[arr.size()];
    int count = arr.size() - 1;
    for (int i = a - 1; i >= 0; i--) {
        if (arrIndex[i] == count) {
            tmp[count] = i;
            count -= 1;
        }
        if (count < 0)
            break;
    }

    cout << arr.size() << '\n';
    for (int i = 0; i < arr.size(); i++) {
        cout << original[tmp[i]] << ' ';
    }
}