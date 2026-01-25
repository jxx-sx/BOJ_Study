#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct compare {
    bool operator()(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
        if (a.second == b.second) {
            if (a.first.first == b.first.first)
                return a.first.second > b.first.second;
            return a.first.first > b.first.first;
        }
        return a.second > b.second;
    }
};

int n;
int arr[20][20];
int x, y;
priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, compare> pq;
vector<vector<bool>> check = vector<vector<bool>>(20, vector<bool>(20, false));
int shark_size = 2, fish_count = 0, shark_move = 0;

void eat_fish() {
    if (shark_size == ++fish_count) {
        fish_count = 0;
        shark_size += 1;
    }
}

void reset() {
    pq = priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, compare>();
    check = vector<vector<bool>>(20, vector<bool>(20, false));
    return;
}

bool bfs() {
    int cur_x, cur_y, dist;
    while (!pq.empty()) {
        cur_x = pq.top().first.first;
        cur_y = pq.top().first.second;
        dist = pq.top().second;
        pq.pop();
        if (arr[cur_x][cur_y] < shark_size and arr[cur_x][cur_y]) {
            eat_fish();
            arr[cur_x][cur_y] = 0;
            shark_move += dist;
            x = cur_x;
            y = cur_y;
            reset();
            return true;
        }

        if (cur_x > 0)
            if (!check[cur_x - 1][cur_y] and arr[cur_x - 1][cur_y] <= shark_size) {
                pq.push({{cur_x - 1, cur_y}, dist + 1});
                check[cur_x - 1][cur_y] = true;
            }
        if (cur_y > 0)
            if (!check[cur_x][cur_y - 1] and arr[cur_x][cur_y - 1] <= shark_size) {
                pq.push({{cur_x, cur_y - 1}, dist + 1});
                check[cur_x][cur_y - 1] = true;
            }
        if (cur_y < n - 1)
            if (!check[cur_x][cur_y + 1] and arr[cur_x][cur_y + 1] <= shark_size) {
                pq.push({{cur_x, cur_y + 1}, dist + 1});
                check[cur_x][cur_y + 1] = true;
            }
        if (cur_x < n - 1)
            if (!check[cur_x + 1][cur_y] and arr[cur_x + 1][cur_y] <= shark_size) {
                pq.push({{cur_x + 1, cur_y}, dist + 1});
                check[cur_x + 1][cur_y] = true;
            }
    }
    return false;
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 9) {
                arr[i][j] = 0;
                x = i;
                y = j;
            }
        }

    return;
}

void solve() {
    do {
        if (x > 0)
            if (arr[x - 1][y] <= shark_size) {
                pq.push({{x - 1, y}, 1});
                check[x - 1][y] = true;
            }
        if (y > 0)
            if (arr[x][y - 1] <= shark_size) {
                pq.push({{x, y - 1}, 1});
                check[x][y - 1] = true;
            }
        if (y < n - 1)
            if (arr[x][y + 1] <= shark_size) {
                pq.push({{x, y + 1}, 1});
                check[x][y + 1] = true;
            }
        if (x < n - 1)
            if (arr[x + 1][y] <= shark_size) {
                pq.push({{x + 1, y}, 1});
                check[x + 1][y] = true;
            }
    } while (bfs());

    cout << shark_move;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}