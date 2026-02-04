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

void dfs(int curNode, int parentNode, const vvi &adjList, vi &dist, int h){
    dist[curNode] = h;
    for (int nextNode : adjList[curNode]) {
        if (nextNode != parentNode) {
            dfs(nextNode, curNode, adjList, dist, h+1);
        }
    }
}

void solve() {
    int n, k;
    cin >> n;

    vvi adjList(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adjList[u].pb(v);
        adjList[v].pb(u);
    }

    vi dist1(n, -1);
    // dfs from any arbitrary node to get the furthest distance from it.
    dfs(0, -1, adjList, dist1, 0);
    int farthestNode1 = max_element(all(dist1)) - dist1.begin();
    // this node will be the start node of the diameter
    // dfs from this node to find the end node of the diameter
    // and to update all distances of nodes referencing from the start node.
    dfs(farthestNode1, -1, adjList, dist1, 0);

    vi dist2(n, -1);
    // get the end node of the diameter.
    int farthestNode2 = max_element(all(dist1)) - dist1.begin();
    // dfs from the end node as well to update all distances of nodes referencing
    // from the end node
    dfs(farthestNode2, -1, adjList, dist2, 0);

    // we update the maximum distance of any node to either the start/end node
    // of the diameter
    // Why? 
    // lets say this is the diameter: x and y are start and end nodes of diameter
    // x <-> x1 <-> x2 <-> d <-> x4 <-> x5 <-> y
    //       x3                         x6
    // x3 and x6 are connected to x1 and x5.
    // notice that from x3 to x the distance in dist1 is 2, while in 
    // dist2 its 6
    // Similarly for x6, in dist2 its dist2[x6]==2, dist1[x6]==6.
    // The reason why we need to get the distance from both x and y as 
    // reference points and take the max is because lets say when
    // k==3, by right x3 should be a connected component to the diameter nodes
    // but if we only have dist1 (which is reference from x only) then we
    // won't be able to include it into the component when it should've been
    // a part of the component as x3 from y is connected since dist2[x3]==6.
    // So how to know if a node is connected to the diameter nodes?
    // We take the max distances of the 2 nodes as reference points.

    for (int i=0; i<n; i++){
        dist2[i] = max(dist2[i], dist1[i]);
    }

    // we sort the maximum distances of each point to either x or y nodes.
    // then we can know that when dist2[node] < k, that means its not connected
    // to the x and y nodes so ans++.
    // This part here is greedy.
    // We start from the shortest distance nodes to see whether it can be 
    // connected to the diameter start and end node component or not since
    // the diameter always gives the max distance (either from the start
    // or end node of the diameter).
    sort(all(dist2));
    int ans = 0;
    for (int k = 1; k <= n; k++){
        while (ans < n && dist2[ans] < k){
            ans++;
        }
        cout << min(n, ans+1)  << ' ';
    }
    
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
