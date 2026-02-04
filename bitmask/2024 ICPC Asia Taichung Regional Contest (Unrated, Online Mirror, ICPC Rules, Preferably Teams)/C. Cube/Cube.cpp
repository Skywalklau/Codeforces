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


// This is an amazing problem, new type dp knowledge obtained!
// Perhaps the biggest obstacle here is knowing what to dp, which I could not figure out
// But once you know the state, it fairly straightforward to implement.
// Essentially, the problem wants us to pick a number from every z plane,
// then for every z plane, we want to pick a number in the matrix that has coordinate 
// x and y
// then onto the next plane, we are not allowed to pick a number from the same yth row
// and xth column (and also all other rows and columns previously from chosen coordinates)
// we keep repeating until we iterate until the end, where we will end up with n numbers
// we want the min sum of the numbers.

// So, what is the dp state? It is obvious that this is bitmask since n is small.
// typically, we do dp[mask][i] or dp[mask].
// this however, is an example of dp[mask][mask].
// this is not a hamiltonian path problem, nor is it a bipartite graph problem.
// Perhaps I would label this as a 3 dimensional plane type of problem.
// The dp state is dp[maskY][maskZ], where dp[maskY][maskZ] represents the minimum 
// sum of far where certain Y coordinates and Z coordinates have been chosen (and we cannot
// pick them again since its what the problem wants).
// we iterate the subsets of each x plane, updating the maskZ nad maskY each time.
// Another condition, the number of y coordinates chosen must obviously be equal to the 
// number of x and z coordintes chosen so far.
// Why? if we are considering lets say 4 subsets of the x planes, that means we should
// have 4 unique x coordinates points that are chosen so far, same for y, same for z 
// so that we can build on top of it via dp for the 5th coordinate point.
// We can check this via their bit count. If it is not equal, then this is not a 
// valid subset to consider.

void solve() {
    int n;
    cin >> n;

    int a[15][15][15];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            for (int t = 0; t < n; t++){
                cin >> a[i][j][t];
            }
        }
    }

    vvi dp(1 << n, vi(1 << n, 1e9));
    dp[0][0] = 0; // Base case

    for (int maskY = 0; maskY < (1 << n); maskY++) {
        int u = __builtin_popcount(maskY); // Current x-coordinates and y-coordinates chosen
        for (int maskZ = 0; maskZ < (1 << n); maskZ++) {
            if (u != __builtin_popcount(maskZ)) continue; // Only valid states
            if (dp[maskY][maskZ] == 1e9) continue; // Skip invalid states

            for (int y = 0; y < n; y++) {
                if (maskY & (1 << y)) continue; // y already used
                for (int z = 0; z < n; z++) {
                    if (maskZ & (1 << z)) continue; // z already used
                    int newMaskY = maskY | (1 << y);
                    int newMaskZ = maskZ | (1 << z);
                    dp[newMaskY][newMaskZ] = min(dp[newMaskY][newMaskZ], dp[maskY][maskZ] + a[u][y][z]);
                }
            }
        }
    }

    cout << dp[(1 << n) - 1][(1 << n) - 1] << '\n';
}

int main() {
    fast_io();
    // int t;
    // cin >> t;
    // while (t--) solve();
    solve();
    return 0;
}
