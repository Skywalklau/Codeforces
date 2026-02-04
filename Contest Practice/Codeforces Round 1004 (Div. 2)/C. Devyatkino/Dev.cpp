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

// Can't fucking solve this. HOLY SHIT I WOULD DO SO BAD IN THIS CONTEST.
// So, the trick here is to notice SEVERAL things (I couldn't notice any).
// Observation 1:
// We only need at most 9 operations to make the last digit 7.
// Proof:
// Consider some random number, say 16.
// for the digit 7 to exist after adding some 9, we will keep adding 9 
// 16 + 9 = 25
// 25 + 9 = 34
// 34 + 9 = 43
// 43 + 9 = 52
// 43 + 9 = 61
// 61 + 9 = 70 (actually just at most 7 operations if we allow any digit to be 7)
// 70 + 9 = 79
// 79 + 9 = 88
// 88 + 9 = 97
// Notice something?
// look at the last digit, it goes from:
// 6 -> 5 -> 4 -> 3 -> 2 -> 1 -> 0 -> 9 -> 8 -> 7
// In fact, we break this down even further, we actually only need at most
// 7 operations (note that this only works for n>=7, for n=5,6 we need 8 moves)
// But n>=7, so our trick works!
// Observation 2:
// Ok, we know we need at most 7 operations, but what numbers of 9 do we add?
// it can be 99, 9, 999, 99999999, 99999 and so on...
// Actually, we can break this down even further.
// Instead of adding 99, 9, 9999 and so on, we can do add 10^a-1.
// Also, we know we need at most 7 moves.
// so for k=0 to 7, we can make our number into num = n-k.
// then consider num.
// So, now the question becomes very simple because now lets say our 
// num = 42143135, and lets say k is 5
// So, the question becomes, can I add 10^x at some position of num
// to make the digit at the xth position into 7 in <= k moves?
// We can iterate through the each digit in num, and check the distance
// from this digit to 7, which is just (17 - digit) % 10.
// if the number of moves is <= k, then we found our answer!
// and we can just return immediately, because we are looping from k=0 to 7
// so the lower the better when we found the answer (its just greedy).
// Eg. n = 90, k = 3.
// so num = 87.
// the distance for 7 to 7 is 0, which is <= k==3, so we know we just need
// k=3 moves, and this is the minimum answer. 

// NOTE: its <= k, otherwise our algo would not work.
// you might say, why not == k? Because there is an edge case, 
// we cannot add 10^0-1, which is 0, we start adding from 10^x-1 onwards
// for x>=1.
// So in order to satisfy the condition, we need to check if its <=k
// for the last digit.
// For the rest, it should be ==k.
// so we can just write <=k.

void solve() {
	int n, k, m;
    cin >> n;
    
    ll ans = 1e9;
    for (int k = 0; k <= 9 && ans == 1e9; k++) {
        ll n2 = n - k;
        while (true){
            int digit = (n2 % 10);
            if ((17 - digit) % 10 <= k){
                ans = k;
                break;
            }
 
            if (n2 == 0) break;
            n2 /= 10;
        }
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
