#include <iostream>
#include <map>
#include <string>

using namespace std;
map<string, string> m;
string id, pw;
int N, M;

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> id >> pw;
        m.insert({id, pw});
    }
    return;
}

void solve() {
    for (int i = 0; i < M; i++) {
        cin >> id;
        cout << m.find(id)->second << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}