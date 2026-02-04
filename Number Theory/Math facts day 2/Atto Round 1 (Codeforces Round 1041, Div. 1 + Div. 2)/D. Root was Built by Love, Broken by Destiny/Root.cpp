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
using vpll = vector<pair<long long, long long>>;
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

const ll K = 6e6+5; // change according to your needs
vll mn(K, 0); // Smallest prime factor of each number
vvll fcv(K); // Prime factorization for each number (only returns each distinct factor once)


void precompute_prime_factors() { // Modified Sieve
    mn[1] = 1; // Base case: 1 has no prime factors
    for (ll i = 2; i < K; i++) {
        if (!mn[i]) { // If i has no prime factor recorded yet, it is a prime number.
            for (ll j = 1; j * i < K; ++j) {
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

void sieve() {
    mn[1] = 1; // 1 is not prime
    for (ll i = 2; i < K; i++) {
        if (mn[i] == 0) { // i is prime
            mn[i] = i;
            for (ll j = i * i; j < K; j += i) {
                if (mn[j] == 0) {
                    mn[j] = i; // smallest prime factor of j
                }
            }
        }
    }
}

vi get_primes_up_to_K() {
    vi primes;
    for (ll i = 2; i < K; i++) {
        if (mn[i] == i) primes.pb(i);
    }
    return primes;
}

// get all factors up to n
vvi factors(K);

void getAllFactors(){
    for (int i = 1; i <= K; i++) {
        for (int j = i; j <= K; j += i) {
            factors[j].push_back(i); // i is a divisor of j
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
const int MAXN = 2e5+5; // fenwick = N, trie  = N * number of bits

// solve time ~ can't solve. Amazing problem.
// Honestly this was such a tough problem for me.
// First, notice that the graph is fully connected, so there is 
// no multiple disjoint components in the input.
// Now, realize that the graph is bipartite, because we must 
// have no components in the same region to be connected.
// What can we observe from this?
// In fact, there cannot be any cycles in the graph.
// Proof:
// 1 <-> 2 <-> 3 <-> 1
// then, it should be:
// 1 3
// 2
// but, there is an edge between 1 and 3, even if you put 3 in the
// other side, there is an edge between 2 to 3.
// So, there cannot be any cycles in the graph.
// Meaning, if m > n-1, its just wrong, keep in mind m>=n-1 from input.
// So, our graph is now a tree.
// What else can we observe?
// Playing around with testcases, you will realize that non-leaf
// nodes can have only AT MOST 2 connections to other non-leaf nodes.
// Proof:
//        1
//      2 3 4
//      5 6 7
// then, the bipartite graph looks like:
//    5 1 6 7
//    2 3 4 
// As you can see, 6 is the issue, because it needs to connect to 
// 3 while 1 needs to connect to 4, so we cannot have 6.
// In fact, a non-leaf node MUST have AT MOST 2 connections with
// other non-leaf nodes only, because the best possible arrangement
// would look like: consider without node 6 from the graph I made.
//   5 1 7
//   2 3 4
// then, 2 and 4 can have infinite number of children and its still valid.
// something more complicated would be:
// y y y 1 x x x
//   2 3 4 5 6
// where the children of 1 is 3,4,5, children of 2 is y,y,y and
// children of 6 is x,x,x.
// and among each children we can do (no. of children)! number 
// of arrangements, the total will be multiply all 
// such factorial among the children of each non-leaf node.
// And thats the idea.
// But, we are not done yet, because we are only counting the 
// arrangements among the leaves while fixing the non-leaf nodes.
// the order of the non-leaf nodes can be changed as well.
// In fact, there are only 4 ways to do so.
// Hence, the answer is just 4*(no. of children)! of each non-leaf
// node.
// Proof thats its 4:
// for at least 2 non-leaf nodes,
// 1 way is the default way.
// 2nd way is to flip the default way into the other component.
// 3rd way is to reverse both components on the default way.
// 4th way is to flip the 3rd way into the other component.
// Any other way cannot work, because it will cause intersections
// between the bridges.

// There is an edge case tho.
// If the no. of non-leaf node is only 1, meaning we form
// a star graph, then the number of solutions is multiply by 2.
// because we can only flip that node up and down into both 
// component.
// Eg.
//    1       or      2 3 4   
//  2 3 4               1     and then permute the children, 3!
// so the total is 2*3! for this.



void solve() {
	int n, k, m;
    cin >> n >> m;

    vvi adjList(n+1);
    for (int i=0; i<m; i++){
        int node1, node2;
        cin >> node1 >> node2;
        adjList[node1].pb(node2);
        adjList[node2].pb(node1);
    }

    if (m != n-1) {cout << 0 << '\n'; return;}

    // get the no. of connections of each non-leaf node
    vvi adjList2(n+1);
    ll cnt = 0;
    for (int node=1; node<=n; node++){
        if (sz(adjList[node]) > 1){
            cnt++;
            for (int nextNode : adjList[node]){
                if (sz(adjList[nextNode]) > 1){
                    adjList2[node].pb(nextNode);
                }
            }
        } 
    }

    for (int node=1; node<=n; node++){
        if (sz(adjList2[node]) >= 3) {cout << 0 << '\n'; return;}
    }

    ll ans = (cnt >= 2 ? 4 : 2);
    
    for (int node=1; node<=n; node++){
        ll cntLeaf = 0;
        if (sz(adjList[node]) > 1){
            for (int nextNode : adjList[node]){
                if (sz(adjList[nextNode]) == 1) cntLeaf++;
            }
        }
        ans *= fact[cntLeaf];
        ans %= MOD;
    }
    
    cout << ans << '\n';
}

int main() {
    fast_io();
    precompute_factorials(MAXN, MOD);
    // sieve();
    // precompute_prime_factors(); // modified sieve
    int t;
    cin >> t;
    while (t--) solve();
    // solve();
    return 0;
}
