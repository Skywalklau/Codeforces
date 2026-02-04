#include <bits/stdc++.h>
using namespace std;

int n;
long long k;
long long M;

vector<vector<int>> memo;   // -1 = unvisited, 0 = impossible, 1 = possible
vector<vector<int>> choice; // store chosen block length for reconstruction

bool dfs(int used, int sum) {
    if (sum > n * n) return false;
    if (used == n) return sum == M;
    int &res = memo[used][sum];
    if (res != -1) return res;

    for (int len = 1; len <= n - used; len++) {
        int newSum = sum + len * len;
        if (newSum > n * n) break;
        if (dfs(used + len, newSum)) {
            choice[used][sum] = len;  // remember choice for reconstruction
            return res = 1;
        }
    }
    return res = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        long long T = 1LL * n * (n - 1) / 2;
        if (k < 0 || k > T) {
            cout << 0 << '\n';
            continue;
        }
        M = 1LL * n * n - 2 * k;

        memo.assign(n + 1, vector<int>(n * n + 1, -1));
        choice.assign(n + 1, vector<int>(n * n + 1, 0));

        if (!dfs(0, 0)) {
            cout << 0 << '\n';
            continue;
        }

        // reconstruct run lengths
        vector<int> runs;
        int used = 0, sum = 0;
        while (used < n) {
            int len = choice[used][sum];
            runs.push_back(len);
            used += len;
            sum += len * len;
        }

        vector<int> perm(n);
        int pos = 0;
        int num = n;
        for (int len : runs) {
            vector<int> tmp;
            for (int i = 0; i < len; i++) tmp.push_back(num--);
            sort(tmp.begin(), tmp.end());
            for (int v : tmp) perm[pos++] = v;
        }

        for (int i = 0; i < n; i++) {
            if (i) cout << ' ';
            cout << perm[i];
        }
        cout << '\n';
    }
    return 0;
}
