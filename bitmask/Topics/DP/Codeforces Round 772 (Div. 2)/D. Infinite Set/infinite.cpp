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
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits

// solve time ~ can't solve
// Holy shit this was an amazing problem. Absolute cinema of a problem.
// first and foremost, we need to identify this problem in terms of bits
// because p is huge (I identified this).
// Next, notice that 2y+1 and 4y operations means: 
// 2y+1: shift left by 1, then add 1 (adding one 1)
// 4y: shift left by 2 (adding two 0's)

// Notice that there can be overlaps between different a[i]'s.
// if x in a, and x == 1001001, and y in a, and y == 1, p = 1000
// then notice that y can form all combinations from 2y+1 and 4y, and one
// of those combinations will make x.
// because if we backtrack from x: 1001001 => 100100 => 1001 => 100 => 1 == y.
// so if we expand from x, its redundant, because we can expand from y, which
// implicitly expands from x as well covering more combinations.Therefore,
// this avoids overcounting.
// So what we can do is extract useful a[i]'s from a, and expand these useful
// a[i]'s.

// Next thing to identify is that there can be many ways to expand each 
// useful a[i].
// every move we can choose to do 2y+1 and 4y.
// This now becomes a standard dp problem.
// At every length < p (because if >= p then our number is >= 2^p)
// dp[i] = number of ways to generate a number of length i (or i bits)
// then the transition will just be: dp[i] = cnt[i] + dp[i-1] + d[i-2].
// cnt[i]: the total numbers with this length of bits
// dp[i-1]: the total numbers with one less bit (2x+1)
// dp[i-2]: the total number with two less bits (4y)
// for each stage, we can add dp[i] to our ans, and there will be no overcounting
// because every number is distinct (we already extracted overlapping a[i]'s).

// GOATED problem, added to favourites!

// Time complexity: O(nlog(n) + nlog(max(a)) + p)
// Space complexity: O(n + p)

void solve() {
	int n, k, m, p;
    cin >> n >> p;

    vi a(n);
    for (int &x: a) cin >> x;

    sort(all(a));
    set<int> useful;
    for (int i=0; i<n; i++){
        int x = a[i];
        bool flag = false;
        while (x > 0){
            if (useful.count(x)) flag = true;

            if (x & 1) x >>= 1; // 01 || 11 => backtrack 2y+1 operation
            else if (x & 2 && !(x & 1)) break; // 10 => cannot backtrack any operation
            else x >>= 2; // 00 => backtrack 4y operation
        }
        if (!flag) useful.insert(a[i]);
    }

    vi cnt(30, 0), dp(p);
    // init base case: the number of a[i]'s with corresponding bit length i.
    for (int x : useful) cnt[31 - __builtin_clz(x)]++;
    
    int ans = 0;
    for (int i=0; i<p; ++i){
        if (i < 30){ // a[i] <= 10^9 => 30 bits at most (0-29)
            dp[i] = cnt[i];
        }

        if (i >= 1){
            dp[i] = (dp[i] + dp[i-1]) % MOD;
        }

        if (i >= 2){
            dp[i] = (dp[i] + dp[i-2]) % MOD;
        }
        
        ans = (ans + dp[i]) % MOD;
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
