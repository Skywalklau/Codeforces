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

// solve time ~ can't solve.
// Honestly, this was such a good problem.
// This problem was an unconventional way of using Kruskal.
// Instead of sorting edges, we sort the values and check, for each value
// from smallest to largest (like kruskal but for values), if we can
// form an edge of this value a[i] to any nodes from 0 to i-1, and i+1 to
// n-1.

// First of all, we know all neighbor nodes are connected by an edge of 
// weight p. So, if a[i] >= p, there is no point in traversing this edge
// to connect to other nodes anymore.
// Also, note that, to satisfy the 1st condition actually we just check
// if a[j] % a[i] == 0, and if it is true, then we can just add a[i] to 
// ans. Because the idea here is that we first consider all the potential
// edge values to add to other nodes from smallest to biggest in value.

// In other words, we say, for each edge value a[i], we want to find what
// nodes can be connected to this i-th node with an edge weight of a[i]. 
// Also, another thing is that if a node is already connected (i.e
// isConnected[j] = true, then we just break the loop because otherwise
// we would form a cycle)
// Remember, we want to find MST, lets say a <-> b <-> c. If we ignore
// isConnected[b] = true for c, and that c can form a valid edge to a
// with a[c], then the graph would be a <-> b <-> c
//                                    <------------   
// which is a cycle, contradiction because we want MST.    

// Note: gcd(x,y,z,...) = min(x,y,z,...) => min(x,y,z,...) | x,y,z,...
// thats why we can just take the smallest number and check if it divides the other
// nodes because they are connected by the weight of the smallest number.

// Time complexity: O(NLOGN)
// Space complexity: O(N)

void solve() {
	int n, k, m, p;
    cin >> n >> p;
    vi a(n);
    for(int i=0; i<n; i++) cin >> a[i];
    
    vb isConnected(n);
    vpii vals;
    
    for(int i=0; i<n; i++) vals.pb({a[i],i});

    sort(all(vals));
    ll ans = 0;

    // isConnected[i] stores the ith edge, whether it has been replaced
    // by a smaller edge value of < p or not.
    // node i-1 (edge i-1) node i (edge i) node i+1
  
    for(auto x : vals){
        int curVal = x.F;
        int i = x.S;

        if (curVal >= p) break;
        
        while(i > 0){
            if(isConnected[i-1]) break; // because implicitly there was a smaller
            // divisor that divides a[i-1] and so also connects to a[i] itself.
            if(a[i-1] % curVal == 0){
                isConnected[i-1] = true;
                ans += curVal;
                i--;
            }
            else break; // because now gcd(x,y,z,...) < min(x,y,z,...)
        }
        
        i = x.S;
        while(i < n-1){
            if(isConnected[i]) break;
            if(a[i+1] % curVal == 0){
                isConnected[i] = true;
                ans += curVal;
                i++;
            }
            else break; // because now gcd(x,y,z,...) < min(x,y,z,...)
        }
        
    }

    for(int i=0;i<n-1;i++){
        if(!isConnected[i]) ans += p;
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
