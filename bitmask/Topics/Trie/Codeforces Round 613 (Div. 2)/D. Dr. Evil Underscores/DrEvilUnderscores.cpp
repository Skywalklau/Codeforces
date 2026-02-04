#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define all(v) (v).begin(), (v).end()
#define sz(x) (int)(x).size()
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define F first
#define S second

// Constants
const int MOD = 998244353;
const int INF = 1e9;
const ll LINF = 1e18;

// Utility Functions
template <typename T>
void printVector(const vector<T>& vec) {
    for (const auto& el : vec) cout << el << " ";
    cout << "\n";
}

// Fast Input/Output
void fast_io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

// Approach:
// we cannot use a trie (maybe you can use it but it might be overkill)
// but I dont think its viable because X is too big
// we need to loop X from 0 to 2^30-1 for that
// Another approach is backtracking dfs.
// We know that, starting from the MSB
// if all the number are 0 at the ith bit
// we can set X as 0, then 0^0 = 0. Hence no contribution to max(ai ^ X) for this ith bit
// Likewise, if all the numbers are 1 at the ith bit
// we can set X as 1, then 1^1 = 0. Hence no contribution to max(ai ^ X) for this ith bit

// However, if some numbers are 0 and some other numbers are 1 at the ith bit.
// then regardless of how we choose our X at the ith bit, we are bound to add 2^i
// using the above as base cases we can repeat our statement recursively until we
// traverse all the bits.


// Time complexity: O(nlog(base 2)[max(a)]) because recursion depth is at most 30
// multiply by n because regardless of splitting into groups the total numbers is still n
// so we will always loop n for each iteration.
// ai is at most 30 bits, each bit is either on or off, so its 2^30 at most.

// Note: This problem can also be solved via trie, but its overkill.
// How? Build the trie, then dfs at each level with the same principle below.
// If both paths exists, then we try both paths, so return 
// min(dfs(left,bit-1),dfs(right, bit-1)) + (1 << bit)
// otherwise we return dfs(flip bit, bit-1)
// the time complexity is still the same, but it takes more space.
int dfs(vi& c, int bit){
    if (bit < 0) return 0;

    vi l, r;
    for (auto &i : c){
        if (((i >> bit) & 1) == 0) l.pb(i); // Group with current bit off
        else r.pb(i);                      // Group with current bit on
    }

    if (l.empty()) return dfs(r, bit - 1); // If no numbers in the left group
    if (r.empty()) return dfs(l, bit - 1); // If no numbers in the right group

    // Recursively solve for both groups and choose the minimum result
    return min(dfs(l, bit - 1), dfs(r, bit - 1)) + (1 << bit);
}

void solve() {
    int n;
    cin >> n;
    vi a(n);
    for (auto &i : a) cin >> i;

    cout << dfs(a, 30) << endl;
}

int main() {
    fast_io();
    // int t;
    // cin >> t;
    // while (t--) {
    //     solve();
    // }
    solve();
    return 0;
}
