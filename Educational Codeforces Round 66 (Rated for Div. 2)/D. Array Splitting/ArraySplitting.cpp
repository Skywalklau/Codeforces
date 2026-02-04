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
const int MOD = 1000000007;
const int INF = 1e9;
const ll LINF = 1e18;

// Utility Functions
template <typename T>
void printVector(const vector<T>& vec) {
    for (const auto& el : vec) cout << el << " ";
    cout << "\n";
}

bool is_prime(int x) { // Iterate up to the square root of x
    for (int i = 2; i * i <= x; i++) { // If x is divisible by i, it's not prime
        if (x % i == 0) return false;
    }
    return true; // If no divisors are found, x is prime
}

// Fast Input/Output
void fast_io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

static bool cmp(ll a, ll b){
    return a > b;
}

void solve(){
    int n, k;

    cin >> n >> k;
    
    // let nums = [7,-3,2,-2,4], k = 3
    // the max cost is 16 after splitting into 3 consecutive non-empty subarrays
    // pro tip: if you see summation related to each element, its most likely 
    // prefix/suffix sum
    // in this case, its suffix sum
    // the suffix sum is suffixSum = [8,1,4,2,4]
    // now notice that if we split the array anywhere, say at i=3 (0 index)
    // then the array is not [7,-3,2] and [-2,4]
    // then the sum becomes 7-3+2 + 2(-2+4) 
    // which, with suffix sum, becomes suffixSum[0] + suffixSum[3]
    // notice that, we ALWAYS have to add suffixSum[0], regardless of what k is.
    // Also, notice that, if we take suffixSum[i] at any point, except i=0.
    // (because we can't split at i=0 otherwise we get a non-empty subarray)
    // this is essentially just suffixSum[0] + suffixSum[i] to get the summation
    // the question required.
    // In other words, our f(i) is implicity handled everytime we take 
    // a suffixSum at any index we chose.
    // so now the question becomes, how do we maximise our suffixSum to maximize
    // the maximum sum?
    // its greedy + sorting.
    // sort the suffixSum from big to small, except for the first element
    // because regardless of how we maniputelate suffixSum, we MUST add suffixSum[0]
    // once.
    // the rest can be added more than once.
    // the array is now suffixSum = [8,4,4,2,1]
    // since k=3, we already included k once with suffixSum[0]
    // so we just add the remaining k, which is k-1 elements from suffixSum
    // so it will be 8+4+4 = 16.

    int a[n];
    for (int i=0; i<n; i++) cin >> a[i];

    vll suffixSum(n,0);
    ll sum = 0;
    for (int i=n-1; i>=0; i--){
        sum += a[i];
        suffixSum[i] = sum;
    } 

    ll result = 0;

    sort(suffixSum.begin()+1, suffixSum.end(), cmp);
    for (int i=0; i<k; i++){
        result += suffixSum[i];
    }

    cout << result << '\n';
}

int main() {
    fast_io();
    // int t;
    // cin >> t;
    // while (t--) solve();
    solve();
    return 0;
}
