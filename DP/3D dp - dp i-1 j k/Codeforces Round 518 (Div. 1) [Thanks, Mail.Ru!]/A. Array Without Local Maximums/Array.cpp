#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MOD = 998244353;
const int MAX_A = 200;

int main() {
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // DP table: dp[i][v][flag] = number of ways to restore the array up to index i with a[i] = v and flag = flag
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(MAX_A + 1, vector<int>(2, 0)));

    // Initialize for the first element
    for (int v = 1; v <= MAX_A; ++v) {
        if (a[0] == -1 || a[0] == v) {
            dp[1][v][0] = 1;  // First element can only have flag=0 (since it's the start of the array)
        }
    }

    // DP processing
    for (int i = 2; i <= n; ++i) {
        vector<int> prefix_0(MAX_A + 2, 0), prefix_1(MAX_A + 2, 0);

        // Compute prefix sums for the previous row (i-1)
        for (int v = 1; v <= MAX_A; ++v) {
            prefix_0[v] = (prefix_0[v - 1] + dp[i - 1][v][0]) % MOD;
            prefix_1[v] = (prefix_1[v - 1] + dp[i - 1][v][1]) % MOD;
        }

        // Compute dp for the current row (i)
        for (int v = 1; v <= MAX_A; ++v) {
            if (a[i - 1] != -1 && a[i - 1] != v) continue;

            // Calculate dp[i][v][0] (ascending or equal from the previous element)
            dp[i][v][0] = (prefix_0[v - 1] + prefix_1[v - 1]) % MOD;

            // Calculate dp[i][v][1] (descending from the previous element)
            dp[i][v][1] = (dp[i - 1][v][0] + (prefix_1[MAX_A] - prefix_1[v - 1] + MOD) % MOD) % MOD;
        }
    }

    // Sum all dp[n][v][1] for the final answer
    int ans = 0;
    for (int v = 1; v <= MAX_A; ++v) {
        if (a[n - 1] == -1 || a[n - 1] == v) {
            ans = (ans + dp[n][v][1]) % MOD;
        }
    }

    cout << ans << endl;

    return 0;
}
