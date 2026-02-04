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

// solve time ~ can't solve.
// Wow I did not know I can even do this in the first place.
// dfs/bfs never even crossed my mind.
// I was thinking dp somehow in NlogN, maybe with bs.
// Because there could be a scenario where there are multiple
// choices we can pick from, but we don't know which one is better.
// like [4,3,2,1]
// all of them are valid, but which do we choose? 
// Thats what I thought.
// But the issue is that we don't know how to check if each element is ok.
// [6, 8, 2, 3]
// the thing with this is that we pick a[4] first, then a[4].
// This means my dp could be O(n^2), which is too slow.
// So I thought maybe bs?
// but then I wouldn't know how to use it here...
// Turns out its a graph problem. Wow.
// Actually, we can rearrange the eqn from:
// a[i] = sz(a) + 1 - i
// to 
// sz(a) = a[i] + i - 1
// then we can set this eqn to u
// which transitions to u + i - 1 (because we add i-1)
// call it v.
// then we can just add a directed edge from u to v.
// In the end, we can just call dfs(n), we dfs starting on n (because this
// is the first starting condition as stated in the problem).
// and we get traverse through all the nodes and finally get the largest-valued
// node to be our answer (because that is the biggest array we can form).
// You might ask? But don't we need to dynamically track the new size of the 
// array when creating the relationships?
// No. Because we are already doing it.
// when I say sz(a) = a[i] + i - 1, it means that:
// there exists a node of this new size sz(a).
// and the new array it will form will be sz(a) + i - 1.
// eg.
// lets say a[i]=2, i=2, and a[j]=2, j=3.
// then we have a node of size 3 (because 2 + 2 - 1 == 3), call it u.
// the new size it will create will be 3 + 2 - 1 == 4, call it v
// then we have another node that is of size 4 (because 2 + 3 - 1 == 4), call it
// u2, call it v2.
// then the new size it will create will be 4 + 3 - 1 == 6.
// hence the relationship u -> v == u2 -> v2.
// and we return the largest element of our visited set, which is v2 == 6.
// And that is our answer.
// of course, we dfs with start node of size n, because that is the requirement
// to branch to a bigger size initially.

void solve() {
	int n, k, m;
    cin >> n;

    vll a(n+1);
    for (int i=1; i<=n; i++) cin >> a[i];

    map<ll, vll> adjList; // nodes are sparse, so we need a map
    for (int i=1; i<=n; i++){
        ll u = a[i] + i - 1;
        ll v = u + i - 1;
        adjList[u].pb(v);
    }

    set<ll> vis; // sparse so we use a set instead of array
    function<void(ll)> dfs = [&](ll u) -> void {
        if (vis.count(u)) return;
        vis.insert(u);
        for (ll v : adjList[u]) dfs(v);
    };

    dfs(n);
    cout << *vis.rbegin() << '\n'; // return the maximum node.

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
