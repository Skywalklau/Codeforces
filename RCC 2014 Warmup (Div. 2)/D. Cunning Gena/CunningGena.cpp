#include <bits/stdc++.h>
using namespace std;

#define int long long
const int LL_MAX = LLONG_MAX;

int n, m, b;

void solve() {
    cin >> n >> m >> b;

    vector<vector<int>> friends(n);

    for (int i = 0; i < n; i++) {
        int monitor, cost, problemsCount;
        cin >> cost >> monitor >> problemsCount;

        friends[i] = {monitor, cost, 0};

        while (problemsCount--) {
            int problem;
            cin >> problem;
            friends[i][2] |= (1 << (problem - 1));  // Create bitmask for problems
        }
    }

    // Sort by monitor requirement
    sort(friends.begin(), friends.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    });

    // Initialize dp
    vector<int> dp(1 << m, LL_MAX);
    dp[0] = 0;  // Base case: no problems solved, no cost

    int minimumCost = LL_MAX;

    for (int i = 0; i < n; i++) {
        int monitorReq = friends[i][0];
        int cost = friends[i][1];
        int problemMask = friends[i][2];

        // Transition
        for (int mask = (1 << m) - 1; mask >= 0; mask--){ 
            int newMask = mask | problemMask;
            if (dp[mask] <= LL_MAX - cost) { // Prevent overflow, and also prevent invalid states
                dp[newMask] = min(dp[newMask], dp[mask] + cost);
            }
        }

        // Update minimum cost
        if (dp[(1 << m) - 1] <= LL_MAX - b * monitorReq) { // Prevent overflow
            minimumCost = min(minimumCost, dp[(1 << m) - 1] + b * monitorReq);
        }
    }

    cout << (minimumCost >= LL_MAX ? -1 : minimumCost) << '\n';
}

#undef int
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}


// #include "bits/stdc++.h"
// using namespace std;
// #define int long long
// #define double long double
// #define pii pair<int,int>
// #define s second
// #define f first
// #define pb push_back
// #define oo 1000000000000000000ll
// #define all(a) (a).begin(), a.end()
// #define rall(a) (a).rbegin(), a.rend()
// #define ln '\n'

// const int INF = 0x3f3f3f3f3f3f3f3f; // 64-bit infinity

// int n, m, b, old[1<<20], nw[1<<20];
// array<int, 3> a[105]; // (# monitor, cost, mask)

// void solve(){
//     cin >> n >> m >> b;
//     for (int i = 0; i < n; i++){
//         cin >> a[i][1] >> a[i][0]; int x; cin >> x;
//         a[i][2] = 0;
//         while (x--) {int y; cin >> y; a[i][2] |= (1<<(y-1));}
//     }
//     sort(a, a+n);
//     memset(old, 0x3f, sizeof(old));
//     memset(nw, 0x3f, sizeof(nw));

//     old[0] = 0;
//     int ans = INF;

//     for (int i = 0; i < n; i++){
//         for (int j = 0; j < (1 << m); j++){
//             int x = (j | a[i][2]);
//             nw[x] = min(nw[x], a[i][1] + old[j]);
//         }
//         for (int j = 0; j < (1 << m); j++) old[j] = min(old[j], nw[j]), nw[j] = INF;
//         ans = min(ans, old[(1<<m)-1] + b * a[i][0]);
//     }
//     cout << (ans >= INF? -1: ans) << ln;
// }


// signed main(){
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);
//     // int TT; cin >> TT;
//     // while (TT--) solve();
//     // while (1) solve();
//     solve();

// }