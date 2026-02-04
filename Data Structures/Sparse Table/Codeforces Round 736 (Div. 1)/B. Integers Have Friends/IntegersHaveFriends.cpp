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


// I solved this problem!
// for consecutive elements to have the same remainder
// a[i] = p * m + r
// a[i+1] = k * m + r
// so | a[i+1] - a[i] | = m * |p - k|
// then we can do the same thing for a[i+1], a[i+2]
// | a[i+2] - a[i+1] | = t * |u - p|
// then for 3 consecutive elements to have the same multiple such that they have the
// same remainder
// => they must share a common divisor such that  | a[i+1] - a[i] | = m * |p - k|
// | a[i+2] - a[i+1] | = t * |u - p| hold true
// => we can take the gcd of their differences.
// and since we want to query the ranges, we can use a sparse table
// segment tree works too
// sparse table:
// we build the sparse table via their differences and take their gcd.
// main code:
// we use sliding window, maybe binary search works as well, but I used sliding window
// 2 pointers, we check the largest subarray that can form from the leftmost idx to
// some idx i until the gcd < 2.
// if the gcd at idx i is < 2, then move the left pointer until the gcd >= 2 again
// sliding window works because of the property of gcd:
// gcd(x, y) >= gcd(x, y, z) >= gcd(x, y, z, k)
// hence as we introduce more elements into the gcd, it will only ever stay the same,
// or decrease. 


const int LOGN = 20;

void solve() {
	int n, k, m;
    cin >> n;
    
    vll a(n);
    for (auto&x : a) cin >> x;

    vll b;
    for (int i=1; i<n; i++) b.pb(abs(a[i] - a[i-1]));

    vvll sparse(LOGN, vll(sz(b)));
    for (int i=0; i<sz(b); i++){
        sparse[0][i] = b[i];
    }

    for (int i=1; i<LOGN; i++){
        for (int j=0; j + (1<<i) <= sz(b); j++){
            sparse[i][j] = __gcd(sparse[i-1][j] , sparse[i-1][j + (1<<(i-1))]);
        }
    }

    auto query = [&](int l, int r){
        int k = 31 - __builtin_clz(r-l+1);
        return __gcd(sparse[k][l], sparse[k][r - (1<<k) +1]);
    }; 


    int j=0;
    ll ans = 1;
    for (int i=0; i<n; i++){
        while (j < i && query(j, i-1) < 2) j++;
        if (j < i && query(j, i-1) >= 2){
            ans = max(ans, (ll) i-j+1);
        }
    }

    cout << ans << '\n';

}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
