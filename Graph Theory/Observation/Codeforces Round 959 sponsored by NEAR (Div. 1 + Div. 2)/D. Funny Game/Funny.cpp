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
const int MAXN = 1e9+5; // fenwick = N, trie  = N * number of bits

// can't solve. Got humbled.
// idk what I'm even doing for this problem...
// turns out its just pigeonhole principle...
// this is why I love adhoc problems...
// Still a good problem tho

int l[2001], r[2001], mark[2001];
bool visited[2001];

void solve() {
	int n, k, m;
    cin >> n;
    
    vi a(n+1);
    for (int i=1; i<=n; i++) cin >> a[i];
    for (int node=1; node<=n; node++) visited[node] = false;

    // question wants abs(a[u] - a[v]) % x == 0
    // => a[u] % x = a[v] % x
    // we have n nodes each with some a[i].
    // we want n-1 connections.
    // this is always possible, because by the pigeonhole principle,
    // a[i] % (n-1) will always have EXACTLY ONE extra duplicate 
    // for some i as we have n nodes.
    // eg. if we have 3 nodes, then we have x=2 connections
    // => a[i] % 2 for each i from 1 to 3 will guarantee a duplicate
    // a[i1] % 3 == a[i2] % 3 because i is [1,3], (3 elements)
    // => connection between 2 nodes is always possible.
    // therefore we can just repeat this process for each x from 
    // n-1 to 1.
    // we do in reverse because otherwise pigeonhole principle 
    // cannot be applied. Eg, 1 can just divide every edge anyways, but
    // which edge do we take?

    for (int x=n-1; x>=1; x--){
        for (int mod=0; mod<x; mod++) mark[mod] = 0;
        for (int node=1; node<=n; node++){
            if (!visited[node]){
                int mod = a[node] % x;
                if (mark[mod]){
                    l[x] = mark[mod];
                    r[x] = node;
                    visited[node] = true;
                    break;
                } 
                else mark[mod] = node;
            }
        }
    }

    cout << "YES" << '\n';
    for (int x=1; x<n; x++){ // n-1 edges from 1 to n-1
        cout << l[x] << " " << r[x] << '\n';
    }

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


// vvi isDivisible(MAXN);

// void preComputeDivisors(){
//     for (int x = 1; x <= 1999; x++){
//         for (ll num = x; num <= 1e9; num += x){
//             isDivisible[num].pb(x); // Directly store x as a divisor
//         }
//     }
// }

// void dfs(int curNode, int parentNode, vvi& adjList){
//     for (int nextNode : adjList[curNode]){
//         if (nextNode != parentNode){
//             dfs(nextNode, curNode, adjList);
//             cout << curNode << " " << nextNode << '\n';
//         }
//     }
// }

// void solve() {
// 	int n, k, m;
//     cin >> n;

//     vi a(n);
//     for (int& x: a) cin >> x;

//     vvi adjList(n+1);
//     vb visitedX(n+1, false);
//     vb visitedNode(n+1, false);
//     int cnt = 0;
//     bool flag = false;
//     for (int u=1; u<=n; u++){
//         visitedNode[u] = true;
//         for (int v=1; v<=n; v++){
//             int diff = abs(a[u]-a[v]);
//             for (int i=sz(isDivisible[diff])-1; i>=0; i--){
//                 // dont use the same x, and make sure v is not already
//                 // part of the same component already
//                 if (!visitedX[isDivisible[diff][i]] && !visitedNode[v]){
//                     visitedX[isDivisible[diff][i]] = true;
//                     visitedNode[v] = true;
//                     adjList[u].pb(v);
//                     adjList[v].pb(u);
//                     cnt++;
//                     break;
//                 }
//             }

//             if (cnt == n-1){
//                 flag = true;
//                 break;
//             }
//         }
//         if (flag) break;
//     }

//     if (flag){
//         cout << "YES" << '\n';
//         dfs(1,0, adjList);
//     }
//     else cout << "NO" << '\n';