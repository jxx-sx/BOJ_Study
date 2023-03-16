#include <iostream>
#include <queue>

using namespace std;
typedef pair<pair<int, int>, int> Lecture;
priority_queue<Lecture, vector<Lecture>, greater<Lecture>> lecture;
int ans[100001];
int room_cnt = 1, n;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> room;

void init() {
    int a, b, c;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b >> c;
        lecture.push({{b, c}, a});
    }
    room.push({0, 1});
    return;
}

void solve() {
    while (!lecture.empty()) {
        if (room.top().first <= lecture.top().first.first) {
            int cur = room.top().second;
            ans[lecture.top().second] = cur;
            room.pop();
            room.push({lecture.top().first.second, cur});
        } else {
            room_cnt++;
            room.push({lecture.top().first.second, room_cnt});
            ans[lecture.top().second] = room_cnt;
        }
        lecture.pop();
    }
    cout << room_cnt << '\n';
    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}