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
using vld= vector<ld>;
using vvdl = vector<vector<ld>>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vstr = vector<str>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvpii = vector<vector<pair<int, int>>>;
using vpstrstr = vector<pair<str, str>>;
using vpvivi = vector<pair<vector<int>,vector<int>>>;
using vvb = vector<vector<bool>>;
using vb = vector<bool>;
using vch = vector<char>;
using vvch = vector<vector<char>>;
using vvstr = vector<vector<str>>;
using vd = vector<double>;

#define mset multiset
#define mmap multimap
#define uset unordered_set
#define umap unordered_map
#define umset unordered_multiset
#define ummap unordered_multimap
#define pq priority_queue

#define all(v) (v).begin(), (v).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define clr(x) x.clear()
#define pb push_back
#define rs resize
#define eb emplace_back
#define rv reverse
#define mp make_pair
#define F first
#define S second

#define pf push_front
#define pb push_back
#define popf pop_front
#define popb pop_back
#define ft front
#define bk back
#define mxe max_element
#define mne min_element

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
    if (x == 1) return false;
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

const ll K = 6e6+5; // change according to your needs
vll mn(K, 0); // Smallest prime factor of each number
vvll fcv(K); // Prime factorization for each number (only returns each distinct factor once)


void precompute_prime_factors() { // Modified Sieve
    mn[1] = 1; // Base case: 1 has no prime factors
    for (ll i = 2; i < K; i++) {
        if (!mn[i]) { // If i has no prime factor recorded yet, it is a prime number.
            for (ll j = 1; j * i < K; ++j) {
                if (!mn[i * j])
                    mn[i * j] = i; // Mark i as the smallest prime factor for all multiples of i.
            }
        }
    }

    // Generate prime factor lists for every number up to N
    for (int i = 1; i < K; i++) {
        int u = i;
        while (u != 1) {
            int v = mn[u]; // Smallest prime factor of u
            fcv[i].push_back(v); // Add it to the factorization of i
            while (u % v == 0) u /= v; // Remove all occurrences of v from u, we only
            // want to add it once since we want DISTINCT prime factors
        }
    }
}

void sieve() {
    mn[1] = 1; // 1 is not prime
    for (ll i = 2; i < K; i++) {
        if (mn[i] == 0) { // i is prime
            mn[i] = i;
            for (ll j = i * i; j < K; j += i) {
                if (mn[j] == 0) {
                    mn[j] = i; // smallest prime factor of j
                }
            }
        }
    }
}

vi get_primes_up_to_K() {
    vi primes;
    for (ll i = 2; i < K; i++) {
        if (mn[i] == i) primes.pb(i);
    }
    return primes;
}

// get all factors up to n
vvi factors(K);

