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
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits

// solve time ~ 1 hr 7 mins
// Nice problem, we can solve this with greedy.
// Lets make some observations.
// First of all, what is the valid range of values of m that we can 
// reach for some n?
// The answer is n <= m <= 1/2(n)(n+1).
// Proof: m >= n.
// Pigeonhole principle, you got n nodes, the min sum you can achieve
// is n (all nodes are rooted to 1).
// So, if m < n, its impossible.
// Proof: m <= 1/2(n)(n+1)
// We root at n, then connect n-1 to n, n-2 to n-1, n-3 to n-2 and so
// on.
// This way, our sum is maximised, and the total sum is 1/2(n)(n+1).
// It is impossible to ahchieve more than 1/2(n)(n+1) because
// the moment we add another node to root node, which is n, our sum
// will always be less than n already.
// Hence, n <= m <= 1/2(n)(n+1).
// Now, we aim to prove that we can reach all sums within this range.
// Which yes, we can. But how?
// The trick is greedy + pigeonhole principle.
// The idea is simple, we have n nodes, and sum of m.
// We can simply just do m-(n-1) to see if its <= n.
// if it is, we root m-(n-1), and connect this node with 1, and connect
// all other nodes to 1.
// If m-(n-1) > n, then we can safely just root n, and move on to 
// the next largest node, which is n-1, and repeat the same scenario.
// In other words, we go down, from node n to 1 with this condition.
// Then, the moment m-(i-1) <= i, then we found the final node, note it.
// Then, the solution is just go from root to this final node, then
// connect 1 to this final node, and then connect all the remaining 
// nodes to 1.
// Why does this work? Because by pigeonhole principle, if I have n
// nodes, then I have n-1 children after connecting this nth node.
// So, if our remaining m is smaller than the number of children,
// we can simply just use 1 units to cover the remainder of m, which
// we can use node 1 for this so all other nodes connecting to node 1
// will have d(v) = 1 as well.
// And thats the idea.
// In terms of the graph visually, its going to be a bamboo from m to 
// some stopNode, and the finalNode connects to stopNode and finalNode
// connects to 1, then the remaining nodes all connect to 1.
// So, its like a bamboo from m until 1, then star graph at 1 
// (if possible).

void solve() {
	ll n, k, m;
    cin >> n >> m;

    if (m < n || m > n*(n+1)/2) {cout << -1 << '\n'; return;}

    int root = -1, finalNode = -1, stopNode = -1;
    for (int i=n; i>=1; i--){
        if (m - (i-1) <= i){
            stopNode = i; // last node before we connect with finalNode
            finalNode = m - (i-1); // we connect 1 with finalNode
            break;
        }
        else {m-=i; root = n;}
    }

    if (root == n){ // m is the root
        // cout << stopNode << endl;
        cout << root << '\n';
        for (int i=n; i-1>stopNode; i--){
            cout << i << " " << i-1 << '\n';
        }
        cout << stopNode+1 << " " << finalNode << '\n';
        cout << finalNode << " " << 1 << '\n';
        for (int i=stopNode; i>=2; i--){
            if (i == finalNode) continue;
            cout << 1 << " " <<  i << '\n';
        }
        
    }
    else{ // finalNode is the root
        cout << finalNode << '\n';
        if (finalNode != 1){
            cout << finalNode << " " << 1 << '\n';
        }
        for (int i=n; i>=1; i--){
            if (i == finalNode || i == 1) continue;
            cout << 1 << " " << i << '\n';
        }
    }




}

int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    // sieve();
    // precompute_prime_factors(); // modified sieve
    int t;
    cin >> t;
    while (t--) solve();
    // solve();
    return 0;
}
