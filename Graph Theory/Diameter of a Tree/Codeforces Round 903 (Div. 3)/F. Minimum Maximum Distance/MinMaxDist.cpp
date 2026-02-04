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

// I tried solving this problem, over engineered it and made a solution that was TLE
// Reason: I did not know the property of a diameter of a tree that well
// Diameter of a tree and its applications: https://codeforces.com/blog/entry/101271


// The intution behind this problem lies in diameter of a tree
// tip: when we think about max/min distance in a tree, we can think about 
// diameter as a potential candidate solution.
// The trick here is to perform a dfs/bfs on any marked node, x, and then find
// the maximum distance of this marked node x to another marked node y.
// then from y, we perform another dfs/bfs to find the maximum distance from y
// to another marked node z (note that z could be x).
// then we can find the answer, d, by doing the max distance between y and 
// z / 2 and ceiling it

// proof:
// lets say you have a tree with more than 1 marked nodes.
// once you find the diameter of the marked nodes on the tree
// and you found d.
// think of the answer as now a chain, x <-> x1 <-> x2 <-> x3 <-> x4 <-> x5 <-> y, where 
// this contains the maximum distance between any 2 marked nodes, in this case its x and y.
// from there, we know that the answer is d, where d = 3.
// it would look like this: x <-> x1 <-> x2 <-> d <-> x4 <-> x5 <-> y
// lets add another marked node, c, outside of of this chain
// but dist(x,c) and dist(c,y) is less than the dist(x,y) 
// x <-> x1 <-> x2 <-> d <-> x4 <-> x5 <-> y
//              c
// note that c can be anywhere as long as it remains that c is not a node that is part of the 
// diameter that creates it.
// basically saying dist(x,c) and dist(c,y) is less than the dist(x,y) must hold (otherwise
// x and y wouldn't be the diameter anymore)
// notice that, the maximum distance from c to any vertex is y.
// which is a distance of 5
// in fact, placing c optimally would be below d, which always results in a maximum distance
// of d+1=4, which is the minimum maximum distance.
// notice that, even if we place a marked node optimally (which is below d), the minimum maximum
// distance is still going to be at least d+1, which is more than d.
// hence, finding the diameter of a tree (specifically the diameter of maked vertices) 
// works here. 

// Time complexity: O(V+E + V+E)
// Space complexity: O(E + marked nodes + V + V)

void dfs(int curNode, int parentNode, const vvi &adjList, vi &dist, int h) {
    dist[curNode] = h;
    for (int nextNode : adjList[curNode]) {
        if (nextNode != parentNode) {
            dfs(nextNode, curNode, adjList, dist, h+1);
        }
    }
}

void solve() {
    int n, k;
    cin >> n >> k;

    vvi adjList(n);
    vi marked(k);

    for (auto &x : marked) {
        cin >> x;
        --x;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    if (k == 1) {
        cout << 0 << '\n';
        return;
    }

    // First DFS from any marked node to find the farthest marked node
    vi dist1(n, -1);
    dfs(marked[0], -1, adjList, dist1, 0);

    int farthestNode1 = marked[0];
    for (int e : marked) {
        if (dist1[e] > dist1[farthestNode1]) farthestNode1 = e;
    }

    // Second DFS from the farthest node found
    vi dist2(n, -1);
    dfs(farthestNode1, -1, adjList, dist2, 0);

    int farthestNode2 = farthestNode1;
    for (int e : marked) {
        if (dist2[e] > dist2[farthestNode2]) farthestNode2 = e;
    }

    cout << (dist2[farthestNode2] + 1) / 2 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}