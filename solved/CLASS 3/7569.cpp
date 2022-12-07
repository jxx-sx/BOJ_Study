#include <iostream>
#include <vector>
using namespace std;
int dz[] = {1, -1, 0, 0, 0, 0};
int dx[] = {0, 0, 1, -1, 0, 0};
int dy[] = {0, 0, 0, 0, 1, -1};
int x, y, z;
int ***arr;
vector<pair<int, pair<int, int>>> v;

void print() {

    for (int i = 0; i < z; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < x; k++) {
                cout << arr[i][j][k] << ' ';
            }
            cout << endl;
        }
    }
    cout << endl;
}
void bfs() {
    int tmp_x, tmp_y, tmp_z;
    int count = 0;
    while (!v.empty()) {
        vector<pair<int, pair<int, int>>> tmp;
        for (int j = 0; j < v.size(); j++) {
            int cur_z = v[j].first;
            int cur_y = v[j].second.first;
            int cur_x = v[j].second.second;
            for (int i = 0; i < 6; i++) {
                tmp_z = cur_z + dz[i];
                tmp_x = cur_x + dx[i];
                tmp_y = cur_y + dy[i];
                if (tmp_x >= 0 and tmp_x < x and tmp_y >= 0 and tmp_y < y and tmp_z >= 0 and tmp_z < z) {
                    if (arr[tmp_z][tmp_y][tmp_x] == 0) {
                        arr[tmp_z][tmp_y][tmp_x] = 1;
                        tmp.push_back({tmp_z, {tmp_y, tmp_x}});
                    }
                }
            }
        }
        v = tmp;
        count++;
    }

    for (int i = 0; i < z; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < x; k++) {
                if (arr[i][j][k] == 0) {
                    cout << -1;
                    return;
                }
            }
        }
    }
    cout << count - 1;
}

void init() {
    cin >> x >> y >> z;
    arr = new int **[z];
    for (int i = 0; i < z; i++) {
        arr[i] = new int *[y];
        for (int j = 0; j < y; j++) {
            arr[i][j] = new int[x];
            for (int k = 0; k < x; k++) {
                cin >> arr[i][j][k];
                if (arr[i][j][k] == 1) {
                    v.push_back({i, {j, k}});
                }
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    bfs();
}