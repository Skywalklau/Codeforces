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
const int MAXN = 1e5+5; // fenwick = N, trie  = N * number of bits

// solve time ~ can't solve.
// Tough one, which was expected since this is a 2000 rated problem.
// The hardest part is figuring out the dp state for me because once I knew
// what to dp, I could do everything else.
// This problem has a very interesting dp state. Personally, I knew it was
// a 2D dp problem, but I just couldn't figure out what the other state was.
// dp[u][0] = No. of ways to make component u as completely white with it's 
// subtrees having exactly one black node 
// dp[u][1] = No. of ways to make component u as exactly one black with it's 
// subtrees having exactly one black node 
// This is so genius, because now we can solve the problem with this state.

// Let W = dp[curNode][0], B = dp[curNode][1].
// We have 2 cases:
// Case 1: include child component
// dp[curNode][0] = (W * dp[nextNode][0]) % MOD;
// dp[curNode][1] = (B * dp[nextNode][0] + W * dp[nextNode][1]) % MOD;
// For dp[curNode][0] to be a white component. If we want to include the
// child component we must pair it with the white component of the child.
// Similarly, for dp[curNode][0] to be exactly 1 black component. If we want to
// include the child component we must pair it with either:
// 1. The black component of the child if curNode is white
// or 
// 2. The white component of the child if curNode is black
// dp[curNode][1] = (B * dp[nextNode][0] + W * dp[nextNode][1]) % MOD;
// generalizes the case because one of them will be 0 (since its impossible
// for curNode is be both black and white)

// Case 2: don't include child component
// dp[curNode][0] += (W * dp[nextNode][1]) % MOD;
// dp[curNode][1] += (B * dp[nextNode][1]) % MOD;
// For dp[curNode][0] to be a white component. If we don't want to include the
// child component we must pair it with the black component of the child.
// Similarly, for dp[curNode][1] to be exactly 1 black component. If we don't
// want to include the child component we must pair it with the black component
// of the child.

// https://abitofcs.blogspot.com/2014/12/dynamic-programming-on-tree-forming-up.html

// Time complexity: O(N)
// Space complexity: O(2*N)

int col[MAXN]; 
ll dp[MAXN][2];

void dfs(int curNode, int parentNode, vvi& adjList){
    dp[curNode][0] = 1-col[curNode]; // white
    dp[curNode][1] = col[curNode]; // black

    for (int nextNode : adjList[curNode]){
        if (nextNode != parentNode){
            dfs(nextNode, curNode, adjList);

            ll W = dp[curNode][0], B = dp[curNode][1];
            
            // Case 1: include child component
            dp[curNode][0] = (W * dp[nextNode][0]) % MOD;
            dp[curNode][1] = (B * dp[nextNode][0] + W * dp[nextNode][1]) % MOD;
            // Case 2: don't include child component
            dp[curNode][0] += (W * dp[nextNode][1]) % MOD;
            dp[curNode][1] += (B * dp[nextNode][1]) % MOD;
            
        }
    }

}


void solve() {
	int n, k, m;
    cin >> n;

    vvi adjList(n);
    for (int i=0; i<n-1; i++){
        int node;
        cin >> node;
        adjList[node].pb(i+1);
        adjList[i+1].pb(node);
    }

    for (int i=0; i<n; i++) cin >> col[i];

    dfs(0, -1, adjList);

    cout << dp[0][1] % MOD << '\n';

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
