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

// solve time ~ 43 mins. I love dp bitmask + backtracking.
// What a way to celebrate my 200th solve in CF with a classic dp bitmask!
// The first thing to notice is that we can always just use 1 for any b[i]
// because gcd of 1 with anything is 1 => pairwise coprime.
// knowing this, we can make an important conclusion:
// we only need to check for numbers from 1 to 59.
// Why? Because we are doing abs(a[i] - b[i]).
// Since a[i] is at most 30, then we know the min score is at most 29.
// Also, since its abs(a[i] - b[i]), we can also do |30 - 59|= 29
// Because abs is symmetrical about a[i], more specifically,
// we only need to check up from 1 to 2*a[i]-1 for every a[i].
// Now, we know what numbers to check for, but we need them to be pairwise
// coprime.
// pairwise coprime just means no number share the same prime factors
// we know there are 16 primes up to 59.
// so we can build from here via bitmask dp.
// let dp[i][j] = min score so far up to ith element, with j being the 
// bitmask of the primes used up to the ith element so far.
// Base case: dp[0][0] = 0, no processed elements, we dont use any primes.
// Transition:
// for every number k from 1 to 59 (or 2*a[i]-1).
// we get the prime decomposition k and bitmask it.
// then we get the remaining bitmask we can use to build from this.
// then for all subsets of the remaining bitmask, we do:
// if (dp[i-1][s] + abs(a[i] - k) < dp[i][s | msk]){
//    dp[i][s | msk] = dp[i-1][s] + abs(a[i] - k);
//    prev_mask[i][s | msk] = s;
//    chosen[i][s | msk] = k;
//}
// s | msk is the new mask with the bitmask of primes of k.
// we build from dp[i-1][s], where s is the subset of the remaning bitmask
// available after deducting the bitmask of k.
// In the end, we get the bitmask of the min of all(dp[n]).
// then we backtrack via chosen and prev_mask to build b.
// then print b.

// Time complexity: O(2^17 * N * 60)
// Space complexity: O(2^17 * N)

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};

int get_mask(int x){
    int mask = 0;
    for (int i=0; i<17; i++){
        if (x % primes[i] == 0) mask |= (1 << i);
    }
    return mask;
}

void solve() {
    int n, m, k;
    cin >> n;
    vi a(n+1);
    for (int i=1; i<=n; i++) cin >> a[i];

    vi fact(61);
    for (int i=1; i<=60; i++) fact[i] = get_mask(i);

    vvi dp(n+1, vi(1<<17, MAX));
    vvi prev_mask(n+1, vi(1<<17, -1));
    vvi chosen(n+1, vi(1<<17, -1));
    
    // base case: no processed elements and no prime factors used has 
    // cost of 0
    dp[0][0] = 0;
    for (int i=1; i<=n; i++){
        for (int k=1; k<=60; k++){
            int msk = fact[k];
            int inv = ((1 << 17) - 1) ^ msk;  // bits available

            for (int s=inv; ; s = (s - 1) & inv){
                if (dp[i-1][s] + abs(a[i] - k) < dp[i][s | msk]){
                    dp[i][s | msk] = dp[i-1][s] + abs(a[i] - k);
                    prev_mask[i][s | msk] = s;
                    chosen[i][s | msk] = k;
                }
                if (s == 0) break;
            }
        }
    }

    int best = min_element(all(dp[n])) - dp[n].begin();
    // reconstruct solution
    vi b(n+1);
    int cur = best;
    for (int i=n; i>=1; i--){
        b[i] = chosen[i][cur];
        cur = prev_mask[i][cur];
    }

    for (int i=1; i<=n; i++) cout << b[i] << " ";
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
