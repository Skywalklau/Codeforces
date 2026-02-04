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

// graphical visualization is written in coding sketchbook pg. 353
// In any case, this was a very nice problem.
// Initially, I tried doing this via diameter of a tree.
// But then I realized you would need to know the lca in order to solve it.
// So I started thinking in terms of lca, and solved it.
// Took longer than expected to solve this problem, but it was worth it.
// The key here is to realize that, by finding the lca and having a reference point
// (which is the root, in this case we make the root as node 1)
// then we can solve this problem.
// each query q has 3 nodes, a, b, c.
// we don't know which is the best combination of s,t, and f.
// we try all, which only has 3 combinations (not 6 because s being the node f
// and f being the node s is the same thing, essentially there are duplicate 
// perspectives)
// Now, from there we can find the lca of s and t, then get the distance from 
// s and t via the lca.
// Note that each node's distance is referenced from the root node.
// say I have s and t, their lca is the root node itself.
// then the distance, dist(s,t), is going to be s to the root node, root node to t,
// or to make it more explicit, the depth[s] + depth[t], which we can precompute 
// in a dfs for all nodes.
// lets say the lca is not the root node, then the perspective is like this:
// dist(s,t) == depth[s] + depth[t] - 2*depth[lca(s,t)]
// why do we minus 2*depth[lca(s,t)]?
// since s and t share an lca that is not the root node, that means the lca of 
// s and t should be the reference point instead, but as I mentioned the reference
// point for the depth of all nodes is from the root node itself.
// Hence, we need to subtract the distance from the lca to the root node.
// and we do it twice, because depth[s] contributes once, and depth[t] also
// contributes another time, so total is 2 times it is reference from the root node.
// by subtracting 2*depth[lca(s,t)], we essentially made the path as:
// s -> lca(s,t) -> t.
// which is the desired output, since we want dist(s,t).
// Now, we do this for each combination of nodes a,b,c.
// so we can get ac = dist(a,b), bc = dist(b,c), ca = dist(c,a).
// using this, we can actually find the common nodes each combo of s,t and f
// meet.
// lets say c is the target, then a and b is s and t vice versa (we dont need to
// check the other way around for a and b as t and s because its the same perspective)
// then, to get the common nodes of a and b to c, we can do:
// common nodes = (ac + bc - ab)/2 + 1.
// ac + bc - ab == the distance from lca(a,b) to c.
// /2 == we double counted the distance from lca(a,b) to c, so /2.
// +1 == since (ac + bc - ab)/2 is the distance, or in terms of graphs, the No.
// of edges, we do +1 to get the No. of nodes.
// Hence, common nodes = (ac + bc - ab)/2 + 1.
// this is just one combination, we need to do 2 more.
// which is c a b and a c b
// again, node that a and b can be swapped, but it dont matter because its just 
// the same perspective again.
// then u get the maximum out of all the combinations, cuz thats what the question
// wants.

// Time complexity: O((N+Q)*LOGN)
// Space complexity: O(N*LOGN)


vvi adjList(MAXN);
int par[MAXN][LOGN], depth[MAXN];

void dfs(int u, int p){
    par[u][0] = p; // Store the direct parent of u

    // Precompute binary lifting table
    for (int i=1; i<LOGN; i++){
        if (par[u][i-1] != -1) par[u][i] = par[par[u][i-1]][i-1]; // Binary lifting table
        else par[u][i] = -1;
    }

    // Visit all children of u
    for (int v : adjList[u]){
        if (v == p) continue; // Avoid revisiting parent
        depth[v] = depth[u] + 1; // Set depth
        dfs(v, u);
    }
}

