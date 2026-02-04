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
// Honestly I tried, I was somewhat in the ballpark of getting the solution, just couldn't pinpoint it.
// Note to self: when it comes to game problems, a good idea for optimal play is to follow what
// the opponent did in the last round.
// We need to make some observations:
// Alice's goal is to always ensure she picks an even number of odds (0 included).
// Bob's goal is to try to force Alice to pick the last odd number so that her final sum is odd.
// From here, we further deduce more observations:
// let x = number of odds, y = number of evens.
// First, notice that taking an even number will never change the parity of Alice's sum.
// Only odd will change the parity. So, focus on the odd numbers.
// We need to make some observations:
// Notice that x == 2 => Alice always loses.
// Bob has a winning strategy: Always choose the number that Alice chooses in her last move. 
// This strategy keeps the invariant that Alice and Bob have the same number of odds after Bob's 
// each move. The only exception that Bob cannot go on with this strategy is that Alice takes the 
// last even. In this case, there must be an even number of odds (and no evens) remaining. 
// Therefore, each of Alice and Bob will choose half of the remaining odds. At last, Alice and Bob 
// have the same number of odds: x/2, which is sums ot an odd number, hence Alice loses.
// From here, we can deduce that generally, its x % 4 == 2 => Alice loses because as mentioned above,
// following this strat for Bob means we require an even number of odds, but not just that we also need
// to ensure that x/2 is odd, hence the stronger condition is x % 4 == 2.
// Now that we have x % 4 == 2, it makes sense to try x % 4 == 0, 1, 3.
// x % 4 == 3:
// Alice has a winning strategy: Choose odd first. After this move, the game is reduced to y evens and
// x-1 odds with Bob taking the first turn and Bob wins if he has an even number of odds at last. 
// This reduced game is indeed the case of x % 4 == 2 which we have already proved that Bob always 
// loses. Hence Alice always wins, i.e Alice just needs to follow Bob since (x-1) is even, so by 
// following Bob, both Alice and Bob will receive (x-1)/2 odds, +1 on top of Alice's first move, which
// will make her final sum even.
// x % 4 == 0:
// Alice has a winning strategy: Choose even first; after that, choose the number that Bob chooses in 
// his last move. This strategy keeps the invariant that Alice and Bob have the same number of odds 
// after Alice's each move. The only exception that Alice cannot go on with this strategy is that 
// there is no even. In this case, there must be an even number of odds (and no evens) remaining. 
// Therefore, each of Alice and Bob will choose half of the remaining odds. At last, Alice and Bob 
// have the same number of odds: x/2, which is sums to an even number. Hence Alice wins.
// x % 4 == 1:
// If any of Alice and Bob chooses the first odd, the game is reduced to y evens and x−1 odds 
// with its opponent moving first, resulting in the case of x % 4 == 0 and its opponent wins. 
// Therefore, the one who chooses the first 1 loses. 
// With this observation, Alice will lose if there are an even number of evens.
// i.e., y % 2 == 0
// Alice will win if y % 2 == 1
// this can be also deduced to x % 4 == 1 && n % 2 == 0 : Alice wins else Bob wins.

void solve() {
	int n, k, m;
    cin >> n;

    vll a(n);
    for (ll& x: a) cin >> x;

    int odd = 0;
    for (int i=0; i<n; i++){
        if (a[i] & 1) odd++;
    }

    if (odd % 4 == 0 || odd % 4 == 3 || (odd % 4 == 1 && n % 2 == 0)) cout << "Alice" << '\n';
    else cout << "Bob" << '\n';

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
