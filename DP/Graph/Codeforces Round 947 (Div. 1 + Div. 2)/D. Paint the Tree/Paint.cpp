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
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits

// solve time ~ 1hr
// Nice problem, seems complex at first but the goal is to just 
// get to the first blue node ASAP, then go through all nodes
// which is 2*(n-1) - d moves, where d is the longest dist
// from the first blue node.
// so the total moves needed is : 2*(n-1) - d + k, where k is the
// shortest distance for Pb to reach to a red node
// => Pa and Pb must meet each other first if they are not together.
// Then, when Pb makes a node blue, Pa can either be:
// 1. inside Pb
// 2. one move ahead of Pb
// in both cases, every node after this will always be coloured blue
// because Pa can move first, colouring any node red, then Pb
// moves next to colour it blue.
// Proof for point 2:
// lets say we know an optimal move for Pb to move next, since in 
// one turn Pb can only move to its neighboring nodes after meeting
// a red node, making it blue, Pa can just move to that optimal
// node first so that in the next subsequent move, Pb can move there.
// In other words, Pa is always one step ahead of Pb so we can always
// colour any node blue because we can just move Pa to that node first.

int intersectionNode;

void dfs1(int curNode, int parentNode, vi& dist, vvi& adjList){
    for (int nextNode : adjList[curNode]){
        if (nextNode != parentNode){
            dist[nextNode] = dist[curNode] + 1;
            dfs1(nextNode, curNode, dist, adjList);
        }
    }
}

void dfs2(int curNode, int parentNode, vi& dist, vi& distA, vi& distB, vvi& adjList){
    if (intersectionNode == -1 && distA[curNode] <= distB[curNode]){
        // distA[curNode] <= distB[curNode] is a necessary condition
        // because a must reach curNode first, then only b can colour
        // it blue.
        intersectionNode = curNode;
    }
    else if (dist[curNode] < dist[intersectionNode] && distA[curNode] <= distB[curNode]){
        // if we found a better move.
        intersectionNode = curNode;
    }

    for (int nextNode : adjList[curNode]){
        if (nextNode != parentNode){
            dfs2(nextNode, curNode, dist, distA, distB, adjList);
        }
    }
}

void solve() {
	int n, k, m, a, b;
    cin >> n;
    cin >> a >> b;

    vvi adjList(n+1);
    for (int i=0; i<n-1; i++){
        int node1, node2;
        cin >> node1 >> node2;
        adjList[node1].pb(node2);
        adjList[node2].pb(node1);
    }

    vi distA(n+1, 0); // dist of a to all other nodes
    vi distB(n+1, 0); // dist of b to all other nodes
    vi dist2(n+1, 0); // distA + distB
    vi dist3(n+1, 0); // dist of the first blue node to all other nodes

    dfs1(a, -1, distA, adjList);
    dfs1(b, -1, distB, adjList);

    for (int i=1; i<=n; i++) dist2[i] = distA[i] + distB[i];

    // ans is just 2*(n-1) - d + dist for Pb to reach a red node
    
    intersectionNode = -1;
    // note: we must expand from b.
    // proof by contradiction: we expand from a instead
    // a <-> x1 <-> x2 <-> x3 <-> b. We know the answer is x2.
    // we expand from a, then we would pick x1 first, and then not
    // pick x2 because dist[x2] == dist[x1] (check dfs2).
    // So we need to expand from b first to actually get x2.
    // Because again, we want to get the FIRST blue node ASAP.
    dfs2(b, -1, dist2, distA, distB, adjList);

    // find the longest dist to intersectionNode
    dfs1(intersectionNode, -1, dist3, adjList);

    int d = 0;
    for (int i=1; i<=n; i++) d = max(d, dist3[i]);
    
    cout << 2*(n-1) - d + distB[intersectionNode] << '\n';

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
