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


// This is a very good problem
// We are given that we need to find F(A), which is the summation of all S(t) until 
// S(t) == 0 for some t for all 2^n configurations of the tree.
// We first have to think of this problem as a combinations problem for sure
// since there is no way we can brute force dfs/bfs for the solution
// One crucial observation to notice, which might seem obvious, but I totally 
// neglected, was that at every iteration of t, the total number of configurations 
// of the trees is still 2^n
// at t=0,1,2,3,4... we still are dealing with 2^n unique trees created from the start
// which is t=0.
// Why I could not solve this problem: I neglected 2^(n-1) trees right from the beginning
// basically, at every iteration, my total combinations kept decreasing by half, which
// is obviously wrong.
// Solution to the problem once this observation is noticed is quite obvious, and I could
// figure out how to solve it after that.
// Solution:
// At every increment of t, the lowest level will be set to all 0
// t=1, all leaves = 0
// t=2, all parents = 0
// t=3, all grandparents = 0
// At t=0, we need to look at all the nodes
// The question now becomes, how many ways out of the 2^n configurations can we find 
// a 1 in this particular node?
// The answer is 2^(n-1), because for this node to have 1 or 0 is a 50% chance.
// So, at t=0, the answer is summation of S[2^n](0) = n * 2^n, where S[2^n](t) is the 
// summation of all 1's for all 2^n configurations at time t.
// Now, at t=1, we know all leaf nodes are 0, so we can simply ignore them as they
// will never contribute to S[2^n](1).
// for the rest of the nodes, we do the same thing again.
// how many ways out of the 2^n configurations can we find a 1 in this particular node?
// This will be S[2^n](1) = (n-k) * 2^n, where k is the number of leaf nodes.
// We keep repeating this process until S[2^n](t) == 0 for some t.
// Knowing this, we can do dfs/bfs.
// At every depth, it contributes some amount of times.
// at leaf nodes -> 1 time
// parent nodes -> 2 time
// grandparent nodes -> 3 time
// and so on
// so we can make a depth array, leaf nodes will have depth of 1, parents depth of 2
// grandparents depth of 3 and so on...
// for each node we find we can then just multiply the depth with 2^(n-1).

// Time complexity: O(V+E)
// Spacce complexity: O(N)

int dfs(int curNode, int parentNode, int curDepth, vvi& adjList, vi& depth){
    int maxDepth = curDepth;
    for (int nextNode : adjList[curNode]){
        if (nextNode != parentNode) {
            maxDepth = max(dfs(nextNode, curNode, curDepth + 1, adjList, depth), maxDepth);
        }
    }

    depth[curNode] = maxDepth - curDepth + 1;
    return maxDepth;
}

void solve() {
    int n;
    cin >> n;

    if (n == 1){
        cout << "1\n"; // Handle single-node case
        return;
    }

    vvi adjList(n);
    for (int i = 0; i < n - 1; i++){
        int node1, node2;
        cin >> node1 >> node2;
        --node1, --node2;
        adjList[node1].push_back(node2);
        adjList[node2].push_back(node1);
    }

    vi depth(n, 0);
    dfs(0, -1, 0, adjList, depth);

    ll p = mod_exp(2, n - 1, MOD), ans = 0;
    for (int i = 0; i < n; i++){
        ans = (ans + (p * depth[i]) % MOD) % MOD;
    }

    cout << ans << "\n";
}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
