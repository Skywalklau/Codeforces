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

// Constants
const int L = 26;  // Number of lowercase letters

// Global variables
vi arr, brr, crr;

// Function to process each word into masks
void build(const vector<string>& srr) {
    int n = srr.size();
    arr.resize(n);
    brr.resize(n);
    for (int i = 0; i < n; ++i) {
        for (char c : srr[i]) {
            arr[i] ^= (1 << (c - 'a'));  // XOR to calculate parity of each character
            brr[i] |= (1 << (c - 'a'));  // OR to track the presence of each character
        }
    }
}

// Function to calculate the number of nightmares excluding letter `c`
ll calc(int c, int n) {
    crr.clear();
    for (int i = 0; i < n; ++i) {
        if (!(brr[i] & (1 << c))) {  // Ignore words containing the `c`-th letter
            crr.pb(arr[i]);
        }
    }

    sort(all(crr));  // Sort the remaining parity masks for binary search
    ll ans = 0;
    int mask = ((1 << L) - 1) ^ (1 << c);  // Complement mask for parity condition

    // Iterate through each mask and count complementary matches
    for (int i = 0; i < crr.size(); ++i){
        int target = crr[i] ^ mask; // get target such that we can make all characters odd
        // if a is even for this string, then our target is set as 1, meaning we need an odd
        // count of a for the character a to be odd in the concatenation.
        // likewise if a is odd for this string, then our target is set as 0, meaning we need 
        // an even count of a for the character a to be odd in the concatenation.

        // this implicity handles the condition for the length to be odd 
        // because if all characters occur in odd counts, since we have 25(which is odd) number
        // characters, 25 * x == odd, where x is the total number 
        // of characters in the string, which is odd. so odd * odd == odd
        ans += upper_bound(all(crr), target) - lower_bound(all(crr), target);
    }

    return ans / 2;  // Since each pair is counted twice
}

// Main function to calculate total number of nightmares
ll solveNightmares(const vector<string>& srr) {
    int n = srr.size();
    build(srr);  // Precompute masks for all words
    ll total = 0;
    for (int c = 0; c < L; ++c) {
        total += calc(c, n);  // Calculate nightmares for each banned letter
    }
    return total;
}

// Time complexity : O(summation of len(s) + 26 * N * log(N))
void solve() {
    int n;
    cin >> n;
    vector<string> srr(n);
    for (int i = 0; i < n; ++i) {
        cin >> srr[i];
    }
    cout << solveNightmares(srr) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
