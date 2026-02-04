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
using vvld = vector<vector<ld>>;
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

// solve time ~ 45 mins
// Math problem.
// We need to make some observations.
// Since we are given n-1 numbers of the prefix sum, this tells us some things:
// 1. the gap between 2 numbers in this prefix sum cannot be >= 2*n
// Because in a permutation of size n, the biggest number we have is n, the next biggest
// is n-1, and n + n -1 = 2n-1 < 2n. So, its impossible to get a sum >= 2n.
// 2. the gap between 2 numbers <= n, then its always possible to form this sum, the number
// in the permutation will be a[i] - a[i-1], which is the gap.
// 3. the gap is > n, but < 2n.
// then its still possible, but we need to use 2 numbers from our permutation to form this
// gap.
// From this, we can deduce a couple of things:
// if gap >= 2n, then its impossible, so output NO.
// if gap <= n, then cnt[gap]++
// if gap >n, <2n, then we need to use 2 numbers from permutation, but which 2 numbers?
// Actually, it doesn't matter, we keep track of it first to note that we need 2 numbers for
// this gap.
// then later on if we find that we need to use another 2 more numbers, then its impossible
// already. Why? Because that means we need to spawn 2 numbers instead of 1 to form the 
// original sequence.
// Having a gap > n and < 2n means we need to create the last number in the original seq
// to sanwhich between this gap so that its possible to form this prefix sums, but if 
// we encounter another gap of this type, then we need to spawn another number, but that
// would make n+1 elements, and we only have n elements, hence impossible.
// Another thing, if cnt[gap] == 1 but we encounter the same gap again, then this counts
// as the same thing again where we need to fill a number in between (because its each
// number from 1 to n can only occur once, aka each gap can only occur once).
// In the end, we will end up with an array cnt where:
// 1. one element in cnt is 0
// 2. two elements in cnt is 0
// case 1: immediately is possible, print YES (because we can create the last number at
// the end of the prefix sum)
// case 2: we need to check if the remaining 2 elements can form the gap, ie x + y = gap.
// Otherwise, its impossible.
// if can, then possible.
// thats the solution. 

void solve() {
	ll n, k, m;
    cin >> n;

    vll a(n-1);
    for (ll& x : a) cin >> x;

    vll cnt(n+1);
    ll y = -1;
    if (a[0] <= n) cnt[a[0]]++;
    else if (a[0] >= 2*n) {cout << "NO" << '\n'; return;} 
    else y = a[0];

    for (int i=1; i<n-1; i++){
        ll x = a[i] - a[i-1];
        if (x <= n){
            if (cnt[x] && y == -1) y = x;
            else if (cnt[x] && y != -1) {cout << "NO" << '\n'; return;}// we need another element
            else if (!cnt[x]) cnt[x]++;
        }
        else if (x >= 2*n) {cout << "NO" << '\n'; return;}
        else{
            if (y == -1) y = x;
            else {cout << "NO" << '\n'; return;}
        }
    }

    int p = 0;
    int b = 0, c = 0;
    for (int i=1; i<=n; i++){
        if (!cnt[i]){
            p++;
            if (!b) b = i;
            else if (!c) c = i;
        } 
    }

    if (p == 2 && c + b != y) {cout << "NO" << '\n'; return;}

    cout << (p == 1 || p == 2 ? "YES" : "NO") << '\n';

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