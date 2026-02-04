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

// solve time ~ longer than expected...
// Observation 1:
// if the whole array is non zero, we can just use 1 move from 1 to n.
// Observation 2:
// if the whole array is zero, we need 3 moves:
// 1 to n-2, make it to 1.
// 2 to 3, make it to 1.
// 1 to 2, make it to 1.
// Observation 3:
// the zero lies in the last 2 or first 2 elements ONLY.
// we can always make the array into [x,0,0] || [x,1,2] || [x,1,0] || [x,0,1]
// 1 and 2 is arbitrary, it can be any non-zero number.
// x is a non-zero number.
// for x to be non-zero, we must make sure that everything before making
// x MUST have a zero, then we can make a non-zero element
// This can happen either on the left from 1 to n-2, or from the right
// from 3 to n.
// Once we have x, we check the last 2 elements:
// Case 1: all zero
// 2 more moves, make the 2 zero into 1, then finally make the whole array
// 0.
// Case 2: all non-zero
// 1 more move, make the whole array into 0.
// Case 3: 1 zero and 1 non-zero.
// 2 more moves, make the non-zero element and zero element into a non-zero
// element.
// Then finally the whole array into 1 zero element.

void solve() {
	int n, k, m;
    cin >> n;

    vi a(n);
    int zeroCount = 0;
    for (int& x: a){
        cin >> x;
        if (x == 0) zeroCount++;
    }

    if (zeroCount == 0){
        cout << 1 << '\n';
        cout << 1 << " " << n << '\n';
        return;
    }
    
    if (zeroCount == n){
        cout << 3 << '\n';
        cout << 1 << " " << n-2 << '\n';
        cout << 2 << " " << 3 << '\n';
        cout << 1 << " " << 2 << '\n';
        return;
    }

    bool hasZeroLeft = false;
    for (int i=0; i<n-2; i++){
        if (a[i] == 0) {hasZeroLeft = true; break;}
    }

    if (hasZeroLeft == false){ // we know its on the right
        if (a[0] != 0 && a[1] != 0){
            cout << 2 << '\n';
            cout << 3 << " " << n << '\n';
            cout << 1 << " " << 3 << '\n';
        }
        else{
            cout << 3 << '\n';
            cout << 3 << " " << n << '\n';
            cout << 1 << " " << 2 << '\n';
            cout << 1 << " " << 2 << '\n';
        }
    }
    else{
        if (a[n-2] != 0 && a[n-1] != 0){
            cout << 2 << '\n';
            cout << 1 << " " << n-2 << '\n';
            cout << 1 << " " << 3 << '\n';
        }
        else{
            cout << 3 << '\n';
            cout << 1 << " " << n-2 << '\n';
            cout << 2 << " " << 3 << '\n';
            cout << 1 << " " << 2 << '\n';
        }
    }

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
