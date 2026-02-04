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
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits

// Absolutely amazing problem using multiset.
// I learned a trick, this was so cool.
// We can brute force this, with multiset
// so the time complexity can become nlogn instead of n^2
// Idea:
// for each node, we delete it, then we find the next best node to delete
// and get the sum of connected components after deleting these 2 nodes.
// Observation 1: I noticed this
// Removing any node means we increase the number of connected components
// by inDegree[node]-1, not inDegree[node].
// Why? Because one of the inDegree[node] component will be further broken down
// into more components on the 2nd removal, and if the component happens to be 
// just one singular node then we dont add anything at all.
// In other words, we only know for sure that we can increase our current 
// connected components by inDegree[node]-1 for now.
// Of course, after we pick this node, we need to decrease the in degree of the other
// nodes that connects to this current node, and also remove the in degree of this 
// node.
// This is where multiset can be used.
// all these operations can be done in O(logn)
// we first add all the in degree of each node into the multiset.
// then for each node, we remove one occurence of the in degree of this node.
// then for each neighbour, we remove the in degree of the neighbours, and add
// the in degree -1 for each neighbor (because now each neighbour has one less 
// connection) 
// So, now we sucessfully simulated the first removal.
// Observation 2:
// For the 2nd removal, we greedily just wanna take the node with the highest in
// degree (because that will make the most number of connected components).
// Multiset makes this convenient, we can just do *s.rbegin() to get the largest
// in degree after the removal of this current node.
// Then the answer is just ans = max(ans, sz(adjList[node])-1+*s.rbegin())
// Afterwards, we update back to our original in degrees.
// so add back the in degree of this node, and remove the neighbours in degree -1,
// and add back the actual in degree of each neighbour.
// This is all done in O(logn) time on multiset. Perfect.

// Time complexity: O(NlogN + 4*(N-1))
// 4*(N-1) because we go through each edge 4 times, twice for each loop (because
// curNode -> nextNode and nextNode -> curNode are considered twice on both 
// perspectives).

void solve() {
	int n, k, m;
    cin >> n;

    vvi adjList(n+1);
    for (int i=0; i<n-1; i++){
        int u, v;
        cin >> u >> v;
        adjList[u].pb(v);
        adjList[v].pb(u);
    }

    mset<int> s;
    for (int node=1; node<=n; node++) s.insert(sz(adjList[node]));

    int ans = 0;
    for (int node=1; node<=n; node++){
        s.erase(s.find(sz(adjList[node])));

        for (int nextNode : adjList[node]){
            s.erase(s.find(sz(adjList[nextNode])));
            s.insert(sz(adjList[nextNode])-1);
        }

        ans = max(ans, sz(adjList[node])-1 + *s.rbegin());
        s.insert(sz(adjList[node]));

        for (int nextNode : adjList[node]){
            s.erase(s.find(sz(adjList[nextNode])-1));
            s.insert(sz(adjList[nextNode]));
        }
        
    }

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

// My attempt: which was wrong
// void solve() {
// 	int n, k, m;
//     cin >> n;

//     vvi adjList(n+1);
//     for (int i=0; i<n-1; i++){
//         int u, v;
//         cin >> u >> v;
//         adjList[u].pb(v);
//         adjList[v].pb(u);
//     }

//     int maxSize = 0;
//     int maxNode1 = -1; // get node with most connections
//     for (int node=1; node<=n; node++){
//         if (sz(adjList[node]) > maxSize){
//             maxSize = sz(adjList[node]);
//             maxNode1 = node;
//         } 
//     }   
    
//     // remove the edges 
//     vi c;
//     for (int nextNode : adjList[maxNode1]) c.pb(nextNode);
    
//     for (int nextNode : c){
//         adjList[maxNode1].erase(remove(all(adjList[maxNode1]), nextNode), adjList[maxNode1].end());
//         adjList[nextNode].erase(remove(all(adjList[nextNode]), maxNode1), adjList[nextNode].end());
//         // cout << nextNode << " " << maxNode1 << endl;
//         // cout << sz(adjList[maxNode1]) << endl;
//         // cout << sz(adjList[nextNode]) << endl;
//     }

//     int ans = maxSize - 1; 
//     // cout << ans << endl;
//     maxSize = 0;
//     for (int node=1; node<=n; node++){
//         if (node == maxNode1) continue;
//         // cout << node << " " << sz(adjList[node]) << endl;
//         if (sz(adjList[node]) > maxSize){
//             maxSize = sz(adjList[node]);
//         } 
//     }   
//     // cout << maxSize << endl;
//     cout << ans + maxSize << '\n';

// }
