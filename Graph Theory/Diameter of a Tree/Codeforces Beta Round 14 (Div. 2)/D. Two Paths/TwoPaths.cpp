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
const int MAXN = 1e6+5; // fenwick = N, trie  = N * number of bits

// This problem was such a big misunderstanding for me.
// I understood the assignment wrongly.
// I thought they wanted 2 largest disjoint components and multiply by the 
// number of edges of the 2 components as the profit.
// So I found the solution for that, which is the diameter's midpoint
// we split there for maximal profit.
// if its 2 potential edge to cut because diameter is even the we try both
// otherwise just the 1 edge is enough if diameter is odd.
// However, I was wrong.
// What they wanted was the longest path from one point to another point
// in both disjoint components.
// In other words, they wanted the diameter of the 2 disjoint components,
// multiplied together as the profit.
// If so the solution would be to cut every edge, and find the diameter each
// time for both disjoint components and multiply them together to get 
// the profit, and we do this for all edges and get the max profit.


void dfs(int curNode, int parentNode, const vvi &adjList, vi &dist, int h){
    dist[curNode] = h;
    for (int nextNode : adjList[curNode]){
        if (nextNode != parentNode){
            dfs(nextNode, curNode, adjList, dist, h + 1);
        }
    }
}

int findDiameter(int startNode, const vvi &adjList){
    int n = adjList.size();
    vi dist(n, -1); // Initialize distances to -1 (unvisited)

    // First DFS to find the farthest node
    dfs(startNode, -1, adjList, dist, 0);
    int farthestNode = mxe(all(dist)) - dist.begin();

    // Reset distances for the second DFS
    fill(all(dist), -1);

    // Second DFS from the farthest node to find the diameter
    dfs(farthestNode, -1, adjList, dist, 0);
    return *mxe(all(dist));
}

// Syntax of Vector erase()
// Vector erase method has two implementations:

// Remove single element
// v.erase(pos);

// Erase range of elements
// v.erase(first, last);

// Parameters:
// pos: Iterator to the element to be deleted.
// first: Iterator to the first element in the range.
// last: Iterator to the theoretical element just after the last element in 
// the range.
// Remove elements in the range [1, 4):
// v.erase(v.begin() + 1, v.begin() + 4);

// std::remove(first, last, val);
// Remove all occurrences of val from a vector 

// Parameters
// first: Iterator to the first element of the container.
// last: Iterator to the element after the last element of the container.
// val: Value to be removed.

// As you may have noticed, we still had to use the vector::erase() function
// to actually delete the elements. This is due to the fact that std::remove()
// function moves all the elements to remove at the end of the container and 
// returns an iterator to the new end of the range that only contains the 
// elements not to remove. It doesn't actually delete these elements from the
// container.

void solve() {
    int n;
    cin >> n;

    vvi adjList(n);
    vpii roads(n - 1);
    for (int i = 0; i < n - 1; i++) {
        int node1, node2;
        cin >> node1 >> node2;
        node1--, node2--;
        adjList[node1].pb(node2);
        adjList[node2].pb(node1);
        roads[i] = {node1, node2};
    }

    int maxProfit = 0;
    for (int i=0; i<n-1; i++){
        int node1 = roads[i].F, node2 = roads[i].S;

        // Temporarily remove the edge (node1, node2)
        adjList[node1].erase(remove(all(adjList[node1]), node2), adjList[node1].end());
        adjList[node2].erase(remove(all(adjList[node2]), node1), adjList[node2].end());

        // Find the diameters of the two components
        int diameter1 = findDiameter(node1, adjList);
        int diameter2 = findDiameter(node2, adjList);

        // Update the maximum profit
        maxProfit = max(maxProfit, diameter1 * diameter2);

        // Restore the edge (node1, node2)
        adjList[node1].pb(node2);
        adjList[node2].pb(node1);
    }

    cout << maxProfit << '\n';
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
