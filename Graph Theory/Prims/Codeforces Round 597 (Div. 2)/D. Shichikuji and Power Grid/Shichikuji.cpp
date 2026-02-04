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
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits

// Couldn't solve, but I learned a new trick!
// We can add an arbitrary node to represent each c[i].
// I had a hunch it was MST, but what kept cofusing me was how to deal
// with the 2 choices of connections...
// Turns out, we can create a an arbitrary node, and connect each node
// to that node with c[i]. Then now our graph can be a clique, where
// we can do MST via prims because this is a dense graph.
// Introduction to prims.
// The idea is that we keep looping for n times, each time we will add a new
// node to our connection to the MST.
// We check, what is the current node that gives us the minimum cost so 
// far (done in a for loop)
// then, we can add this cost to our ans.
// after that, we loop again, this time we update each cost for unvisited
// nodes to this node that we found that is the cheapest costing node.
// We update our new costs and compare if the current costs is more expensive
// then we update it to a cheaper cost.
// We repeat this for n times, then we can get the MST.

void solve() {
	int n, m;
    cin >> n;

    vi x(n), y(n);
    for (int i=0; i<n; i++) cin >> x[i] >> y[i];
    
    vi c(n), k(n);
    for (int i=0; i<n; i++) cin >> c[i]; 
    for (int i=0; i<n; i++) cin >> k[i]; 
    
    vi parent(n, -1);
    vi cost(n, MAX);
    vb visited(n);

    // initialize everything to the arbitrary node first, indicating build
    // power grid.
    for(int i=0; i<n; i++){
        cost[i] = c[i];
        parent[i] = n;
    }

    ll ans = 0;
    vi v;
    vpii e;

    for (int _=0; _<n; _++){
        int node = -1;
        for(int i=0; i<n; i++){
            if (!visited[i] && (node == -1 || cost[node] > cost[i]))
            node = i;
        }
        
        if (parent[node] == n) v.pb(node+1);
        else e.pb(mp(node+1, parent[node]+1));
        ans += cost[node];
        
        visited[node] = true;
        for(int i=0; i<n; i++){
            if (!visited[i]){
                ll newCost = (k[node] + k[i]) * 1LL * (abs(x[node] - x[i]) + abs(y[node] - y[i]));
                if (newCost < cost[i]){
                    cost[i] = newCost;
                    parent[i] = node;
                }
            }
        }   
    }

    cout << ans << '\n';
    cout << sz(v) << '\n';
    printVector(v);
    cout << sz(e) << '\n';
    for (auto it : e) cout << it.F << " " << it.S << '\n';

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

// Kruskall
// class DSU{
//     vector<int> parent , sz;
// public:
//     DSU (int n){
//         parent.assign(n , 0);
//         iota(parent.begin() , parent.end() , 0);
//         sz.assign(n , 1);
//     }
 
//     int getRoot(int x){
//         if(parent[x] == x){
//             return x;
//         }
//         parent[x] = getRoot(parent[x]);
//         return parent[x];
//     }
 
//     bool merge(int x , int y){
//         x = getRoot(x);
//         y = getRoot(y);
//         if(x == y)  return false;
//         if(sz[x] < sz[y])   swap(x , y);
//         parent[y] = x;
//         sz[x] += sz[y];
//         return true;
//     }
// };
 
// void minimumCost(int N , vector<int> x , vector<int> y , vector<int> c , vector<int> k){
//     vector<array<int,3>> edges;
//     for(int i = 0 ; i < N ; ++i){
//         for(int j = i + 1 ; j < N ; ++j){
//             int cost = (abs(x[i] - x[j]) + abs(y[i] - y[j]))  * 1LL * (k[i] + k[j]);
//             edges.push_back({cost , i , j});
//         }
//     }
 
//     for(int i = 0 ; i < N ; i++){
//         edges.push_back({c[i] , i , N});
//     }
 
//     sortall(edges);
//     DSU graph(N + 1);
//     int total_Cost = 0;
//     vector<int> powerStation;
//     vector<array<int,2>> addedEdges;
//     for(auto [cost , u , v] : edges){
//         if(graph.merge(u , v)){
//             total_Cost += cost;
//             if(v ==  N){
//                 powerStation.push_back(u + 1);
//             }
//             else{
//                 addedEdges.push_back({u + 1 , v + 1});
//             }
//         }
//     }
 
//     cout << total_Cost << nl;
//     cout << powerStation.size() << nl;
//     for(int x : powerStation){
//         cout << x << ' ';
//     }
 
//     cout << nl;
//     cout << addedEdges.size() << nl;
//     for(auto [x , y] : addedEdges){
//         cout << x << ' ' << y << nl;
//     }
// }