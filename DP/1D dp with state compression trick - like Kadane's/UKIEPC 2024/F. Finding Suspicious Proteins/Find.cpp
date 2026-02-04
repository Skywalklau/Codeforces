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
using vvld = vector<vector<ld>>;
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

// solve time ~ can't solve
// this was a really good problem.
// I liked it a lot.
// So, how do we solve this problem?
// Actually, its pretty simple. But I couldn't come up with it... Haizzzz...
// First of all, following what they want, naively the time complexity would be
// O(n*l*k(k-1)/2).
// because we need to recalculate all the pairs of sums and then get the min on the
// same loop.
// But, this part can be optimized.
// Instead of recalucalting, we can precompute the min so far for each embedding with
// the k embeddings that we chosen so far.
// let min_dist[i] be the min distance against all k-1 embedding so far.
// then we can do:
// min_dist[i] = min(min_dist[i], D(i,new))
// doing this allows us to update the new min_dist[i] after comparing against the kth
// embedding.
// And thats the solution.
// First, we simulate what they want, we get p1 and p2 like how they want.
// then, we compute min_dist[i] for all unused embeddings with p1 first.
// Then, from the 3rd chosen embedding onwards, we compare each embedding with
// min_dist[i] = min(min_dist[i], D(i,new))
// where new in this case would be emb[p2].
// for the 4th emb, it will be D(i, emb[p3]).
// for the 5th emb, it will be D(i, emb[p4]).
// and so on until our chosen set is of size k.
// D is the getDistance function.
// This way, our time complexity reduces to O(n*l*k),
// which is small enough for 5s.

int getDistance(vi& a, vi& b, int l){
    int ans = 0;
    for (int i=0; i<l; i++) ans += abs(a[i] - b[i]);
    return ans;
}

void solve() {
	int n, l, k;
    cin >> n >> l >> k;
    
    vstr names(n+1);
    vvi emb(n+1, vi(l));

    for (int i=0; i<n; i++){
        cin >> names[i];
        for (int j=0; j<l; j++) cin >> emb[i][j];
    }

    vi min_dist(n, MAX), used(n);
    vi chosen;

    // get p1
    int p1 = -1, mx = -1;
    for (int i=1; i<n; i++){
        int dist = getDistance(emb[0], emb[i], l);
        if (dist > mx){
            mx = dist;
            p1 = i;
        }
    }

    chosen.pb(p1);
    used[p1] = 1;

    // get p2
    int p2 = -1; 
    mx = -1;
    for (int i=0; i<n; i++){
        if (!used[i]){
            int dist = getDistance(emb[p1], emb[i], l);
            if (dist > mx){
                mx = dist;
                p2 = i;
            }
        }
    }

    chosen.pb(p2);
    used[p2] = 1;

    for (int i=0; i<n; i++){
        if (!used[i]){
            int dist = getDistance(emb[p1], emb[i], l);
            min_dist[i] = min(min_dist[i], dist);
        }   
    }

    // round 3 to k
    for (int i=2; i<k; i++){
        int last = chosen.back();
        for (int j=0; j<n; j++){
            if (!used[j]){
                int dist = getDistance(emb[last], emb[j], l);
                min_dist[j] = min(min_dist[j], dist);
            }
        }   

        int p = -1;
        mx = -1;
        for (int j=0; j<n; j++){
            if (!used[j]){
                if (min_dist[j] > mx){
                    mx = min_dist[j];
                    p = j;
                }
            }
        }

        chosen.pb(p);
        used[p] = 1;
    }

    for (int i=0; i<k; i++) cout << names[chosen[i]] << '\n';

}

int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    // sieve();
    // precompute_prime_factors(); // modified sieve
    // int t;
    // cin >> t;
    // while (t--) solve();
    solve();
    return 0;
}
