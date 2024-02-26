#include <iostream>

using namespace std;

long long arr[50];

char dfs(int x, int i) {
    if (x <= 2)
        return "Messi Gimossi"[i];
    if (i < arr[x - 1])
        return dfs(x - 1, i);
    if (arr[x - 1] == i)
        return ' ';
    return dfs(x - 2, i - arr[x - 1] - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    arr[1] = 5;
    arr[2] = 13;

    for (int i = 2; i <= 45; i++)
        arr[i + 1] = arr[i - 1] + arr[i] + 1;
    char ch = dfs(45, n - 1);
    if (ch == ' ')
        cout << "Messi Messi Gimossi";
    else
        cout << ch;
}
