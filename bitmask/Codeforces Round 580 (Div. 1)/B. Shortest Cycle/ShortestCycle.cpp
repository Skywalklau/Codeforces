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

// This is a good problem, I learned Floyd-Warshall and how to use the pigeonhole principle
// the pigeonhole principle states that if n items are put into m containers, 
// with n > m, then at least one container must contain more than one item.
// If there are n = 10 pigeons in m = 9 holes. Since 10 is greater than 9, the pigeonhole 
// principle says that at least one hole has more than one pigeon.
// We can apply that idea here, since we know that the maximum number is 10^18
// this means it can be represented by a minimum of 60 bits since 2^60 > 10^18
// knowing this, we can think about the pigeonhole principle, the hole is now each 
// bit position, so m = 60.
// Key Observation: if any bit position has more than 3 numbers, it is a cycle of 3.
// (which is also the minimum)
// knowing this, what is the minimum number of numbers where we can fill the 
// bit positions to form a cycle, which is of size 3?
// the answer is 121.
// Why? We need to think greedily, the only way without guaranteeing 
// (a cycle may still form if n<=120, but not guaranteed)
// to form a cycle is by having numbers that fill each unique bit position.
// that is having numbers 1 2 4 8 ... 2^59 each filling bit positions 0 1 2 ... 59
// in one iteration, we can fill 60 numbers at best (assuming each number satisfies our
// condition)
// We can apply the same thing again, now we will fill 120 numbers at each bit position
// twice, this ensures that we might not form a cycle.
// However, on the 121st number, we definitely will fill at least one bit position
// with 3 numbers, therefore guarateeing that we form a cycle of 3.
// considering this, we need to handle an edge case, if the number is 0, since it does not
// fill in any bit slots => we need to ignore it and not count it to our total numbers.

// now, if we have <= 120 numbers, there may or may not be a cycle.
// We don't know intuitively, but this is where we can utilize floyd-warshall
// to find the shortest cycle.
// since <= 120 is sufficiently small enough to run in n^3 complexity.
// In your typical floyd-warshall, we would set dp[i][j] = 0 for i == j
// to indicate that the distance to itself it 0 (obviously) then build from there.
// In this variant, we can use floyd-warshall to find the cycle by fist setting all
// pairs of nodes to 1, dp[i][j] = 1 where i != j 
// we essentially modify to ans = min(ans, dp[i][j] + d[i][k] + d[k][j]);
// since its a cycle, d[i][k] + d[k][j] will be 2 iff there is an edge from i to k and 
// from k to j, if there is, then the distance is a constant, which is 2.
// dp[i][j] will be the current shortest path up until this point.
// To visualize this variant of floyd-warshall, its essentially checking if to 
// nodes from i to k, then k to j exists first, if it exists, then obviously the distance
// will be 2
// then now we just need to check the distance between i to j to complete a cycle,
// if it doesnt exists then its INF, otherwise its some value.

void solve() {
    int n;
    cin >> n;

    vll a;
    for (int i = 0; i < n; i++){
        ll x;
        cin >> x;
        if (x == 0) n--, i--;
        else a.pb(x);
    }

    n = sz(a);

    if (n >= 121) { // If more than 120 numbers, a cycle of length 3 is guaranteed
        cout << "3\n";
        return;
    }

    vvll s(n, vll(n, 1e9)); // Adjacency matrix
    vvll d(n, vll(n, 1e9)); // Distance matrix

    // Build the adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] & a[j]) {
                s[i][j] = s[j][i] = 1;
            }
        }
    }

    d = s; // Copy adjacency matrix to distance matrix

    ll ans = 1e9;

    // Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && j != k && k != i) {
                    ans = min(ans, s[i][j] + d[i][k] + d[k][j]);
                    s[i][j] = min(s[i][j], s[i][k] + s[k][j]);
                }
            }
        }
    }

    cout << (ans == 1e9 ? -1 : ans) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}