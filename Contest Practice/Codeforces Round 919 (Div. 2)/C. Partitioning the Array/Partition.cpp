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

const ll K = 2e+5; // change according to your needs
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

// solve time ~ 1hr 15mins
// I feel quite proud that I managed to solve this.
// Finally a number theory W.
// To put it simply, I took inspiration from integers have friends 
// || maximum modula equality.
// First, notice that they want all such k st. its a divisor of n.
// Meaning, they want all factors of n.
// Then, they split for each factor k, into n/k parts, each of length k.
// Then, what they want is that find some m st. the for each part,
// every element % m is the same throughout all the parts.
// In other words, lets say we have [a,b,c], [x,y,z], [p,o,l]
// then we need to find some m>=2 so that   
// [a % m, b % m, c % m] = [x % m, y % m, z % m] = [p % m, o % m, l % m]
// So, how do we solve this?
// First of all, what does this imply?
// if we look by each index of each array.
// It means a % m = x % m = p % m, same for other indexes 2 and 3.
// which we can just rewrite as (a-x) % m = (x-p) % m.
// So, what does this mean? It means we can just take the gcd of 
// all the differences of each index of each subarray.
// and if the gcd >= 2, then ok valid (for this index of each array).
// This is the same concept as integer have friends || max mod equality
// so this solves the condition for an index of a each array.
// Now, we can proceed with other indexes.
// In the end, we end up with some suitable candidates of divisors.
// [a1,a2,a3].
// Now, notice that, if the gcd is a1 for some index, we can still
// potentially pick a smaller divisor, because this is the greatest
// one.
// So, lets say we have [9,3,6] in the end.
// what does this mean?
// It means, for the index 1, we can use 9 to divide everthing
// so that the remainder is the same. For index 2, we can use 3 and
// for index 3 we can use 6 as the largest divisors.
// But, we want to find an m that divides ALL rows to satisfy the 
// condition.
// So, how do we do this now?
// The answer is just the gcd of these final candidates.
// Why? Because if we know 9 can divide to satisfy the 1st index,
// then 3 can as well, because 3 is a divisor of 9, so whatever 9
// can divide to satisfy the remainder, 3 can as well.
// So, we just take gcd of all the candidates.
// and if the final answer is >= 2, yay this is one valid way 
// to split the array for this particular factor.
// Also, we can get the factor of any n in nlogn time, and loop
// through each factor, we can safely do this without TLE because
// the number of factors for any number is very small compared
// to the value of n.

void solve() {
	int n, k, m;
    cin >> n;
    
    vll a(n);
    for (ll& x: a) cin >> x;

    int ans = 0;
    for (int size : factors[n]){
        // cout << size << endl;
        vll temp;
        for (int i=0; i<size; i++){
            ll g = 0;
            for (int j=i+size; j<n; j+=size){
                // if (size == 2) cout << a[j-size] << " " << a[j] <<  endl;
                ll diff = abs(a[j] - a[j-size]);
                g = gcd(g, diff);
            }
            temp.pb(g);
        }
        
        m = 0;
        for (int i=0; i<sz(temp); i++) m = gcd(m, temp[i]);
        // cout << "m: " << m << endl;
        // printVector(temp);
        // m == 0 => m can be anything
        if (m>=2 || m == 0) ans++;
    }

    cout << ans << '\n';

}

int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    // sieve();
    // precompute_prime_factors(); // modified sieve
    getAllFactors();
    int t;
    cin >> t;
    while (t--) solve();
    // solve();
    return 0;
}
