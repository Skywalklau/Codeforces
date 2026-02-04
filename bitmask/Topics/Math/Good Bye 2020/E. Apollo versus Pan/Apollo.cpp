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
const int MAXN = 1e6+5; // fenwick = N, trie  = N * number of bits

// Explanation for this problem is in my coding sketchbook.
// Too mathematical, I can't really write this in text.
// But I will try my best to explain without math.
// Nontheless a good problem, and I learned a new trick for swapping summations
// We can swap because notice that when x_j is fixed, the 2 conditions
// becomes independent from each other.
// and so it becomes just looking at the summation of (x_i && x_j) * summation
// of (x_j || x_k) for each fixed x_j.
// ok. This makes things simple now, we can now look at this problem bit by bit

// for any i-th bit, if the x_j element has the i-th bit set, then:
// the summation (x_i && x_j) will be 1 when x_i is 1, because only 1 && 1 = 1.
// So we just need to count the number of x_i that have 1 set at this bit position
// and so the AndSum = countOnes[at this bit position] * bitValue
// where bitValue = (1 << bit position)
// the summation (x_j || x_k) will always just be adding all the elements since
// x_j is 1, so regardless of whether the bit in x_k is set or unset it will
// still be 1.
// so OrSum = n * bitValue.
// where bitValue = (1 << bit position)

// now for the case when bit is unset for x_j.
// in this case:
// summation (x_i && x_j) will never be 1 for any pair.
// because x_j is unset.
// summation (x_j || x_k) will depend on the the count of ones in this bit position
// because only x_j=0 || x_k=1 = 1.
// so OrSum = countOnes[at this bit position] * bitValue
// where bitValue = (1 << bit position)
// then finally, we can add either one of these scenarios for either when
// x_j is set or unset at this bit position to our answer.
// ans += AndSum * OrSum.
// We then do this for every bit for each element.
// Notice that the countOfOnes for each bit position can also be precomputed.

void solve() {
	int n, k, m;
    cin >> n;

    vll a(n);
    for (ll& x: a) cin >> x;

    ll result = 0;

    // Precompute count of ones for each bit
    vll countOnes(60, 0);
    for (ll x : a) {
        for (int c = 0; c < 60; c++){
            if (x & (1LL << c)) countOnes[c]++;
        }
    }

    // Iterate over each element as x_j
    for (ll xj : a){
        ll sumAND = 0, sumOR = 0;

        // Calculate SumAND and SumOR
        for (int c = 0; c < 60; c++){
            ll bitValue = (1LL << c) % MOD;

            if (xj & (1LL << c)){
                // Contribution to SumAND
                sumAND = (sumAND + countOnes[c] * bitValue) % MOD;

                // Contribution to SumOR
                sumOR = (sumOR + n * bitValue % MOD) % MOD;
            } 
            else{
                // Contribution to SumOR
                sumOR = (sumOR + countOnes[c] * bitValue) % MOD;
            }
        }

        // Add contribution of x_j to result
        result = (result + sumAND * sumOR % MOD) % MOD;
    }

    cout << result << '\n';
}


int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
