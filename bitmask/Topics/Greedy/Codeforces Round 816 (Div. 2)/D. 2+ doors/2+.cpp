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
const int MAXN = 1e5+5; // fenwick = N, trie  = N * number of bits

// Nice problem.
// Had to use the editorial to understand how do it. 
// Only then could I do it myself.
// This problem was tough bruh, I thought I could do it but man was I wrong.

void solve() {
	int n, k, m, q;
    cin >> n >> q;

    vvpii adjList(n);
    for (int i=0; i<q; i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--,v--;
        adjList[u].pb({v, w});
        adjList[v].pb({u, w});
    }

    // IMPORTANT: set all values to 1 at each bit initially
    vi result(n,(1<<30)-1);

    // we need to solve the problem bit by bit, because OR is independent
    // of each other.
    // let x | y = 1 | 1 == 1.
    // regardless of whether x or y is 1, then answer is 1.
    // => independence.

    for (int bit=0; bit<30; bit++){
        for(int curNode=0; curNode<n; curNode++){
            for (auto [nextNode, weight] : adjList[curNode]){
                // if the bit is not set at this bit pos for the weight (edge)
                // => both nodes can be 0 at this bit pos for this edge connection
                // Why? Because there is no contribution needed for both
                // nodes to make this bit 0 at this edge.
                // so this minimizes our value
                // making it lexicographically smaller.
                if (!(weight & (1<<bit))){
                    result[curNode] &= ~(1<<bit);
                }
            }
        }

        // looping from 0 to n-1 ensures lexicographical min
        // because greedily, we always turn off the smaller idx bits first if
        // possible => lexicographical min
        for(int curNode=0; curNode<n; curNode++){
            bool canSetZero = true;
            if (result[curNode] & (1<<bit)){ // check if we can turn this bit off
                for (auto [nextNode, weight] : adjList[curNode]){
                    // if the node connects to itself, we can never set
                    // this bit to 0 (because the weight is 1)
                    if (nextNode == curNode){
                        canSetZero = false;
                        break;
                    }

                    // if the nextNode is 0, then the curNode must be 1
                    // (because again, the weight is 1 at this bit, and 
                    // we need to satisfy the condition)
                    if (!(result[nextNode] & (1<<bit))){
                        canSetZero = false;
                        break;
                    }
                }
            }

            if (canSetZero) result[curNode] &= ~(1<<bit);
        }
    }

    printVector(result);
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

// My bum ass solution. Which is wrong.

// bool visited[MAXN] = {false}, connectItself[MAXN] = {false};

// void dfs(int curNode, vi& result, vvpii& adjList){
//     visited[curNode] = true;
//     for (auto [nextNode, weight] : adjList[curNode]){
//         if (!visited[nextNode]){
//             dfs(nextNode, result, adjList);
//             if (!connectItself[nextNode]) result[nextNode] = result[curNode]^weight;
//             if (!connectItself[curNode]) result[curNode] = result[nextNode]^weight;
//         }
//     }
// }

// void solve() {
// 	int n, k, m, q;
//     cin >> n >> q;

//     vvpii adjList(n);
//     vi result(n,0);
//     for (int i=0; i<q; i++){
//         int u, v, w;
//         cin >> u >> v >> w;
//         u--,v--;
//         if (u == v) result[u] = w, connectItself[u] = true;
//         adjList[u].pb({v, w});
//         adjList[v].pb({u, w});
//     }

//     for (int i=0; i<n; i++){
//         if (visited[i]) continue;
//         dfs(i, result, adjList);
//     }

//     printVector(result);
// }