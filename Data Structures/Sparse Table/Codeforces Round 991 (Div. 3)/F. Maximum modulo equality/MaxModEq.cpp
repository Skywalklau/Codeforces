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

const int N = 1e6 + 5; // change according to your needs
vi mn(N, 0); // Smallest prime factor of each number
vvi fcv(N); // Prime factorization for each number (only returns each distinct factor once)


void precompute_prime_factors() { // Modified Sieve
    mn[1] = 1; // Base case: 1 has no prime factors
    for (int i = 2; i < N; i++) {
        if (!mn[i]) { // If i has no prime factor recorded yet, it is a prime number.
            for (int j = 1; j * i < N; ++j) {
                if (!mn[i * j])
                    mn[i * j] = i; // Mark i as the smallest prime factor for all multiples of i.
            }
        }
    }

    // Generate prime factor lists for every number up to N
    for (int i = 1; i < N; i++) {
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

// Introduction to sparse table:
// Goal: Reducing a range query problem from O(Q*N) to O(NlogN + Q) 
// Problem types that use sparse table:
// Range Minimum Query (RMQ): Find the minimum value in a range [l,r]
// Range Maximum Query (RMQ): Find the maximum value in a range [l,r]
// Range Greatest Common Divisor (GCD).
// Range Sum (less common because prefix sums are simpler to implement and more space-efficient).

// Use Sparse tables when updates are NOT needed, otherwise segment tree.
// Sparse tables work best with operations that satisfy the idempotence property:
// f(f(a,b),c)=f(a,f(b,c)), for this problem, its gcd.
// Other types of indempotent functions include:
// Min, Max, LCM, XOR

// Systematic approach to implementing sparse tables
// 1. Determine the maximum interval size
// max interval size == ceil(log2(N)),
// however its better to hardcode this + 2 for some leeway.

// 2. Construct an array that we will use to build the sparse table
// This step is optional depending on the problem
// Eg. Min/Max queries do not need to precompute a min/max array.
// but for gcd we need to the difference of each neigboring value 
// for XOR we also need the XOR values of each neighboring value

// 3. Set base case: interval of 2^0==1 for each element
// this is always just the element itself from the new array we constructed (or 
// just the element from the original array if its min/max queries).
// sparse.rs(LOGN, vi(sz(b), 1));
// for (int i = 0; i < sz(b); i++) {
//     sparse[0][i] = b[i]; 
// }

// 4. Precompute in logN time, each interval up to max interval size.
// Note: __gcd can be changed with whatever indempotent function we want.
// for (int i = 1; i < LOGN; i++) {
//     for (int j = 0; j + (1 << i) <= sz(b); j++) {
//         sparse[i][j] = __gcd(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]);
//     }
// }

// 5. Query function
// Note: __gcd can be changed with whatever indempotent function we want.
// Note: int k = 31 - __builtin_clz(r - l + 1); is basically a constant time method
// to retrieve the maximum interval for this range.
// the logN solution to get k is to do 1<<i, i++ until i>r-1+1.
// int query(int l, int r) {
//     int k = 31 - __builtin_clz(r - l + 1);
//     return __gcd(sparse[k][l], sparse[k][r - (1 << k) + 1]);
// }


// Why could this problem be solved with sparse table?
// Key Observation: if a % m == b % m
// => abs(a-b) % m
// hence for a % m == b % m == c % m == d % m ...
// => abs(a-b) % m == abs(c-b) % m == abs(d-c) % m ...
// => m = gcd(abs(a-b), abs(c-b), abs(d-c), ...)
// Since gcd is indempotent, and there are many queries, and the data we computed
// for the gcd of a particular range does not change.
// => sparse table || segment tree
// segment tree allows updates for a particular range, but we don't need updates
// to a sequence of numbers after each query hence its overkill to use it
// sparse table is more suitable.

const int LOGN = 20; // hardcoded from doing log(base2) of N, + some leeway

vvi stGCD;

// query function
int get_gcd(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return __gcd(stGCD[k][l], stGCD[k][r - (1 << k) + 1]);
}

void solve() {
    clr(stGCD);
    int n, q; 
    cin >> n >> q;

    vi a(n);
    for (int &x : a) cin >> x;

    // Construct difference array
    vi b;
    for (int i = 1; i < n; i++) {
        b.pb(abs(a[i - 1] - a[i]));
    }

    // Build sparse table for GCD
    stGCD.rs(LOGN, vi(sz(b), 1));
    for (int i = 0; i < sz(b); i++) {
        stGCD[0][i] = b[i];
    }
    for (int i = 1; i < LOGN; i++) {
        for (int j = 0; j + (1 << i) <= sz(b); j++) {
            stGCD[i][j] = __gcd(stGCD[i - 1][j], stGCD[i - 1][j + (1 << (i - 1))]);
        }
    }

    // Process each query
    while (q--) {
        int l, r; 
        cin >> l >> r;
        if (l == r) {
            cout << 0 << " ";
            continue;
        }
        l--; 
        r-=2; // one for 0-index, the other to adjust for difference array
        
        int gcd = get_gcd(l, r);
        cout << gcd << " ";
    }
    cout << '\n';
}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
