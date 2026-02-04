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
using vpstrstr = vector<pair<str, str>>;
using vpvivi = vector<pair<vector<int>,vector<int>>>;
using vvbb = vector<vector<bool>>;
using vb = vector<bool>;
using vvch = vector<vector<char>>;

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

const int K = 1e6 + 5; // change according to your needs
vi mn(K, 0); // Smallest prime factor of each number
vvi fcv(K); // Prime factorization for each number (only returns each distinct factor once)


void precompute_prime_factors() { // Modified Sieve
    mn[1] = 1; // Base case: 1 has no prime factors
    for (int i = 2; i < K; i++) {
        if (!mn[i]) { // If i has no prime factor recorded yet, it is a prime number.
            for (int j = 1; j * i < K; ++j) {
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

const int LOGN = 18; // sparse table interval
const int MAXN = 1e5+5; // fenwick = N, trie  = N * number of bits

int sparseMin[LOGN][MAXN], sparseMax[LOGN][MAXN];


// This was a really good problem.
// I missed out on 2 things, and because of it, I could not solve this problem.
// 1. The property that [j, i] is monotonic after finding RMaxQ && RMinQ.
// for some i and j.
// 2. Perspective of dp transition, I went from left to right, but it should 
// be from right to left, which makes sense because going from left to right
// you will not able to consider previous states to build on top of it...

// 1. Why is [j,i] monotonic after finding RMaxQ && RMinQ?
// proof:
// lets say we found the RMaxQ and the RMinQ for some range [i, j]
// so the max val is = 8, and the min val is lets say 3.
// so, the difference will be 5.
// as you decrease the size of [i,j], meaning decreasing i for a fixed j.
// then realise that the max val will only decrease or stay the same,
// and the min val will only increase or stay the same.
// lets say [i,j] is [4,3,4,5,4,8], so difference is 8-3=5.
// then if we decrease the size by 2.
// then the array becomes [4,5,4,8], notice that, the max is still 8, but
// the min is now 4, but its >= 3.
// so min will only every increase || stay the same.
// the same can be said for max.
// Hence, the difference will only decrease or stay the same as we decrease i.
// => if [i,j] is a valid range (meaning <= s), then everything before
// is valid as well.
// => we can do bs safely because of this monotonic condition.

// 2. Now for the dp.
// If we went from right to left, we can't really consider previous states.
// but going from left to right, we can.
// Idea:
// for each element, we bs the largest range including this current element
// such that both conditions are satisfied (>=l && <=s).
// then, we would have some range [j,i].
// we can then do another bs to search for j to check how many strips are 
// already formed at j.
// then we build on top of it. => +1 from dp[j] => dp[i] = dp[j]+1.
// but obviously we need to check if dp[j] is valid first.


void createSparseMax(vi& a){ 
    for (int i=0; i<sz(a); i++) sparseMax[0][i] = a[i];
    for (int i=1; i<LOGN; i++){
        for (int j=0; j+(1<<i)<=sz(a); j++){
            sparseMax[i][j] = max(sparseMax[i-1][j], sparseMax[i-1][j+(1<<(i-1))]);
        }
    }
}

void createSparseMin(vi& a){
    for (int i=0; i<sz(a); i++) sparseMin[0][i] = a[i];
    for (int i=1; i<LOGN; i++){
        for (int j=0; j+(1<<i)<=sz(a); j++){
            sparseMin[i][j] = min(sparseMin[i-1][j], sparseMin[i-1][j+(1<<(i-1))]);
        }
    }
}

int queryMin(int l, int r){
    int k = 31 - __builtin_clz(r-l+1);
    return min(sparseMin[k][l], sparseMin[k][r-(1<<k)+1]); 
}

int queryMax(int l, int r){
    int k = 31 - __builtin_clz(r-l+1);
    return max(sparseMax[k][l], sparseMax[k][r-(1<<k)+1]); 
}

int binarySearch(int i, int& s){
    int low = 0, high = i, ans = i;
    while (low <= high){
        int mid = low + (high-low)/2;
        if (queryMax(mid, i) - queryMin(mid, i) <= s){
            ans = mid;
            high = mid - 1;
        } 
        else low = mid + 1;
    }
    return ans;
}

void solve() {
    int n, s, l;
    cin >> n >> s >> l;

    vi a(n);
    for (int &x : a) cin >> x;

    createSparseMax(a);
    createSparseMin(a);


    // sparse dp, you can do vi dp(n), but there are redundant values
    // that will not store anything.
    // dp[i] = min number of strips formed at up to i (excluding i)
    map<int, int> dp;
    dp[0] = 0; // base case, we always build on top of it.

    for (int i = 0; i < n; i++){
        int j = binarySearch(i, s);
        auto it = dp.lb(j);

        if (it != dp.end() && (i - it->F + 1 >= l)){
            dp[i+1] = it->S + 1; // new strip at i+1.
        }
    }

    if (!dp.count(n)) cout << -1 << '\n';
    else cout << dp[n] << '\n';
    
}


int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    // int t;
    // cin >> t;
    // while (t--) solve();
    solve();
    return 0;
}
