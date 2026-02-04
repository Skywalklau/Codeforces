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

// solve time ~ 50 mins
// This was quite a fun problem. 
// First, notice that we only get values, we don't remove values.
// So this is a very typically query type problem where we can just
// keep getting more and more elements, and there are only 30 of them.
// So, we don't need any fancy data structure for this, just use a 
// freq array will do to keep track of each bit.
// Now for the GET x part, which is the toughest part, but its actually
// not that bad.
// How do we solve this? The answer is greedy.
// We solve this bit by bit, starting from the MSB (just like almost any
// bitmask problem)
// Then, if the current bit of x is set, then that means we want to 
// find a subset sum that can get this sum of (1 << bit) for this bit
// we are on.
// Obviously, we would not check the available bits at a higher position
// than this current bit because otherwise our sum would exceed (1 << bit)
// So, we check i for all i from bit to 0.
// First of all, we can do this in O(29^2 * m). This still fits within
// 1.5 seconds.
// So, the idea can work.
// Now for the logic, we need to use a current frequency map of bits
// that we used so far, call it used.
// From i=bit to 0, we get freq[i] - used[i], which is the
// remaining count bits we have at this bit position, call it remain.
// If remain * (1 << i) >= target, where target == (1 << bit).
// Then that means we have enough count of values at this bit position  
// to achieve this target sum already.
// So, we would need exactly target / (1 << i) of this i bit, so 
// define need = target / (1 << i), and do used[i] += need because
// we used need amount of bits of this bit i.
// then we can set target == 0, cuz we go the sum of this bit.
// Otherwise, we don't have enough bits to make target == 0 yet, but
// does that mean we just move on to the next lower bit? No!
// Because its always beneficial to use the remaining count of bits 
// at this bit position to contribute to the target even if we don't 
// have enough!
// Hence, we just need to do: 
// target -= remain * (1ll << i);
// used[i] = freq[i]; 
// because we used all occurence of this bit count to contribute to
// our target.
// then we move on to the next lower bit.
// At the end, we will know, if target == 0, then ok we can fulfill
// this currentBit, now we move on to the next bit of x, and repeat again
// the same logic.
// If at any point, target != 0, then ok = 0, meaning we cannot 
// make x with our current count of bits within our multiset.
// And thats the solution.
// Now, why can we just do target -= remain * (1ll << i);
// and also need = target / (1ll << i);
// Its because notice that since everything is in the form of 2^i, for
// all 2^j where j<=i, 2^j | 2^i.
// This is a well known fact.
// In fact, since we did target -= remain * (1ll << i)
// our target could be in the form of 2^i - 2^(i-k1) - 2^(i-k2) - ...
// but because we are going from MSB to LSB, we will always end up
// at the current smallest bit position, call it 2^y.
// And, notice that 2^y | 2^i - 2^(i-k1) - 2^(i-k2) - ... 2^(y+1).
// So, that is why we can safely just divide by 2^y, or (1 << i) since
// we are always going to be at the current smallest bit.
// Really cool math observation needed to solve this greedily.

void solve() {
	int n, k, m;
    cin >> m;
 
    vi freq(30);
    while (m--){
        int q, x;
        cin >> q >> x;
        if (q == 1) freq[x]++;
        else{
            vi used(30);
            int ok = 1;
            for (int bit=29; bit>=0; bit--){
                int currentBit = (x >> bit) & 1;
                if (!currentBit) continue;
                
                ll i = bit, target = 1 << bit;
                bool found = false;
                while (i >= 0 && target != 0){
                    ll remain = freq[i] - used[i];
                    if (remain * (1ll << i) >= target){
                        int need = target / (1ll << i);
                        target = 0;
                        used[i] += need;
                    }
                    else{
                        target -= remain * (1ll << i);
                        used[i] = freq[i];
                    }
                    i--;
                }

                if (target != 0) {ok = 0; break;}
 
            }
 
            cout << (ok ? "YES" : "NO") << '\n';
        }
    }
 
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
