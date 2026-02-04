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

// solve time ~ can't solve.
// Cool problem, learned a new trick from this problem.
// Yea I wouldn't know how to do this without knowing this trick tbh.
// We need to first notice that we exclude for, essentially we are removing 4 away from
// our number system, which means we are actually counting in base 9 (0-8) instead of 
// base 10 (0-9). Then, we can map the numbers from (0-8) to the numbers we want.
// Since we only want to exclude 4, essentially all the numbers >= 4 will be +1.
// So, in terms of our mapping, it will look like:
// [0,1,2,3,5,6,7,8,9]
// Notice that for i>=4 onwards, our mapping is i+1 instead of i, this is to account for
// skipping 4.
// But, this is more simplified, what if lets say we wanna exclude 3,4,5 (base 7)?
// Look below for the code, in fact, we can even account for gaps, what if we wanna exclude
// 3,7,8 (base 7)? We can do the same thing with mapping.
// For excluding 3,4,5, it will look like [0,1,2,6,7,8,9]
// for exluding 3,7,8, it will look like [0,1,2,4,5,6,9]
// Then, once we have the map, we can just % base system, and extract the digit, 
// and map it to our map.
// then divide k by the base system we are on.
// Ofc, we do base*10 each time because we wanna go to next digit of our final number.
// Repeat until k <= 0.

ll toLiving(ll k){
    ll res = 0, base = 1;
    while (k > 0){
        int digit = k % 9;
        if (digit >= 4) digit++; // skip the '4'
        res += digit * base;
        base *= 10;
        k /= 9;
    }
    return res;
}

void solve() {
	ll n, k, m;
    cin >> k;

    cout << toLiving(k) << '\n';

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

// // Returns the k-th "safe" number (1-indexed) that avoids all digits in `banned`
// long long getSafeNumber(long long k, const vector<int>& banned) {
//     // Step 1: build list of allowed digits
//     vector<int> allowed;
//     for (int d = 0; d <= 9; ++d)
//         if (find(banned.begin(), banned.end(), d) == banned.end())
//             allowed.push_back(d);

//     int base = allowed.size(); // effective base after banning digits
//     long long res = 0, mult = 1;

//     // Step 2: convert to base-(allowed.size())
//     while (k > 0) {
//         int digit = k % base;
//         k /= base;

//         // Step 3: map base digit to allowed decimal digit
//         res += 1LL * allowed[digit] * mult;
//         mult *= 10;
//     }

//     return res;
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int t;
//     cin >> t;
//     while (t--) {
//         long long k;
//         cin >> k;
//         // Example: living sequence (ban digit 4)
//         vector<int> banned = {4};
//         cout << getSafeNumber(k, banned) << "\n";
//     }
// }


// higher base:
// converts k (1-indexed) into the allowed symbol system
// string getSafeNumber(long long k, const vector<char>& allowed) {
//     int base = allowed.size();
//     string res;
//     while (k > 0) {
//         int digit = k % base;
//         k /= base;
//         res.push_back(allowed[digit]);
//     }
//     reverse(res.begin(), res.end());
//     return res;
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     // Example 2: base 12 using 0–9, A, B
//     vector<char> allowed2;
//     for (char c = '0'; c <= '9'; ++c) allowed2.push_back(c);
//     allowed2.push_back('A');
//     allowed2.push_back('B');

//     cout << "Base-12: " << getSafeNumber(12345, allowed2) << "\n";
// }