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
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits

// Solved this problem easily.
// but I read this goofy ahh problem wrongly when outputting
// the answer, which made me so fucking confused.
// What they wanted was to output the node in the order from index to 1 to n
// so if I want to sell node 4 first, it would be on index 0, and if I want
// to sell node 10 as the 3rd node, it would be on index 2 ans so on...
// What my silly ass thought was that if I want to sell node 4 first,
// then index 3 should be 1, and if I want to sell node 10 as the 3rd node,
// then index 9 should be 3.
// bruh and this shit made me way to confused.
// Either way, I solved the problem, quite easily actually.
// Turns out this problem can be labelled as a directed graph, where each
// node has only one edge, and there is a cycle for each disjoint component.
// you want to trim the leaf nodes first (nodes with inDegree == 0) so that
// you can double the profit.
// There will come a point where you will encounter a cycle after trimming
// the component.
// Then we need to deal with it by finding the smallest value node in the cycle
// and bfs from the node that it points to.
// Why? Because greedily, to maximize we want to double all the higher values
// in the component.
// Notice that, each component can have all nodes doubled except one
// because of the cycle in each component.
// in other words, we just find the min value node and start bfs at where
// it points to so that in the end we can reach the min value node again
// and we will directly be able to pop it last.

bool visited[MAXN];

void solve() {
	int n, k, m;
    cin >> n;

    memset(visited, 0, sizeof(visited));
    vvi adjList(n); 
    vi inDegree(n);
    vi a(n), c(n);
    for (int i=0; i<n; i++){
        int node;
        cin >> node;
        node--;
        a[i] = node;
        adjList[i].pb(node);
        inDegree[node]++;
    } 

    for (int& x: c) cin >> x;

    queue<int> q;
    for (int i=0; i<n; i++){
        if (inDegree[i] == 0) q.push(i);
    }

    vi result;
    while (!q.empty()){
        int curNode = q.ft();
        q.pop();
        if (visited[curNode]) continue;
        visited[curNode] = 1;
        result.pb(curNode+1);
        for (int nextNode : adjList[curNode]){
            inDegree[nextNode]--;
            if (inDegree[nextNode] == 0){
                q.push(nextNode);
            }
        }
    }

    for (int i=0; i<n; i++){
        if (!visited[i]){ // cycle 
            int v = a[i];
            vi cycle = {v};
            int minVal = c[i];
            while (v != i){ // backtrack to get all node in cycle
                minVal = c[v] < minVal ? c[v] : minVal;
                v = a[v];
                cycle.pb(v);
            }

            // printVector(cycle);
            // cout << minVal << endl;

            for (int node: cycle){
                if (c[node] == minVal){
                    // start at next node after min node
                    //q.push(node);
                    q.push(a[node]);
                    while (!q.empty()){
                        int curNode = q.ft();
                        q.pop();
                        if (visited[curNode]) continue;
                        visited[curNode] = 1;
                        result.pb(curNode+1);
                        for (int nextNode : adjList[curNode]){
                            inDegree[nextNode]--;
                            if (inDegree[nextNode] == 0){
                                q.push(nextNode);
                            }
                        }
                    }
                }
            }
        } 
    }

    printVector(result);
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
