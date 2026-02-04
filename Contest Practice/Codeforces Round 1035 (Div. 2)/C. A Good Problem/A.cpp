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
using vpll = vector<pair<long long, long long>>;
using vvpii = vector<vector<pair<int, int>>>;
using vpstrstr = vector<pair<str, str>>;
using vpvivi = vector<pair<vector<int>,vector<int>>>;
using vvb = vector<vector<bool>>;
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
#define mne min_element

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
    if (x == 1) return false;
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

const ll K = 6e6+5; // change according to your needs
vll mn(K, 0); // Smallest prime factor of each number
vvll fcv(K); // Prime factorization for each number (only returns each distinct factor once)


void precompute_prime_factors() { // Modified Sieve
    mn[1] = 1; // Base case: 1 has no prime factors
    for (ll i = 2; i < K; i++) {
        if (!mn[i]) { // If i has no prime factor recorded yet, it is a prime number.
            for (ll j = 1; j * i < K; ++j) {
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

void sieve() {
    mn[1] = 1; // 1 is not prime
    for (ll i = 2; i < K; i++) {
        if (mn[i] == 0) { // i is prime
            mn[i] = i;
            for (ll j = i * i; j < K; j += i) {
                if (mn[j] == 0) {
                    mn[j] = i; // smallest prime factor of j
                }
            }
        }
    }
}

vi get_primes_up_to_K() {
    vi primes;
    for (ll i = 2; i < K; i++) {
        if (mn[i] == i) primes.pb(i);
    }
    return primes;
}

// get all factors up to n
vvi factors(K);

void getAllFactors(){
    for (int i = 1; i <= K; i++) {
        for (int j = i; j <= K; j += i) {
            factors[j].push_back(i); // i is a divisor of j
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

// solve time ~ 1hr 15 mins, not good.
// Took a while, honestly kinda frustrating cuz I had to look into 
// editorial to see if I'm going in the right direction.
// Turns out I am.
// We need to make some observations.  
// First, notice that if n is odd, its very simple. Because
// we can just set everything to l, and the conditions are satisfied.
// So, just take l for everything as AND of an odd number of l is 
// the same as XOR of an odd number of l.
// Now for the case when n is even.
// If n is even, we defo cannot do the same strat anymore because
// now the XOR part is going to be 0 if we take all n.
// So, lets try to change a[n]
// What do we need?
// the condition is l & a[n] = l ^ a[n].
// Why? Because we try to take all a[1] to a[n-1] as l, then so 
// their AND and XOR are both l.
// But, notice that this will not work if we did l & a[n] = l ^ a[n].
// Why? Because at any point in the bit, if l == 1, then we have
// a contradiction, if a[n] == 1, then the AND part will be 1, but the
// XOR part will be 0.
// Likewise, if a[n] == 0, the AND part will be 0, the XOR part will be 
// 1.
// So, we can never satisfy the condition.
// But can we try to take a[n-1] and a[n]?
// Yes. So now the condition becomes l & a[n-1] & a[n] = 0 ^ a[n-1] ^ a[n]
// which is l & a[n-1] & a[n] = a[n-1] & a[n]
// Because an even number of l makes XOR 0, but AND as 1.
// So, is there a way to satisy the eqn?
// Yes,
// at some bit,
// if l == 1, a[n-1] = a[n] = 0
// if l == 0, a[n-1] = a[n] = 1 || a[n-1] = a[n] = 0.
// This way we can always satify our condition.
// So, now our goal is to minimize a[n-1] = a[n].
// How?
// Notice that, if the bit of l is 1, it a[n] must be 0.
// So, immediately notice that only for off bits in l, we can change
// the bits of a[n].
// But, we wanna minimize this a[n], while still satisfying l<=a[n]<=r
// So, what does this mean?
// If we want a[n] >= l, but we cannot make a[n] == 1 when l == 1 at
// some bit position, then the next best number we can make
// is just a[n] = 1 << (m+1), where m is the MSB position of l.
// this way, we greedily minimize our a[n], while still being >= l.
// Of course, now we just need to check if a[n] <= r.
// If yes, then its possible. So, a[n-1] = a[n] = 1 << (m+1).
// And for all other elements, its l.
// There is an edge case tho, if n == 2, then the answer can only
// be [0,0] , but since l >= 1, then n == 2 is always impossible.
// Why only [0,0]?
// Because think truth tables, x & y == x ^ y is only true iff x==y==0
// at every bit position.

void solve() {
	ll n, m, l, r, k;
    cin >> n >> l >> r >> k;

    if (n % 2 == 1) cout << l << '\n';
    else{
        m = 63 - __builtin_clzll(l);
        if (1ll << (m+1) > r) cout << -1 << '\n';
        else{
            if (n == 2) cout << -1 << '\n';
            else if (k <= n-2) cout << l << '\n';
            else cout << (1ll << (m+1)) << '\n';
        }
    }

}

int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    // sieve();
    // precompute_prime_factors(); // modified sieve
    int t;
    cin >> t;
    while (t--) solve();
    // solve();
    return 0;
}
