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

// solve time ~ can't solve
// This is actually such a good problem on gcd. My fav so far.
// I failed to solve this problem because I lacked
// one crucial observation (Observation 3).

// Observation 1: we just need to check if a number i from 1 to max(all(a))
// can be added to the array. I figured this one

// Observation 2: Intead of checking gcd(a[i], a[j]) for each pair
// We instead just need to check multiples of i.
// Why? Because it is obvious that if a[i] || a[j] is not a multiple of i,
// then gcd(a[i], a[j]) != i.
// Like, say i=7, and a[i] =14, a[j] = 3, then obviously the gcd is not 7.
// I figured this one as well.

// Observation 3 (MOST IMPORTANT): The thing about this problem, is that
// when we find gcd(a[i], a[j]) is not in a, we will add it to 
// the array, meaning gcd(a[i], a[j]) is a new element to be considered.
// In other words, we can do something like: gcd(gcd(a[i], a[j]), a[z]). 
// Meaning, lets say we have all the multiples of i in an array b
// then b = [b1, b2, b3, ...]
// we took gcd(b1, b2), but gcd(b1,b2) != i, does that mean we just 
// continue checking gcd(b1, b3)? No! because gcd(b1,b3) can be != i.
// Here's the most important part, gcd(b1,b2) != i
// => gcd(b1, b2) == i * j for some j that is an integer.
// Now, if gcd(b1, b2) is not in the array, we would add it, otherwise its
// in the array already. 
// In both cases, gcd(b1,b2) is present in the array, meaning
// we can actually do gcd(gcd(b1,b2),b3) == i * k, where i*k <= i*j, because
// gcd is a monotonic decreasing function, the more elements you add,
// the lower the gcd becomes, and since all our numbers are multiples
// of i, we can take the gcd of the WHOLE array b (including the new elements
// added to a that are multiples of i) to check if the gcd == i.
// Because if i does exist in the array a, then there MUST EXIST
// 2 pairs of elements that give gcd == i, and these 2 pairs of elements
// DO NOT NECESSARILY come from the original array a, they can come from
// previous operations, but in that case, we would already add them.
// And since gcd is a monotonic decreasing function that gives you 
// the greatest multiple of 2 numbers <= the min of the 2 numbers, we 
// can guarantee to get a number that is some multiple of i which we can
// further use to get the gcd of the other multiples of i in b.
// We keep doing this until gcd(bx, by) = i * k where k == 1 
// => we found a pair, where bx = gcd(gcd(gcd(...))) and by = gcd(gcd(gcd(...)))
// This was the most important observation I missed but once I realised
// this observation the problem became very simple.

void solve() {
	int n, k, m;
    cin >> n;

    vb exist(MAXN, false);
    int maxi = 0;
    for (int i=0; i<n; i++){
        int x;
        cin >> x;
        maxi = max(maxi, x);
        exist[x] = true;
    }

    int ans = 0;
    for (int i=1; i<=maxi; i++){
        int gcd = 0;
        for (int j=i; j<=maxi; j+=i){
            if (exist[j]){ // if j is a multiple of i existing in a
                gcd = __gcd(gcd, j);
            }
        }

        if (gcd == i && !exist[i]){
            ans++;
            exist[i] = true;
        }
    }

    cout << ans << '\n';

}

int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    // int t;
    // cin >> t;
    // while (t--) solve();
    solve();
    return 0;
}
