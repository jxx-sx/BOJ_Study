    #include <iostream>
    #include <vector>

    using namespace std;

    int main() {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        int n, temp;
        cin >> n;
        vector<int> tri[n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i + 1; j++) {
                cin >> temp;
                tri[i].push_back(temp);
            }
        }

        int i = n - 2;
        while (i >= 0) {
            for (int j = 0; j < tri[i].size(); j++) {
                tri[i][j] += (tri[i + 1][j] > tri[i + 1][j + 1]) ? tri[i + 1][j] : tri[i + 1][j + 1];
            }
            i--;
        }
        cout << tri[0][0];
    }