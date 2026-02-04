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

// solve time ~ 14 mins
// I mean, this problem is quite easy for a C.
// What they want is also very straightforward, how to maximize
// the product?
// Well, since we can only swap characters on the same index, then
// the only way we can maximize the product is to make the numbers
// as close as possible.
// Hence, all we need to do is just make the numbers as close as
// possible, this will maximize the product.
// Why does this work?
// We need to make an important observation to explain this.
// When numbers are closer to one another, their product is always
// going to be bigger than numbers that are further apart.
// This is a fact between the product of any 2 numbers
// when we can only swap between their digits of the same index.
// So, they must be as close as possible to maximize their products.
// Now, since we are not allowed to introduce a new digit, but 
// can only swap between digits of the same index, the only way
// we can make them as close as possible is to just swap between
// the numbers when its sensible to do so.
// How? Just track from the most significant digit, which digit
// is bigger will be the number that is bigger.
// Then, from there on we always set the larger digit to the smaller
// number and the smaller digit to the bigger number to make
// them as close as possible.
// As for the proof, look at the editorial. Because I did not
// come up with that shit, my intuition just told me this is how
// to solve it.

void solve() {
	int n, k, m;
    str a;
    str b;
    cin >> a >> b;
    n = sz(a);
    vi x(n), y(n);
    for (int i=0; i<n; i++){
        x[i] = a[i]-'0';
        y[i] = b[i]-'0';
    }

    bool found = false;
    bool xSmall = false;
    str ans1 = "", ans2 = "";
    for (int i=0; i<n; i++){
        if (x[i] != y[i] && !found){
            if (x[i] < y[i]) xSmall = true;
            found = true;
        }
        else if (x[i] != y[i] && found){
            int mx = max(y[i], x[i]);
            int mn = min(y[i], x[i]);
            if (xSmall){
                x[i] = mx;
                y[i] = mn;
            }
            else{
                y[i] = mx;
                x[i] = mn;
                // cout << " ds
            }
        }
        ans1 += char(x[i]+'0');
        ans2 += char(y[i]+'0');
    }
    
    cout << ans1 << '\n';
    cout << ans2 << '\n';

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
