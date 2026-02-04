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

const int N = 1e6 + 5; // change according to your needs
vi mn(N, 0); // Smallest prime factor of each number
vvi fcv(N); // Prime factorization for each number (only returns each distinct factor once)


void precompute_prime_factors() { // Modified Sieve
    mn[1] = 1; // Base case: 1 has no prime factors
    for (int i = 2; i < N; i++) {
        if (!mn[i]) { // If i has no prime factor recorded yet, it is a prime number.
            for (int j = 1; j * i < N; ++j) {
                if (!mn[i * j])
                    mn[i * j] = i; // Mark i as the smallest prime factor for all multiples of i.
            }
        }
    }

    // Generate prime factor lists for every number up to N
    for (int i = 1; i < N; i++) {
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

// I was so close to solving this problem, I just needed one more observation...
// we need to bfs from b, if any node we are on is 0. Then we can just teleport from
// a to that node, call it c, then go from c to b.
// Here is where I made a mistake.
// If c does not exist, then I realised that we need to find a subtree 
// such that its XOR is equal to the XOR from a to b.
// But this is wrong.
// Because the paths cannot overlap as they will just cancel out (x^x=0). 
// Backtracking a bit, I realised that I still have a teleport (tp) if no such c nodes 
// exist
// Here is where I got stuck, and gave up...
// Actually, I was so close, my solution is basically a "subset" of the general solution
// The idea is that, we just need to find some path from a to c, then tp to d then go
// to b such that the path from a to c is equal to the path from d to b
// so their XOR cancels out.
// I basically only acccounted for when a is one node, not a to any node c.
// From a to c, if its XOR is equal to some paths from d to b, then 
// we can just go from a to c, then tp to d, then go from d to b.
// In other words, we can just BFS/DFS from a to some node c, where c!=b (because
// b is the final node to reach, we don't want to go to any nodes after node b
// from a)
// and keep track of all the XOR so far in a set.
// then, we do another BFS/DFS from b to some node d, XOR along each unique path
// until we ecounter some node from d to b (but not d == b because we cannot teleport
// to b) such that its XOR exists within
// out set from the first BFS/DFS, then we can just return true => YES.
// Otherwise, NO.

void dfs1(int curNode, int parentNode, vvpii& adjList, set<int>& memo, int curXOR, int b){
    // b is the final node, so we don't go beyond b
    if (curNode == b) return;
    memo.insert(curXOR);
    for (auto e : adjList[curNode]){
        int nextNode = e.F, weight = e.S;
        if (nextNode != parentNode){
            dfs1(nextNode, curNode, adjList, memo, weight^curXOR, b);
        }
    }
}

bool dfs2(int curNode, int parentNode, vvpii& adjList, set<int>& memo, int curXOR, int b){
    // curNode != b because 
    // 1. at b, XOR is always 0 (since its the start) and the set already has 0
    // so it will always trivially return true (which is wrong)
    // 2. we don't want to tp to b (because we cannot tp to b from the question)
    if (curNode != b && memo.count(curXOR)) return true;
    for (auto e : adjList[curNode]){
        int nextNode = e.F, weight = e.S;
        if (nextNode != parentNode){
            if (dfs2(nextNode, curNode, adjList, memo, weight^curXOR, b)) return true;
        }
    }

    return false;
}


void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    a--, b--;
    
    vvpii adjList(n);
    set<int> memo;
    for (int i=0; i<n-1; i++){
        int node1, node2, weight;
        cin >> node1 >> node2 >> weight;
        node1--, node2--;
        adjList[node1].pb({node2, weight});
        adjList[node2].pb({node1, weight});
    }

    dfs1(a, -1, adjList, memo, 0, b);
    if (dfs2(b, -1, adjList, memo, 0, b)) cout << "YES" << '\n';
    else cout << "NO" << '\n';
    
}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
