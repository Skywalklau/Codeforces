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
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits

// solve time ~ 40 mins
// This was a nice problem. Honestly I was really doubting myself
// when I thought of the dp states, because I kept thinking it wouldn't
// work in the transition. But it does.
// Let dp[i][j] = min cost so far after processing i elements, with 
// j being the state of the word "hard"
// j == 0 => "", j == 1 => "h", ... , j == 4 => "hard"
// Base case: dp[0][0] = 0; Because we have not processed any elements
// so far, so the only state is the empty state for j, so dp[0][0] = 0.
// Transition:
// let p = "hard"
// keep if s[i-1] == p[j], else just transfer states
// dp[i][j + (s[i-1] == p[j])] = min(dp[i][j + (s[i-1] == p[j])], dp[i-1][j]); 
// remove
// dp[i][j] = min(dp[i][j], dp[i-1][j] + a[i]);
// Basically, if lets say we are on the state dp[i]["ha"], and 
// s[i-1] == "r", we have 2 choices, keep or remove. 
// We simulate both. So,
// dp[i]["ha"] -> keep -> dp[i]["har"] = min(dp[i]["har"], dp[i-1]["ha"]);
// dp[i]["ha"] -> remove -> dp[i]["ha"] = min(dp[i]["ha"], dp[i-1]["ha"] + a[i]);
// Otherwise, we just transfer states.

// Time complexity: O(4N)
// Space complexity: O(5N)

void solve() {
	int n, k, m;
    cin >> n;
    str s;
    cin >> s;

    vi a(n+1);
    for (int i=1; i<=n; i++) cin >> a[i];
    
    vvll dp(n+1, vll(5, MAXL));
    // dp[i][j] = min cost so far
    // i = num of elements processed so far
    // j = the state of the word "hard"
    // j == 0 => "", j == 1 => "h", ... , j == 4 => "hard"
    // base case: process nothing so far with 0 removal cost 0
    dp[0][0] = 0;
    const str p = "hard";
    for (int i=1; i<=n; i++){
        for (int j=0; j<4; j++){
            if (p[j] == s[i-1]){
                // case 1: keep
                dp[i][j+1] = min(dp[i][j+1], dp[i-1][j]);
                // case 2: remove
                dp[i][j] = min(dp[i][j], dp[i-1][j] + a[i]);
            }
            else{
                // just keep cuz there is no point in removing
                // so just transfer states
                dp[i][j] = min(dp[i][j], dp[i-1][j]);
            }
        }
    }

    // cout << dp[1][1] << endl;
    // cout << dp[1][0] << endl;
    ll ans = MAXL;
    for (int i=0; i<4; i++) ans = min(ans,dp[n][i]);

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
