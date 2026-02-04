#include <bits/stdc++.h>
using namespace std;

using str = string;
using ch = char;
using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vstr = vector<str>;
using vpii = vector<pair<int, int>>;
using vpstrstr = vector<pair<str, str>>;
using vpvivi = vector<pair<vector<int>,vector<int>>>;
using vvb = vector<vector<bool>>;
using vb = vector<bool>;

#define mset multiset
#define mmap multimap
#define uset unordered_set
#define umap unordered_map
#define umset unordered_multiset
#define ummap unordered_multimap
#define pqpriority_queue

#define all(v) (v).begin(), (v).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define clr(x) x.clear()
#define pb push_back
#define rs resize
#define eb emplace_back
#define mp make_pair
#define F first
#define S second

#define pf push_front
#define pb push_back
#define popf pop_front
#define popb pop_back
#define ft front
#define bk back

#define lb lower_bound
#define ub upper_bound
#define bs binary_search

// Utility Functions
template <typename T>
void printVector(const vector<T>& vec){
    for (const auto& el : vec) cout << el << " ";
    cout << "\n";
}

void precision(int x){
	cout.setf(ios::fixed | ios::showpoint);
	cout.precision(x);
	return;
}

bool is_prime(int x){ // Iterate up to the square root of x
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

// Global Variables
vector<ll> fact, inv_fact;

// Function to calculate modular exponentiation
ll mod_exp(ll base, ll exp, ll mod){
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Precompute factorials and modular inverses
void precompute_factorials(int n, ll mod){
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = (fact[i - 1] * i) % mod;
    for (int i = 0; i <= n; i++) inv_fact[i] = mod_exp(fact[i], mod - 2, mod);
}

// Calculate nCr % MOD
// to use this just call precompute_factorials
ll nCr(int n, int r, ll mod){
    if (n < r || r < 0) return 0;
    return (((fact[n] * inv_fact[r]) % mod) * inv_fact[n - r]) % mod;
}

ll factorial(int a){
	ll ans = 1;
	for (int i = 2; i <= a; i++) {
		ans *= ll(i);
	}
	return ans;
}
 
ll factorial_by_mod(int a, ll mod){
	ll ans = 1;
	for (int i = 2; i <= a; i++) {
		ans *= ll(i);
		ans %= mod;
	}
	return ans;
}

ll binpow(ll a, int b){
	ll ans = 1;
	while (b) {
		if ((b & 1) == 1) {
			ans *= a;
		}
		b >>= 1;
		a *= a;
	}
	return ans;
}
 
ll binpow_by_mod(ll a, ll b, ll mod){
	ll ans = 1;
	while (b) {
		if ((b & 1) == 1) {
			ans *= a;
			ans %= mod;
		}
		b >>= 1;
		a *= a;
		a %= mod;
	}
	return ans;
}

bool is_square(ll a){
	ll b = ll(sqrt(a));
	return (b * b == a);
}
 
bool is_cube(ll a){
	ll b = ll(cbrt(a));
	return (b * b * b == a);
}
 
int digit_sum(ll a){
	int sum = 0;
	while (a) {
		sum += int(a % 10);
		a /= 10;
	}
	return sum;
}

ll gcd(ll a, ll b){
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;}
 
ll lcm(ll a, ll b){
	return a / gcd(a, b) * b;
}


// Constants
const int MAX = int(1e9 + 5);
const ll MAXL = ll(1e18 + 5);
const ll MOD = ll(1e9 + 7);
const ll MOD2 = ll(998244353);

// This is an interesting problem
// I learned a new way of dp here, also the usage of prefix sums and bitmasking
// to greedily check for maximum picks is very intuitive

// What I did right:
// I identified that we had to start from the MSF because 2^i > 2^0 + 2^1 + ... + 2^(i-1)
// I also knew that we can do this greedily, by finding some k segments to make the 
// higest possible bit as 1.
// However, what I tried to do neglected many possible moves that can create x
// if [4, 3] can make the ith bit set
// I immediately set x to 0 and continue
// but [4,3,1] could potentially make the ith bit set as well
// So I knew from there we needed some kind of dp
// knapsack dp would not work here, 2^50 is too big, even if we introduce pruning.
// from here I got stuck, and I gave up.


// What I learned:
// A new type of dp, with a very intuitive bitmasking technique.
// we will use 2D dp, where dp[i][t] represents whether we can partition the first i elements 
// into exactly t valid segments. A "valid" segment is one where the sum of the segment 
// meets the bitwise condition:
// ((s[i] - s[j]) & mask & targ) == targ
// In simple terms, dp[i][t] = true means that we can split the first i elements into t 
// valid segments.

// Understanding the dp transition:
// Outer loop (i loop):
// We are considering the first i elements and checking if it's possible to partition 
// them into exactly t segments.

// Inner loop (j loop):
// We check all possible previous points j (where 0 <= j < i) to find the partition 
// points.
// This means we are considering a partition between j and i. The sum of the segment 
// from j+1 to i is s[i] - s[j].

// The key part of the transition is checking the bitwise condition:
// if (((s[i] - s[j]) & mask & targ) == targ)
// This checks whether the sum of the segment [j+1, i] satisfies the condition
// that the specified bits (given by targ and mask) are set.
// s[i] - s[j]: This is the sum of the elements from index j+1 to i.

// & mask: This ensures we only check the bits of the sum that are relevant for this 
// particular condition (determined by the mask).

// & targ: This checks whether the required bits, as specified by targ, 
// are present in the sum. If they are, the condition will be true.

// State Transition:
// If the bitwise condition is satisfied, we check if we can extend a valid partition 
// up to j into a partition ending at i with exactly t segments:
// for (int t = 0; t < k; t++) {
//     if (dp[j][t]) dp[i][t + 1] = true;
// }
// This means:
// If we can partition the first j elements into t segments (dp[j][t] is true), 
// then we can extend that partition by adding one more segment (from j+1 to i), 
// making the total number of segments t + 1.

// After filling the DP table, the value of dp[n][k] will tell us whether it is possible
// to partition the first n elements into exactly k valid segments.


// Function to check if a particular mask and target are feasible
bool dp_check(int n, int k, const vll &s, ll targ){
    vvb dp(n + 1, vb(k + 1, false));
    dp[0][0] = true; // the first 0 books can form 0 partitions (which is true)

    for (int i = 1; i <= n; ++i){
        for (int j = 0; j < i; ++j){
            if (((s[i] - s[j]) & targ) == targ){
                for (int t = 0; t <= k-1; t++){
                    if (dp[j][t]) dp[i][t + 1] = true;
                }
            }
        }
    }

    return dp[n][k];
}

void solve() {
    int n, k;
    cin >> n >> k;

    vll a(n), s(n + 1, 0);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
        s[i + 1] = s[i] + a[i]; // prefix sums
    }

    ll ans = 0;
    // Here I set bit = 56, it is neccesary.
    // worse case: k=1, all a[i] = 2^50-1.
    // then the sum goes to >= 2^56.
    for (int bit = 56; bit >= 0; bit--){
        // we do ans | (1LL << bit) because lets say we found that the 47 bit can be found
        // and it is the first bit we found to be valid
        // then lets say we have the 45th bit that is valid as well
        // we must ensure that the 47th bit is set before considering the 45th bit
        // because 2^i > 2^0 + 2^1 + ... + 2^(i-1)
        // So, to maximize, we obviously need the 47th bit.
        // anything that comes after is extra, but if we can take it, we will
        // (because it increases our maximum sum)
        if (dp_check(n, k, s, ans | (1LL << bit))){
            ans |= (1LL << bit); // if we can form k segments with n numbers we take this bit
        }
    }

    cout << ans << "\n";
}


int main() {
    fast_io();
    solve();
    return 0;
}


// My attempt, which failed.
// void solve() {
// 	   int n, k, m;
//     cin >> n >> k;

//     ll x, y, count;
//     int targetBit = 0;
//     vll nums(n);
//     for (auto&x : nums) cin >> x;

//     for (int bit=49; bit>=0; bit--){
//         x = 0, count = k;
//         for (int i=0; i<n; i++){
//             x+=nums[i];
//             if (x & (1LL << bit)){
//                 x=0;
//                 count--;
//             }
//         }

//         if (count == 0){
//             targetBit = bit;
//             break;
//         }
//     }

//     cout << targetBit << endl;

//     x = 0, y = 0;
//     bool flag = false;
//     for (int i=0; i<n; i++){
//         if (!flag) x += nums[i];
//         if (flag) y += nums[i];

//         if ((x & (1LL << targetBit)) && !flag){
//             flag = true;
//         }

//         if (y & (1LL << targetBit)){
//             x &= y;
//             y = 0;
//         }
//     }
    

//     cout << x << '\n';
// }

