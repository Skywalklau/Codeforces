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


// This was a tough dp problem, but I learned something.
// fundamentally, we had to think backwards to solve this problem
// It took me a while to understand such few lines of code
// Let me explain.
// we want Jedi Ivan to win, he is at index 0.
// since n is small, its quite obvious that we had to try all combinations and see which
// "path" is the best for Jedi Ivan to take.
// the dp state here, which I figured out, was the dp[mask][i].
// mask is the state representing who is alive or dead, i is the current winner so far.
// What I struggled was handling the dp transition, it was quite tough to figure out 
// intuitively because we had to think backwards.

// Base Case: dp[1][0] = 1.0
// The base case was confusing, but essentially
// setting dp[1][0] = 1.0 doesn’t mean Ivan always survives; it only means:
// If he is the last one standing, his probability of winning is 100%
// Think of it this way, we are trying to build from the base case where Ivan wins to
// the beginning of the match, at the very beginning, all participants are alive
// and depending on who goes first, this will change Ivan's probability of survival
// hence we want to fill up dp[fullMask][each participant] to see from the path
// that Ivan wins, which one has to greatest probability from the beginning such that 
// Ivan's survival probability is the highest.
// Hence we return max(dp[fullMask][each participant]

// DP transition:
// This is the toughest part, since we are building from the end, we need to think backwards
// Now, when any 2 people are alive currently, lets say i and j, we know that in
// the next match either i or j will die and the mask will update to minus either 
// 2^i or 2^j depending on who wins.
// However, what we want is when any 2 people are alive currently, lets say i and j,
// what was the previous state that make it up to this point?
// lets say mask = 1011, i=0, j=3, i is the current winner so far.
// what is the next state?
// either newMask = 1010, j is the current winner so far
// or newMask = 0011, i is the current winner so far
// Here is where we need to think backwards once we think frontwards.
// since our goal is to build from end to start.
// since mask=1011, i=0, j=3 is a larger state than (1010,j) and (0011,i)
// Our transition would be: 
// dp[mask][i] = max(dp[mask][i], dp[mask-2^i][j] * p[j][i] + dp[mask-2^j][i] * p[i][j])

void solve() {
    int n;
    cin >> n;

    ld p[n][n];

    for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>p[i][j];
		}
	}

    vvld dp(1<<n, vld(n, 0));
	dp[1][0] = 1.0; // if only Jedi Ivan (participant 0) is alive, his survival probability is 100%.
	for (int mask = 1; mask < (1 << n); mask++) {
        for (int j = 0; j < n; j++) {
            if (mask & (1 << j)) { // If person j is alive
                for (int k = 0; k < n; k++) {
                    if ((mask & (1 << k)) && j != k) { // If person k is alive and different from j
                        dp[mask][j] = max(dp[mask][j],
                        dp[mask ^ (1 << j)][k] * p[k][j] + dp[mask ^ (1 << k)][j] * p[j][k]);
                	}	
            	}
        	}
    	}
	}	
	
	cout << fixed << setprecision(12) << *max_element(all(dp[(1<<n)-1])) << '\n';
}

int main() {
    fast_io();
    // int t;
    // cin >> t;
    // while (t--) solve();
    solve();
    return 0;
}
