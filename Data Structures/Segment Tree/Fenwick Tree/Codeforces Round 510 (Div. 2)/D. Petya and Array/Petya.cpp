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

const int LOGN = 20; // sparse table
const int MAXN = 2e5 + 5; // Fenwick tree 

int fen[MAXN];

void update(int i, int val, int n) {
    while (i <= n) {
        fen[i] += val;
        i += i & -i;
    }
}

ll query(int i){
    ll ans = 0;
    while (i > 0) {
        ans += fen[i];
        i -= i & -i;
    }
    return ans;
}

void solve() {
    int n;
    ll t;
    cin >> n >> t;

    vi a(n);
    for (int& x : a) cin >> x;


    vll pref(1, 0LL);
    ll sum = 0;
    for (int i = 0; i < n; i++){
        sum += a[i];
        pref.pb(sum);
    }

    sort(all(pref));
    // printVector(pref);
    pref.rs(unique(all(pref)) -  pref.begin()); // remove duplicates
    
    ll ans = 0;
    sum = 0;
    // Why add 0?
    // to handle the case pref[r] < t
    // => taking the whole subarray from 1 to r (1 indexed) 
    update(lb(all(pref), 0LL) - pref.begin() + 1, 1, MAXN); // 1 based index
    // printVector(pref);
    // we want pref[r] - pref[l-1] < t
    // => pref[l-1] > pref[r] - t;
    // for some l at every r we see
    // to find l we do bs.
    for (int i = 0; i < n; i++){
        sum += a[i];

        // ub because we want pref[l-1] to be stricly greater than pref[r] - t;
        // lb when >=, but since >, we use ub.
        int val = ub(all(pref), sum - t) - pref.begin() + 1; // convert to 1 based
        // then we can query how many prefix sums are < val
        // then we do query(MAXN)- query(val-1)
        // => total segments up to i - invalid segments.
        // query(MAXN) gives the total number of prefix sums so far
        // query(val-1) gives the number of prefix sums <= sum - t
        // Subtracting gives the count of prefix sums > sum - t
        ans += query(MAXN) - query(val-1);
        // cout << ans << " " << query(val-1) << " " << val << '\n';
        
        // we get the idx of this prefix
        int k = lb(all(pref), sum) - pref.begin();
        update(k+1, 1, MAXN);  // Update Fenwick Tree at index k+1 (1-based)
    }

    cout << ans << '\n';
}


// finding segments > t
// we want pref[l-1] < pref[r] - t; 
// lb because we dont want strictly greater than.
// (query(MAXN) - query(val-1)) == total prefixes - (prefixes < val)
// where val == all values < pref[l-1] == all the valid prefixes
// => total prefixes - valid prefixes == invalid prefixes
// (i+1) - invalid prefixes == valid segments including i.

// finding segment > t, use lb
// int val = lb(all(pref), sum - t) - pref.begin() + 1; // convert to 1 based
// ans += query(val - 1); // get all pref[l-1] < sum-t
// query(val - 1) gives the count of prefix sums < sum - t

// finding segment <= t, use lb + reference from MAXN
// int val = lb(all(pref), sum - t) - pref.begin() + 1; // convert to 1 based
// ans += query(MAXN) - query(val-1); // get all pref[l-1] >= sum-t
// query(MAXN): total prefix sums so far
// query(val-1) gives the number of prefix sums < sum - t
// Subtracting gives the count of prefix sums >= sum - t

// finding segment >= t, use lb
// int val = lb(all(pref), sum - t) - pref.begin() + 1;
// ans += query(val); // get all pref[l-1] <= sum-t
// Add current prefix to Fenwick
// int k = lb(all(pref), sum) - pref.begin();
// update(k + 1, 1, MAXN);

// finding segment == t, use lb + reference from val
// Find the exact prefix sum == sum - t
// int val = lb(all(pref), sum - t) - pref.begin() + 1; // convert 1 based
// Check if sum - t exists in the Fenwick Tree
// if (val <= sz(pref) && pref[val - 1] == sum - t){ 
//     ans += query(val) - query(val - 1); // Count occurrences of sum - t
// }
// we do pref[val-1] == sum - t because:
// we want to make sure pref[val-1] actually does have sum-t

int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    // int t;
    // cin >> t;
    // while (t--) solve();
    solve();
    return 0;
}
