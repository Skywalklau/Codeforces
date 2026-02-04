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
using vvpii = vector<vector<pair<int, int>>>;
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

const int LOGN = 20; // sparse table interval
const int MAXN = 2e5+5; // fenwick = N, trie  = N * number of bits

// tough problem, couldn't solve it.
// I knew it was fenwick, but the way I tried using the fenwick just couldn't
// help me solve the problem.
// Mistake: I went from left to right via x-coordinate, down to up via
// y-coordinate, which made things very difficult.
// Actually, we are supposed to go from up to down, left to right.
// This is the way to solve it.
// Note to self: if looking from a certain perspective doesn't help, try
// looking the problem from a different starting point, ie. like this problem, 
// or dp problems where u start loop from n-1 to 0 instead of 0 to n-1.
// Overall, great problem, and it was a good reminder to look via different
// starting points.

int fen[MAXN];
bool added[MAXN];

void update(int i, int val, int n){
    if (added[i]) return; // I figured out we needed this as well.
    added[i] = 1;
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

    vpii coords(n);
    vi zx(n), zy(n);

    for (int i=0; i<n;i++){
        int x, y;
        cin >> x >> y;
        coords[i] = {x,y}; 
        zx[i] = x;
        zy[i] = y;
    }

    // Coordinate Compression, I knew we needed this as well.
    sort(all(zx));
    zx.rs(unique(all(zx)) - zx.begin());
    sort(all(zy));
    zy.rs(unique(all(zy)) - zy.begin());

    auto getIdx = [&](int x, vi& nums){
        return lb(all(nums), x) - nums.begin() + 1; // +1 for Fenwick Tree 1-based indexing
    };

    vvi a(n+1);
    // Map original (x, y) to compressed coordinates
    for (int i=0; i<n; i++){
        int xx = getIdx(coords[i].F, zx);
        int yy = getIdx(coords[i].S, zy);
        // yy >= 1.
        a[yy].pb(xx);  // Store compressed x-coordinate for each y-level
    }


    // This is where my mistake is made.
    // We should go from up to down, then left to right
    // not left to right, then down to up.
    ll ans = 0;
    // Note: we start from sz(zy) because fenwick is 1-indexed
    for (int i=sz(zy); i>0; i--){
        sort(all(a[i]));  // Sort x-coordinates for current y
        for (int j : a[i]) update(j, 1, n); // Add x-coordinates to Fenwick Tree
        // printVector(a[i]);
        // Count valid (xL, xR) pairs
        for (int j=0; j<sz(a[i]); j++){
            int now = a[i][j];  
            int nxt = (j+1 < sz(a[i]) ? a[i][j+1] : n+1);
            int l = query(now);  // Count x-values <= now
            int r = query(nxt-1) - query(now-1);  // Count x-values in range [now, nxt)
            // cout << l << " " << r << endl;
            ans += (ll) l * r;  // Number of ways to pick (xL, xR)
        }
     }
     cout << ans << '\n';
    
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
