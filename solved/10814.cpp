#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
// typedef pair<int, string> Data;
vector<pair<int, string>> dd;

bool compare(pair<int, string> a, pair<int, string> b) { return a.first < b.first; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    pair<int, string> tmp;
    for (int i = 0; i < n; i++) {
        cin >> tmp.first >> tmp.second;
        dd.push_back(tmp);
    }
    stable_sort(dd.begin(), dd.end(), compare);
    for (int i = 0; i < n; i++)
        cout << dd[i].first << ' ' << dd[i].second << '\n';
}