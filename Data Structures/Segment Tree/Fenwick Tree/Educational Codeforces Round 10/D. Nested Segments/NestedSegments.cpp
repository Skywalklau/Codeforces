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
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits
 
int fen[MAXN];

// Nice problem, I learned something here.
// yea this problem is similar to Turn Off the TV || Petya and Array
// However the case here is that we don't actually use prefix sums...
// Why? I think its possible to use prefix sums, but it would harder to 
// implement and idk how tbh.
// The method I'm using is much better as it has similarities to Turn off the
// TV and Petya, which I am more comfortable with.


void update(int i, int val, int n){
    while (i <= n){
        fen[i] += val;
        i += i & -i;
    }
}
 
int query(int i){
    int ans = 0;
    while (i > 0){
        ans += fen[i];
        i -= i & -i;
    }
    return ans;
}
 
 
void solve() {
	int n, k, m;
    cin >> n;
 
    vector<pair<pii, int>> intervals; // store intervals with their original index
    vi comp; // compressed coordinates
 
    for (int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        intervals.pb({{l, r}, i}); // store the interval with its index
        comp.pb(l - 1); // to account for "gaps" -> Turn off the TV.
        comp.pb(l);
        comp.pb(r);
    }
 
    // Coordinate compression
    sort(all(comp));
    comp.rs(unique(all(comp)) - comp.begin());
    
 
    auto getIdx = [&](int x){
        return lb(all(comp), x) - comp.begin() + 1; // +1 for Fenwick Tree 1-based indexing
    };
 
    // Here is where it gets different.
    vi result(n);
 
    // Compress the intervals' coordinates
    // Why? so it fits within n when we add it to result.
    for (int i = 0; i < n; i++){
        intervals[i].F.F = getIdx(intervals[i].F.F); // left endpoint
        intervals[i].F.S = getIdx(intervals[i].F.S); // right endpoint
    }
 
    // Sort intervals by their right endpoint, then left endpoint
    sort(all(intervals), [](const pair<pii, int> &a, const pair<pii, int> &b) {
        if (a.F.S == b.F.S) return a.F.F > b.F.F; // sort by descending
        return a.F.S < b.F.S; // sort by ascending
    });
    // eg. [(2, 5), (1, 5), (3, 7), (4, 7), (1, 3)]
    // becomes [(1, 3), (2, 5), (1, 5), (4, 7), (3, 7)]

    for (int i = 0; i < n; i++){
        int l = intervals[i].F.F;
        int r = intervals[i].F.S;
        // like prefix sums, we do query(r) - query(l-1) to account
        // for the fact that we are including l itself since its [l,r] not
        // (l,r]
        result[intervals[i].S] = query(r) - query(l-1); // Count nested intervals
        update(l, 1, sz(comp)); // Add current interval's left endpoint
        // Why add left point?
        // Because it acts as the starting point for each interval
        // and because we sorted the intervals
        // we know our right end points are always monotonic increasing.
        // => any interval before the current ith interval, if it has a larger
        // left point than the current ith interval left point
        // => its inside the current ith interval.
        // And if they have the same right endpoint, 
        // then we sort by descending order of left endpoint
        // Why? Take: [(2,5), (1,5)]
        // sorted by ascending order of right endpoint, descending order of 
        // left endpoint.
        // if we add l only, so 2 is added to the fenwick.
        // then at (1,5), again because of the monotonic increasing property
        // of the intervals because of how we sorted it, we know we just need
        // to look at the left endpoint, and since we know that 2 > 1.
        // we are able to include it in the interval count for this interval.
    }
 
    for (int i = 0; i < n; i++) cout << result[i] << '\n';
 
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