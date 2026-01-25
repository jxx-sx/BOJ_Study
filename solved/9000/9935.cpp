#include <iostream>
#include <string>
#include <vector>

using namespace std;
string st, bomb;
vector<pair<char, int>> v;
void init() {
    cin >> st >> bomb;
    v.push_back({0, -1});
}

void solve() {
    for (auto a : st) {
        if (bomb[v.back().second + 1] == a)
            v.push_back({a, v.back().second + 1});
        else if (a == bomb[0])
            v.push_back({a, 0});
        else
            v.push_back({a, -1});
        if (v.back().second == bomb.size() - 1)
            for (int i = 0; i < bomb.size(); i++)
                v.pop_back();
    }

    if (v.size() == 1)
        cout << "FRULA";
    else
        for (int i = 1; i < v.size(); i++)
            cout << v[i].first;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}