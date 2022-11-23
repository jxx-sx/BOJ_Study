#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> pp;
vector<pp> vec;

void init() {
    vec.push_back({1, 0});
    vec.push_back({0, 1});
    for (int i = 2; i <= 40; i++) {
        int count0 = vec[i - 1].first + vec[i - 2].first;
        int count1 = vec[i - 1].second + vec[i - 2].second;
        vec.push_back({count0, count1});
    }
}

int main() {
    init();
    int n, m;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> m;
        cout << vec[m].first << ' ' << vec[m].second << endl;
    }
}