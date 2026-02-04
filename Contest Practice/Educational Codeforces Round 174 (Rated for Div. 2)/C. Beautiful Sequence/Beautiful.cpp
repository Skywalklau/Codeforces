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
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits

// solve time ~ 1hr 10 mins
// tbh, I could've done better.
// Pro tip: when thinking in terms of subsequence, think dp as a potential
// approach.
// I had many intution/ideas for this one, but none of them worked, until
// I thought, lets try dp, and then it worked!
// Initially, I thought fenwick, but it does not work, because order matters
// if a 2 exists before a 1, our fenwick still return the cnt of that 2.
// Then I thought maybe monotonic stacks, does not work as well, because
// we can't track all the subseq effectively.
// At this point, I was kinda out of ideas, then I thought, why no dp?
// And it worked.
// Intuition of dp states: Very similar to a lot of subseq style dp state
// dp[i][j], where i is the index, j is the current element so far.
// So here is my approach:
// let dp[i][j] = min number of ways to form a valid subseq. so far with
// j being the latest number, and at the ith index.
// base case:
// dp[1][a[i]] = a[i] == 1 ? 1 : 0
// because we must start a subseq with 1 first.
// Why? Notice that a subseq in this problem must always be in the form
// [1,2,2,2...,3]
// it starts with 1, has at least one 2, and ends with 3.
// So, every time we ecounter a new 1, we can set this a new subseq with this
// 1.
// Transition:
// if (a[i] == 1) dp[i][1] += dp[i-1][1] + 1;
// if (a[i] == 2) dp[i][2] += dp[i-1][2] + dp[i-1][2] + dp[i-1][1];
// if (a[i] == 3) dp[i][3] += dp[i-1][2];
// a[i] == 1, there is a new starting point, so +1, along with all the prior
// starting points so far.
// a[i] == 2, there are 2 ways, we can choose to include this 2, or not.
// include: dp[i-1][1] + dp[i-1][2]
// dont include: dp[i-1][2]
// so total is 2*(dp[i-1][2]) + dp[i-1][1]
// a[i] == 3, there is a new end point, so just + dp[i-1][2], we build
// from all the subseq. with 2 as the previous element so far.

// In the end, we just return dp[n][3].

void solve() {
	int n, k, m;
    cin >> n;

    vi a(n+1);
    for (int i=1; i<=n; i++) cin >> a[i];

    vvll dp(n+1, vll(4, 0));
    dp[1][1] = a[1] == 1 ? 1 : 0;
    for (int i=2; i<=n; i++){
        // handle dont include case, or just transfer states basically:
        for (int j=1; j<=3; j++) dp[i][j] = dp[i-1][j]; 
        // include case:
        if (a[i] == 1){
            dp[i][1] = (dp[i][1] + 1) % MOD2;
        }
        else if (a[i] == 2){
            dp[i][2] = ((dp[i][2] + dp[i-1][1]) % MOD2 + dp[i-1][2]) % MOD2;
        }
        else{
            dp[i][3] = (dp[i][3] + dp[i-1][2]) % MOD2;
        }
    }
    
    cout << dp[n][3] << '\n';

}

int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    int t;
    cin >> t;
    while (t--) solve();
    // solve();
    return 0;
}
