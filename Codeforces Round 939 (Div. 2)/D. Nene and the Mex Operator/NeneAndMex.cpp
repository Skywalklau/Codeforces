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

// Global variables
int n;
vi a;
vi cnt; // Count array for MEX calculation
vector<pii> operations; // Stores the operations (l, r)

// Perform the operation on the range [l, r]
void performOperation(int l, int r) {
    fill(all(cnt), 0);
    for (int i = l; i <= r; ++i) {
        if (a[i] <= n) cnt[a[i]]++;
    }

    int mex = 0;
    while (cnt[mex]) ++mex; // Compute MEX

    for (int i = l; i <= r; ++i) {
        a[i] = mex; // Set all elements in the range to MEX
    }

    operations.pb({l, r});
}

// Recursively build the desired array for range [l, r]
void buildArray(int l, int r) {
    if (l == r) {
        if (a[l] != 0) performOperation(l, r);
        return;
    }

    buildArray(l, r - 1);

    // If the current element doesn't match the desired value
    if (a[r] != r - l) {
        performOperation(l, r);
        buildArray(l, r - 1);
    }
}

// simulating the process of how buildArray works
// lets say we have [1,2,1,3], we can definitely make this into [4,4,4,4]
// we start with buildArray(0,3)
// then recursion makes it into buildArray(0,0)
// in the base case, we make the first element into 0
// now the array is [0,2,1,3] and we return; => go up on level of recursion depth (1 move)
// now since a[1]==2 != 1-0
// we can call performOperations(0,1)
// which now makes the array into [1,1,1,3] (2 moves)
// we call buildArray(0,0), which call performOperations(0,0)
// which now makes the array into [0,1,1,3] (3 moves)
// again since a[2]==1 != 2-0
// we call performOperation(0,2) to make the array into [2,2,2,3] (4 moves)
// again we backtrack, calling buildArray(0,1) then backtrack again to buildArray(0,0)
// performOperations(0,0) now makes the array to [0,2,2,3] (5 moves)
// going one level above recursion depth again
// since a[1]==2 != 1-0
// we call performOperations(0,1) to make the array into [1,1,2,3] (6 moves)
// you get the gist,
// last one goes to performOperations(0,0) to make the array into [0,1,2,3]
// Now, at the highest level of recursion, we see that a[3]==3 == 3-0
// recursion ends...
// HOWEVER, there is one final move of performOperations needed, which is performOperations(0,3)
// to make the array into [4,4,4,4]
// this is done outside the recursion itself.



void solve() {
    // The trick to solving this problem is to realise that the maximum MEX we can set
    // on a subarray is the length of the subarray itself
    // if a subarray has length n, then the maximum value we can set to each value in the 
    // subarray is n, making the sum n*n = n^2
    // since n is small, we can just find all the subsets which have values on and off for each bit
    // where each bit represents each element
    // if the bit is on we take it and find the consecutive on elements and get their sum
    // which is the r-l+1, r is the rightmost element, l is the leftmost element in the subarray
    // +1 due to indexing.
    // from there we try all possible combinations, and once done and we get the mask representing
    // the maximum sum
    // we use that mask to build the operations.

    // buildArray essentially constructs the array in the form [0,1,2,...,n] for the array 
    // of length n
    // performOperations get the mex of the current array input, and makes everything equal
    // to the mex
    // we can combine these 2 functions, using buildArray recursively to construct the final
    // form of the array into [0,1,2,...,n-1]
    // and then use one final call of performOperations to make
    // the array into [n,n,n,...,n]

    // Time complexity : O(2^N + 2^k + 2^m + (however many gaps to make [n,n,n,...,n]))
    // so Time complexity: O(2^(N+1)) if we need to change everything, which is feasible.
    // where k and m are the length of the subarrays.
    cin >> n;
    a.resize(n);
    cnt.resize(n + 1);
    operations.clear();

    for (int i = 0; i < n; ++i) cin >> a[i];

    int maxSum = 0, bestMask = 0;

    // Try all subsets of the array using a bitmask
    for (int mask = 0; mask < (1 << n); ++mask) {
        int tempSum = 0;

        for (int l = 0; l < n; ++l) {
            if (mask & (1 << l)) {
                int r = l;
                while (r + 1 < n && (mask & (1 << (r + 1)))) ++r;

                tempSum += (r - l + 1) * (r - l + 1);
                l = r;
            } else {
                tempSum += a[l];
            }
        }

        if (tempSum > maxSum) {
            maxSum = tempSum;
            bestMask = mask;
        }
    }

    // Apply the best mask and build the array
    for (int l = 0; l < n; ++l) {
        if (bestMask & (1 << l)) {
            int r = l;
            while (r + 1 < n && (bestMask & (1 << (r + 1)))) ++r;

            buildArray(l, r);
            performOperation(l, r); // final call to make array into [n,n,n...,n]
            l = r;
        }
    }

    // Output the results
    cout << maxSum << " " << sz(operations) << "\n";
    for (const auto& op : operations) {
        cout << op.F + 1 << " " << op.S + 1 << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}

