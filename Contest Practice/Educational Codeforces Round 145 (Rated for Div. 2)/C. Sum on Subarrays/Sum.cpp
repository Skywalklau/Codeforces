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

// solve time ~ 2hrs, yea lets not talk about it...
// This was a fun problem tho. Quite proud to solve this one.
// Idk why the judge was so slow, so I kept slacking halfway while waiting for
// verdict.
// I think its prolly gonna be faster if the judge responds faster, had to wait
// like 15 mins for one reply bruh.
// The trick to solving this problem, is to first play around with some ideas.
// Finding a systematic way to construct the solution.
// We can make some observations tho.
// Notice that no subarray can have a sum of 0.
// Meaning, no 2 consecutive elements can be equal.
// Another thing, if they want some k positive elements, we can construct
// the biggest subarray of postitive elements to get as close to k as possible.
// eg, k = 14 we can do [1,2,3,4] to have 10 ways already.
// The same for negative.
// We can look at which one is bigger, pos or neg.
// if neg then we do this strat for negative numbers, else positive.
// Ok, then for the remainder elements they should just be the opposite sign.
// Now the question becomes how do we get exactly k positive and n*(n-1)/2 - k
// negative.
// We know we have fixed our elements in the form [pos,pos,pos,...,neg,neg] 
// (more positive than negative)
// or [neg,neg,neg,...,pos,pos] (more negative than positive)
// So, What numbers should we assign them?
// The simplest idea I thought of was to just do consecutive numbers.
// so if we need 5 positives, then do
// [5,4,3,2,1,neg,neg,neg...,neg]
// We will find out later that actually [6,5,4,3,2,neg,neg,neg...,neg] is better.
// Then, now that we have [5,4,3,2,1,neg,neg,neg,...,neg]
// What should the negative numbers be?
// Well, we may still not have enough combinations to get k yet, so we can
// use the first neg to adjust how much more we need to add.
// Which is just the prefix sums up to which point we need the sum until.
// Eg, if we have [5,4,3,2,1,neg,neg...,neg]
// and we need 2 more sum of postive to reach k, then we can just do
// 1st neg = 3+2+1+1 and flip sign.
// so it becomes [5,4,3,2,1,-7,-1000,-1000,...]
// implicitly, as long as we dont have a subarray sum of 0, if we have exactly
// k positive, then we have n*(n-1)/2 - k negative sums.
// So, to ensure that, we can just set the rest of neg to -1000.
// But, notice that we can't add the last positive contribution, because
// the 1st neg would have to be -2 for that.
// Eg. [5,4,3,2,1,neg,neg...,neg] and we need 5 more to reach k.
// then, neg = 1+1 then flip = -2, which won't add the last [1,neg] contribution
// So, what we can do is just increase everything by 1.
// so it becomes [6,5,4,3,2,neg,neg,neg...,neg]
// this way our 1st neg can be made to include the last positive if need be.
// which neg will just be -1 in this case.
// eg. [6,5,4,3,2,-1,-1000,-1000....]
// and do the same for negative cnt > positive cnt scenario as well.
// eg. [-6,-5,-4,-3,-2, pos, 1000, 1000, 1000...] if k < n*(n-1)/2 - k
// note that pos != neg because n*(n+1)/2 is odd.
// and thats the solution.

void solve() {
	int n, k, m;
    cin >> n >> k;

    int pos = k;
    int neg = n*(n+1)/2 - k;

    // pos != neg cuz n*(n+1)/2 is always odd
    vi ans;
    if (pos > neg){
        int j = -1;
        for (int i=1; i<=n; i++){
            if (i*(i+1)/2 == pos){
                int x = i;
                for (int j=0; j<i; j++) ans.pb(x--);
                for (int j=0; j<n-i; i++) ans.pb(-1000);
                printVector(ans);
                return;
            }
            else if (i*(i+1)/2 > pos){
                pos -= i*(i-1)/2;
                j = i-1;
                break;
            }
        }

        int x = j+1;
        for (int i=0; i<j; i++) ans.pb(x--);
        ll sum = accumulate(ans.begin() + pos, ans.end(), 0ll);
        ans.pb(-sum-1);

        m = sz(ans);
        for (int p=0; p<n-m; p++) ans.pb(-1000);
        printVector(ans);
    }
    else{
        int j = -1;
        for (int i=1; i<=n; i++){
            if (i*(i+1)/2 == neg){
                int x = i;
                for (int j=0; j<i; j++) ans.pb(-x--);
                for (int j=0; j<n-i; i++) ans.pb(1000);
                printVector(ans);
                return;
            }
            else if (i*(i+1)/2 > neg){
                neg -= i*(i-1)/2;
                j = i-1;
                break;
            }
        }

        int x = j+1;
        for (int i=0; i<j; i++) ans.pb(-x--);
        ll sum = accumulate(ans.begin() + neg, ans.end(), 0ll);
        ans.pb(-sum+1);

        m = sz(ans);
        for (int p=0; p<n-m; p++) ans.pb(1000);
        printVector(ans);
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
