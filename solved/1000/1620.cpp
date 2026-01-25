#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef pair<string, int> info;

vector<info> v1, v2;
int N, M;

bool compare1(info a, info b) { return a.first < b.first; }

bool compare2(info a, info b) { return a.second < b.second; }

bool isNumeric(string str) {
    if (str[0] <= '9' && '0' <= str[0]) {
        return true;
    }
    return false;
}

int find_index(string s) {
    int lo = 0, hi = N - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (v1[mid].first == s) {
            return mid;
        } else if (v1[mid].first > s) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return 0;
}

void solve() {
    string s;
    for (int i = 0; i < M; i++) {
        cin >> s;
        if (isNumeric(s)) {
            cout << v2[atoi(s.c_str()) - 1].first << '\n';
        } else {
            cout << v1[find_index(s)].second << '\n';
        }
    }
}

void init() {
    cin >> N >> M;
    string s;
    for (int i = 0; i < N; i++) {
        cin >> s;
        v1.push_back({s, i + 1});
        v2.push_back({s, i + 1});
    }
    stable_sort(v1.begin(), v1.end(), compare1);
    stable_sort(v2.begin(), v2.end(), compare2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}