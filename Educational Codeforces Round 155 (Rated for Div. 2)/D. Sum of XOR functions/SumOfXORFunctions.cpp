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

void solve() {
    int n;
    cin >> n;
    vll a(n);
    for (ll &x : a) cin >> x;

    ll result = 0;
    
    // let XOR == xor of all elements in a particular range.
    // problem breakdown: we want to find all subarrays XOR
    // brute force does not work, (3 x 10^5)^2 > 2 x 10^8;  
    // intuition: look at this problem bit by bit.
    // for any number in a range [l, r]
    // for each of their bits,
    // f(l, r) = al ^ al+1 ^ ... ar == 1 or 0
    // f(l, r) = a1 ^ a1+1 ^ ... ^ ar == 0 if l-r+1 is even
    // f(l, r) = a1 ^ a1+1 ^ ... ^ ar == 1 if l-r+1 is is odd
    // Knowing this, f(l,r) * (r-l+1) is relevant iff f(l, r) == 1 => [l, r] has 
    // odd number of 1's
    

    // To find the summation,
    // we need to determine if f(l, r) is a valid range, i.e f(l, r) == 1
    // Notice that, we can use a variant of prefix sum
    // for any point we are traversing r
    // we can cumulatively keep track of ar ^ ar-1 ^ ar-2 ... ^ a0
    // to determine if [0, r] has even 1's or odd 1's,
    // then for any point of r, we keep track of the number of l's
    // such that f(l, r) == 1
    
    // Notice that, for any value of r,
    // if there is an even number of 1's,
    // we need to find the number of l's such that the f(l, r) == 1
    // that means we need to find the l's which allows [l, r] to have odd number of 1's
    // so that f(l, r) == 1
    // Note, even 1's - odd 1's = odd 1's
    // we can do this by using cnt[1];
    // where cnt[1] represent the number of l's such that [l, r] has odd number of 1's.
    // so, whenever there is an odd count of 1's, cnt[1]++, only until we 
    // encounter a number with their current bit == 1, then we flip the bit.
    // this way, we can find the number of ranges such that [l,r] have an odd number of 1's
    // for f(l, r) == 1
    // (1) is the bit we are looking at
    // 1 0 0 1 1 0 0 (1)
    // r = 0: cnt[1] = 1
    // r = 1: cnt[1] = 2
    // r = 2: cnt[1] = 3
    // r = 3: cnt[1] = 3
    // r = 4: cnt[1] = 4
    // r = 5: cnt[1] = 5
    // r = 6: cnt[1] = 6
    // r = 7: cnt[1] = 6
    // at (1), we have 6 subarrays such that f(l, r) == 1
    // [1] 0 0 1 1 0 0 (1)
    // [1 0] 0 1 1 0 0 (1)
    // [1 0 0] 1 1 0 0 (1)
    // [1 0 0 1 1] 0 0 (1)
    // [1 0 0 1 1 0] 0 (1)
    // [1 0 0 1 1 0 0] (1)
    
    // Notice that, for any value of r,
    // if there is an odd number of 1's,
    // we need to find the number of l's such that the f(l, r) == 1
    // that means we need to find the l's which allows [l, r] to have odd number of 1's
    // so that f(l, r) == 1
    // Note, odd 1's - even 1's = odd 1's
    // we can do this by using cnt[0];
    // so, whenever there is an even count of 1's, cnt[0]++, only until we 
    // encounter a number with their current bit == 1, then we flip the bit.
    // this way, we can find the number of ranges such that [l,r] have an odd number of 1's
    // for f(l, r) == 1
    // (1) is the bit we are looking at
    // 1 0 0 1 1 0 0 1 (1)
    // r = 0: cnt[0] = 1 (base case, no 1's means 1 way to make it, which is empty, [])
    // r = 1: cnt[0] = 1
    // r = 2: cnt[0] = 1
    // r = 3: cnt[0] = 2
    // r = 4: cnt[0] = 2
    // r = 5: cnt[0] = 2
    // r = 6: cnt[0] = 2
    // r = 7: cnt[0] = 3
    // r = 8: cnt[0] = 3
    // [1 0 0 1 1 0 0 1 (1)]
    // 1 0 0 1 [1 0 0 1 (1)]
    // 1 0 0 1 1 0 0 1 [(1)]

    
    // if f(l, r) == 1, it is valid. 
    // The summation[l,r](f(l,r) * (r-l+1)) == summation[l,r](1 * (r+1)) - summation[l,r](l)
    // == summation[l,r](r+1) - summation[l,r](l)
    // since we have cnt[0] || cnt[1] of such ranges of [l,r]
    // total contribution += cnt[0 || 1] * summation[l,r](r+1) - summation[l,r](l)
    // where cnt[0] when r has odd number of of 1's and cnt[1] when r has even number of 1's
    // notice that cnt[0] = 1 is a base case, why?
    // 1 0 (0) 1 1 0 0 1 1
    // at (0),
    // we have 3 subarrays of odd 1's, if cnt[0] = 0 that would mean 0
    // subarrays with odd 1's, which is wrong. 

    // on the other hand, why is cnt[1] = 0 the base case?
    // 1 0 0 (1) 1 0 0 1 1
    // at (1), r = 3, cnt[1] = 3, cnt[0] = 2
    // if cnt[1] = 1 as a base case, then cnt[1] = 4 at r=3
    // notice that, there is actually only 3 subarrays such that f(l,r) == 1, not 4
    // [1] 0 0 (1) 1 0 0 1 1
    // [1 0] 0 (1) 1 0 0 1 1
    // [1 0 0] (1) 1 0 0 1 1
    // hence cnt[1] = 0 is the base case.

    // For the last part, how do we find summation[l,r](l)?
    // pretty straightforward, prefix sum! But with a twist for both even odd cases.
    // if the current iteration of r is having an odd number of 1's
    // summation[l,r](l) must be the even prefix sum.
    // if the current iteration of r is having an even number of 1's
    // summation[l,r](l) must be the odd prefix sum.
    // we can do this by using sumOfL[0] and sumOfL[1]
    // sumOfL[0] for even prefix sum
    // sumOfL[1] for odd prefix sum


    // Process each bit separately
    for (int bitPos = 0; bitPos < 30; bitPos++) {
        ll currentBit = 1ll << bitPos;
        vll cnt(2, 0); // Count of even/odd prefixes
        vll sumOfL(2, 0); // Sum of indices with even/odd prefixes
        cnt[0] = 1;   // base case
        ll cur = 0;

        for (int r = 0; r < n; r++) {
            if (a[r] & currentBit) cur ^= 1;
            cnt[cur]++;
            sumOfL[cur] = (sumOfL[cur] + r + 1) % MOD;
            ll cv = (cnt[cur ^ 1] * (r + 1)) % MOD - sumOfL[cur ^ 1];
            cv = (cv + MOD) % MOD;  // Ensure positive
            result = (result + cv * currentBit) % MOD;
        }
    }
    
    // Output the result
    cout << result << "\n";
}


int main() {
    fast_io();
    solve();
    return 0;
}
