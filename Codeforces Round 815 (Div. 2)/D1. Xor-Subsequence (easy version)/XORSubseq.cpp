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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vstr = vector<str>;
using vpvivi = vector<pair<vector<int>,vector<int>>>;

#define mset multiset
#define mmap multimap
#define uset unordered_set
#define umap unordered_map
#define umset unordered_multiset
#define ummap unordered_multimap
#define pqueue priority_queue

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

// The hard part of this problem is understanding the problem.
// essentially we want to find the longest subsequence from a such that
// a[i] ^ j < a[j] ^ i where i and j are the indexes of a and j > i.
// The subsequence, b, is increasing in nature since we are taking indexes.
// Knowing this, we can kinda sense that this is a variant of 
// longest increasing subsequence.
// => dp where dp[i] = longest subsequence such that the condition is fufilled so far
// Another thing to note, 0 <= a[i] <= 200.
// which is at most 7 bits
// so if lets say the index j = 111010101011101
// note that :           a[i] = 00000000xxxxxxx
// where x is either 0 or 1 such that 0 <= a[i] <= 200
// so now since we have a[i] ^ j, what is the biggest value and smallest value?
// max(a[i] ^ j) = xx...x1111111, min(a[i] ^ j) = xx...x0000000
// hence max(a[i] ^ j) = j + 255, min(a[i] ^ j) = j - 255
// Similarly for a[j] ^ i,
// max(a[j] ^ i) = i + 255, min(a[j] ^ i) = i - 255 
// from the question, we want a[i] ^ j < a[j] ^ i
// if we take the most extreme boundaries such that a[i] ^ j < a[j] ^ i
// then j-255 < i+255
// so j - i < 510 is our max limit.
// Knowing this, we can do a dp to find the longest subsequence 
// such that a[i] ^ j < a[j] ^ i, and j - i < 510.

// Time complexity: O(510 * N) == O(N)
// Space complexty : O(N)

void solve() {
	int n, k, m;
    cin >> n;
    
    vi a(n);

    for (auto& x : a) cin >> x;

    vi dp(n, 1); // base case, each element is a valid "longest subseq" intially
    for (int j=0; j<n; j++){
        for (int i=j-1; i>=0 && j-i < 510; i--){
            if ((a[i] ^ j) < (a[j] ^ i)) dp[j] = max(dp[j], dp[i]+1);
        }
    }

    cout << *max_element(all(dp)) << '\n';

}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
