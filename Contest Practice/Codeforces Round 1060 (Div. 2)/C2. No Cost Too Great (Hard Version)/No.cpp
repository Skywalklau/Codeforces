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

const ll K = 2e5+5; // change according to your needs
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
// I was so close with this one honestly 
// 2000 rated btw, so I'm not that pissed off that I can't solve it.
// We need to notice a couple of things.
// Case 1: By default there exists 2 numbers that have gcd > 1.
// We can do this easily by getting the count of all the prime factors of each a[i]
// and if any of the primes factors have a cnt >= 2 then we found a solution, hence the
// ans is 0.
// Case 2: No pairs have gcd > 1.
// So, what does this mean?
// Notice a very important observation, since gcd == 1 for all numbers, then all numbers
// are pairwise coprime.
// So, what is upper bound for the number of moves needed to make gcd >= 2?
// 2 moves.
// We can always just take 2 odds and then make them even, then gcd >= 2.
// And since we want the lowest cost, we can just take the first 2 lowest cost elements.
// so ans is at most b[0] + b[1], (after sorting b).
// But, this is not always the case.
// Because we know that since its all pairwise coprime, its either:
// 1. all numbers odd
// 2. 1 even, rest are odd.
// So, sometimes we just need 1 move cuz we can make 1 odd to even then we have 2 even.
// Now, we set our answer to b[0] + b[1], but an edge case is that either a[0] or a[1]
// is even, so actually it might be just b[0] or b[1] only.
// However, thats not the only case we need to check.
// Again, an upper bound is always b[0] + b[1], and this always guarantees we have gcd>=2.
// But, we need to know that we can also try a[1] to a[n] onwards, and adding them
// by 1 or 2 and checking their prime factors. 
// Why? Because it could be the case that b[i] < b[0] + b[1] for some i >= 1.
// Notice that we only need to add them once or twice, because 2b[i] >= b[0] + b[1] 
// already for i>=1, but 3b[i] < b[0] + b[1].
// So, there is no point in checking further after 2 moves.
// However, notice a special case, that is a[0], since we can actually
// keep increasing a[0] by x times until we find a prime factor to it for some other
// a[i] for i>=1.
// So, the last check if to find if a[0] can be added by x times to get a gcd >= 2
// with some other number.
// How do we do this?
// The naive way is to loop until we find a factor, starting from a[0], then a[0]+1,
// then a[0]+2 and so on.
// But that is too slow.
// What we can do, which is genius, is to just get all the prime factors of all 
// numbers except a[0].
// then we can just do ll times = y - (a[0] % y);
// we times tell us how many times we need to add until we get a prime factor to some
// a[i] for i>=1 with gcd >= 2.
// and if times == y, then that means we don't need to add anything at all, so times=0.
// then we can do ans = min(ans, times * b[0])
// and thats the solution.

void solve() {
	int n, k, m;
    cin >> n;

    vpll c(n);
    for (int i=0; i<n; i++){
        ll x;
        cin >> x;
        c[i].S = x;
    }
    for (int i=0; i<n; i++){
        ll x;
        cin >> x;
        c[i].F = x;
    }

    sort(all(c));
    ll ans = c[0].F + c[1].F;
    map<int, int> cnt;
    for (int i=0; i<n; i++){
        for (int x : fcv[c[i].S]){
            if (cnt[x] > 0) ans = 0;
            cnt[x]++;
        }
    }

    for (int i=0; i<n; i++){
        for (ll x : fcv[c[i].S]) cnt[x]--;

        for (ll x : fcv[c[i].S + 1]){
            if (cnt[x] > 0) ans = min(ans, c[i].F);
        }

        for (ll x : fcv[c[i].S + 2]){
            if (cnt[x] > 0) ans = min(ans, 2*c[i].F);
        }

        for (ll x : fcv[c[i].S]) cnt[x]++;
    }

    vll check;
    for (int i=1; i<n; i++){
        for (ll x : fcv[c[i].S]) check.pb(x);
    }

    for (ll x : check){
        ll times = x - (c[0].S % x);
        if (times == x) times = 0;

        ans = min(1LL * ans, 1LL * times * c[0].F);
    }

    cout << ans << "\n";

}

int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    // sieve();
    precompute_prime_factors(); // modified sieve
    int t;
    cin >> t;
    while (t--) solve();
    // solve();
    return 0;
}
