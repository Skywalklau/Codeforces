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
const int MAXN = 2e5+5; // fenwick = N, trie  = N * number of bits

// solve time ~ bruh took too long...
// BUT, I SOLVED IT WITH AN EVEN BETTER SOLUTION THAN THE EDITORIAL.
// This was a very nice problem, I actually managed to solve this in 
// quite an elegant manner, O(N) time. Faster than editorial.
// Tbh, editorial was fucked up, they were mentioning virtual trees which
// idk wtf it is..., and the solution runs in O(NLOGN) time, which is even
// worse than my solution bruh.
// The idea is to use just one single dfs, with a cute little trick to 
// restore states of each node according to their colour.
// Idea: dp.
// for each node of a certain colour, we can keep track of a cnt of 
// that colour that this node can reach, basically dp.
// Specifically, dp[c[curNode]] = number of nodes of the same colour
// that this curNode can reach while satisfying the given criteria.
// then we can just do ans += dp[c[curNode]].
// Transition (the hardest part):
// Notice that, when we reach a node of the same colour, after adding
// dp[c[curNode]] to our ans, we need to reset the dp[c[curNode]] to 1.
// Why? Because now, this curNode will be the new starting point for 
// the whole subtree in the dfs. Therefore, every new node of the same
// colour will meet this node, then we set the dp[c[nextNode of the same
// colour]] to 1 again, and repeat this process (cuz its dp).
// Drawing it out helps a lot...
// Last thing to note, after dfs, as we backtrack upwards, we need to 
// set dp[c[curNode after dfs]] = dp[c[curNode before dfs]] + 1 to restore
// its state with a +1.
// Why? Because now, every node that we meet before the curNode (basically
// like dfs, we will backtrack, to a higher level from curNode, so its 
// all the nodes that are of a higher ancestry than curNode), will not 
// only meet curNode itself, but also curNode's ancestors as well at some
// point of the tree.
// Essentially, the +1 comes from curNode itself (every path that forms
// will include curNode as the start node now), and dp[c[curNode]] comes 
// from all the nodes that curNode can meet such that all these dp[c[curNode]]
// will be the starting nodes to the other potential paths to other nodes.

int c[MAXN], dp[MAXN];
ll ans;

void dfs(int curNode, int parentNode, vvi& adjList){
    //if (c[curNode] == 4) cout << curNode << " " << cnt[c[curNode]] << endl;
    ans += dp[c[curNode]];
    int temp = dp[c[curNode]];
    for(int nextNode : adjList[curNode])
        if(nextNode != parentNode){
            dp[c[curNode]] = 1;
            dfs(nextNode, curNode, adjList);
        }
    dp[c[curNode]] = temp+1;
    //if (c[curNode] == 4) cout << curNode << " k " << cnt[c[curNode]] << endl;
}
 

void solve() {
	int n, k, m;
    cin >> n;
    for (int i=1; i<=n; i++) cin >> c[i];
    
    ans = 0;
    vvi adjList(n+1);
    for (int i=0; i<n-1; i++){
        int node1, node2;
        cin >> node1 >> node2;
        adjList[node1].pb(node2);
        adjList[node2].pb(node1);
    }

    for (int i=1; i<=n; i++) dp[i] = 0;
    dfs(1, 0, adjList);

    cout << ans << '\n';
    
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
