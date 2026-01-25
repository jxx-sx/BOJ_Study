#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string str, arrs;
        bool first = true;
        int count;
        int start = 0;
        cin >> str >> count >> arrs;
        int end = count;
        for (int j = 0; j < str.size(); j++) {
            if (str[j] == 'R') {
                first = !first;
            } else {
                if (first) {
                    start++;
                } else {
                    end--;
                }
                if (start > end) {
                    break;
                }
            }
        }
        if (start > end) {
            cout << "error\n";
        } else {
            cout << '[';
            arrs = arrs.substr(1, arrs.size() - 2);

            istringstream ss(arrs);

            string strBuffer;
            vector<string> v;

            v.clear();
            while (getline(ss, strBuffer, ',')) {
                if (strBuffer != "") {
                    v.push_back(strBuffer);
                }
            }
            if (first) {
                for (int k = start; k < end; k++) {
                    cout << v[k];
                    if (k != end - 1) {
                        cout << ',';
                    }
                }
            } else {
                for (int k = end - 1; k >= start; k--) {
                    cout << v[k];
                    if (k != start) {
                        cout << ',';
                    }
                }
            }

            cout << "]\n";
        }
    }
}