void getAllFactors(){
    for (int i = 1; i <= K; i++) {
        for (int j = i; j <= K; j += i) {
            factors[j].push_back(i); // i is a divisor of j
        }
    }
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

// Calculate nCr
// don't need to call precompute_factorials for this.
ll nCr_no_mod(int n, int r){
    if (r < 0 || r > n) return 0;
    ll res = 1;
    for (int i=1; i<=r; i++){
        res *= (n - i + 1);
        res /= i;
    }
    return res;
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

const int LOGN = 20; // sparse table interval
const int MAXN = 2e5+5; // fenwick = N, trie  = N * number of bits

// solve time ~ can't solve
// this was a really good problem.
// My idea was to do something like Petya and array, but we store the max idx
// for a sum instead.
// However, that is overkill.
// We can just use a map and a pos array to store the last index.
// Lets make some observations.
// First of all, consider any element, a[i] then we wanna find a j<=i
// such that the sum from j to i is 0.
// This is obviously a prefix sums problem.
// But, doing this for every i is O(N^2). So this is too slow.
// Also, lets make another observation, which is crucial.
// lets say [x,x,x,x,x,x,x,y] has a sum of 0 at y.
// but then for the same index, [x,x,x,y] is actually enough to make the 
// sum 0.
// Then, in this case, we actually just need to consider [x,x,x,y] only
// and not take [x,x,x,x,x,x,x,y] as the range.
// Why? Because greedily, this is always the better choice as [x,x,x,x]
// could potentially give us some subarray within it with sum as 0.
// So, greedily, as soon as the sum is 0, we take it.
// And thats the idea.
// But, we need to know efficiently where is the first index such
// that this happens, or if it happens at all.
// This is where we can use a map via prefix sums to store the latest
// positions.
// We take the prefix sums, note that now the eqn just becomes at some r,
// we want pref[r] - pref[l-1] = 0, which is the same as pref[r] = pref[l-1].
// So, while we take prefix sums, we store this new index for each 
// prefix sum.
// then, if it has been seen before, then that means we found a valid
// pref[l-1] (the latest one).
// Then, this means from [l,r] our array has a beautiful segment.
// Now, since the question wants us to find the max number of beautiful
// segments, its quite obvious that we need to use dp.
// Why? because now that we have the best answer [l,r] at r, then all we
// need to do now is do something like 1 + dp[l-1], where the dp[l-1]
// is the best answer up to l-1 (since we took the segment from l to r
// already).
// Essentially, we can use the dp to store the best answer so far, up to
// and including i.
// We can do this because when our map returns to us the last position
// such that pref[r] - pref[l-1] = 0, we get l-1, not l, so its like 
// we indirectly can do dp[i] = max(dp[i], 1 + dp[j-1]), but we can just do
// 1 + dp[pos[i]] instead, since pos[i] corresponds to j-1, not j.
// meaning, implicitly, we can just dp[pos[pref[i]]] or just dp[pos[i]] since
// we already would've precomputed that.
// and thats the solution.


void solve() {
    int n, m, k;
    cin >> n;
    vll a(n+1);
    for (int i=1; i<=n; i++) cin >> a[i];

    map<ll, ll> memo;
    memo[0] = 0; // 0 is always valid by default so set it first
    vi pos(n+1);
    vll pref(n+1, 0);
    for (int i=1; i<=n; i++){
        pref[i] = pref[i-1] + a[i];
        if (memo.find(pref[i]) != memo.end()) pos[i] = memo[pref[i]];
        else pos[i] = -1;
        memo[pref[i]] = i;
    }
    // printVector(pos);
    vi dp(n+1);
    for (int i=1; i<=n; i++){
        // don't pick
        dp[i] = max(dp[i], dp[i-1]); 
        // pick
        if (pos[i] != -1){
            dp[i] = max(dp[i], dp[pos[i]] + 1);
        }
    }  
    // printVector(dp);
    cout << dp[n] << '\n';
    
}


int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    // sieve();
    // precompute_prime_factors(); // modified sieve
    int t;
    cin >> t;
    while (t--) solve();
    // solve();
    return 0;
}

// fenwick idea:
// I want to generalize this idea.
// lets say we wanna find the max number of segments st. a[l...r] > t
// Then the idea is to do coordinate compression over the prefix sums
// sort(all(pref))
// pref.rs(unique(all(pref)) - pref.begin())
// then remember to do 
// update(lb(all(pref), 0ll) - pref.begin() + 1, 0) as the base case
// to handle pref[r] > t for pref[l-1] == 0.
// since pref[r] - pref[l-1] > t => pref[l-1] < pref[r] - t.
// we can do val = lb(all(pref), pref[r] - t) - pref.begin() + 1.
// then do k = query(val-1), because stricly less than.
// essentially the idea is to store the best dp[l-1] in the fenwick
// for the index of pref[r] - t.
// finally, the transition would be dp[i] = max(dp[i], k + 1)
// because k == l-1.
// then can do j = lb(all(pref), sum) - pref.begin() + 1;
// and update(j, dp[j]); 


// struct BITMax {
//     int n;
//     vector<int> bit; // 1-based
//     BITMax(int n): n(n), bit(n+1, 0) {}
//     void update(int idx, int val){
//         for (; idx <= n; idx += idx & -idx) bit[idx] = max(bit[idx], val);
//     }
//     int query(int idx){ // max on [1..idx]
//         int res = 0;
//         for (; idx > 0; idx -= idx & -idx) res = max(res, bit[idx]);
//         return res;
//     }
// };

// void solve() {
//     int n; 
//     cin >> n;
//     vector<long long> a(n+1);
//     for (int i = 1; i <= n; i++) cin >> a[i];

//     // Build pos[i]: last index j < i with same prefix sum (pref[j] == pref[i])
//     unordered_map<long long,int> last;
//     last.reserve(2*n + 5);
//     long long s = 0;
//     last[0] = 0; // prefix sum 0 at position 0
//     vector<int> pos(n+1, -1);
//     for (int i = 1; i <= n; i++) {
//         s += a[i];
//         auto it = last.find(s);
//         pos[i] = (it == last.end() ? -1 : it->second);
//         last[s] = i;
//     }

//     vector<int> dp(n+1, 0);   // dp[i] = best for prefix [1..i]
//     BITMax bit(n);            // stores dp by index, supports prefix max

//     for (int i = 1; i <= n; i++) {
//         // don't pick
//         dp[i] = dp[i-1];

//         // pick: (pos[i]+1 .. i) is zero-sum when pos[i] != -1
//         if (pos[i] != -1) {
//             int best_before = (pos[i] == 0 ? 0 : bit.query(pos[i])); // equals dp[pos[i]]
//             dp[i] = max(dp[i], best_before + 1);
//         }

//         // publish dp[i] at position i
//         bit.update(i, dp[i]);
//     }

//     cout << dp[n] << '\n';
// }