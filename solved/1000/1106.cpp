#include <iostream>

#define INF 1'000'000'000
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, c;
pair<int, int> arr[21];
int dp[21][1001];

void init() {
  cin >> c >> n;
  for (int i = 1; i <= n; i++)
    cin >> arr[i].first >> arr[i].second;
  for (int i = 1; i <= 1000; i++)
    dp[0][i] = INF;
}

void solve() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= c; j++) {
      dp[i][j] = dp[i - 1][j];
      for (int k = 1;; k++) {
        if (j - arr[i].second * k < 0) {
          dp[i][j] = min(dp[i][j], arr[i].first * k);
          break;
        }
        dp[i][j] =
            min(dp[i][j], dp[i - 1][j - arr[i].second * k] + arr[i].first * k);
      }
    }
  }
  cout << dp[n][c];
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  init();
  solve();

  return 0;
}