int lca(int u, int v){
    if (depth[u] < depth[v]) swap(u, v); // Ensure u is deeper
    int diff = depth[u] - depth[v];

    // Move u up until it's at the same depth as v
    for (int i=0; i<LOGN; i++){
        if (diff & (1 << i)) u = par[u][i];
    }

    // check if v is the ancestor of u.
    //    v
    //   u
    if (u == v) return u; // If they meet, return LCA

    // Move both up until they meet
    // lca(u,v)
    // u    v
    for (int i=LOGN-1; i>=0; i--){
        if (par[u][i] != par[v][i]){
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0]; // Return their parent, which is the LCA
}

int dist(int u, int v){
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

void solve() {
    int n, m, k, q;
    cin >> n >> q;

    for (int i = 2; i <= n; i++){
        int v;
        cin >> v;
        adjList[i].pb(v);
        adjList[v].pb(i);
    }

    memset(par, -1, sizeof(par));
    depth[1] = 0;
    dfs(1, -1);
    while (q--){
        int a, b, c;
        cin >> a >> b >> c;
        int ab = dist(a, b), bc = dist(b, c), ca = dist(c, a);
        cout << (max({ab + bc - ca, bc + ca - ab, ca + ab - bc}) / 2 + 1) << '\n';
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


// void bfs(int start, vi &parent, vi &dist, vvi &adjList){
//     int n = sz(adjList);
//     queue<int> q;
//     q.push(start);
//     dist[start] = 0;
//     parent[start] = -1;
//     while (!q.empty()){
//         int u = q.ft();
//         q.pop();
//         for (int v : adjList[u]){
//             if (dist[v] == -1){ // Not visited
//                 dist[v] = dist[u] + 1;
//                 parent[v] = u;
//                 q.push(v);
//             }
//         }
//     }
// }

// vi findTreeDiameter(vvi &adjList){
//     int n = sz(adjList);
//     if (n == 1) return {0};

//     vi parent(n, -1), dist(n, -1);
    
//     // First BFS to find the farthest node from node 0
//     bfs(0, parent, dist, adjList);
//     int farthest = max_element(all(dist)) - dist.begin();
    
//     // Second BFS from the farthest node to get the diameter
//     fill(all(parent), -1);
//     fill(all(dist), -1);
//     bfs(farthest, parent, dist, adjList);
//     int endpoint = max_element(all(dist)) - dist.begin();
    
//     // Retrieve the diameter path
//     vi diameterNodes;
//     for (int v = endpoint; v != -1; v = parent[v]){
//         diameterNodes.pb(v);
//     }
//     reverse(all(diameterNodes));
//     return diameterNodes;
// }


// void solve() {
// 	int n, k, m, q;
//     cin >> n >> q;


//     vvi adjList(n);
//     for (int i=0; i<n-1; i++){
//         int node;
//         cin >> node;
//         node--;
//         adjList[i+1].pb(node);
//         adjList[node].pb(i+1);
//         cout << node << " " << i+1 << endl;
//     }

//     vi diameterNodes = findTreeDiameter(adjList);
//     //printVector(diameterNodes);

//     set<int> diameterSet(all(diameterNodes));

//     vi parent(n, -1), dist(n, -1);
//     queue<int> bfsQueue;

//     // Initialize BFS from all diameter nodes
//     for (int root : diameterNodes) {
//         for (int v : adjList[root]) {
//             if (diameterSet.count(v) == 0 && dist[v] == -1) {
//                 // Only add non-diameter nodes to the BFS queue
//                 bfsQueue.push(v);
//                 dist[v] = 0;
//                 parent[v] = root;
//             }
//         }
//     }

//     // Perform BFS
//     while (!bfsQueue.empty()) {
//         int u = bfsQueue.ft();
//         bfsQueue.pop();

//         for (int v : adjList[u]) {
//             if (dist[v] == -1) { 
//                 dist[v] = dist[u] + 1;
//                 parent[v] = parent[u];  // Keep the original diameter node as ancestor
//                 bfsQueue.push(v);
//             }
//         }
//     }

//     printVector(diameterNodes);
//     printVector(parent);


// }