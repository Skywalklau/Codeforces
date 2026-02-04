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
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits

// solve time ~ 20mins
// Nice problem on modulo arithmetic

// Observation 1: elements must be distinct
// Why? Because of there are 2 of the same elements, then 
// gcd(a1+x,a2+x) == a1+x != 1 because x > 0.
// So we can sort the elements and check for duplicates.

// Observation 2: (a[i]+x, a[j]+x) for any i<j<=n cannot be divisible by p>1
// if its divisible by p, then gcd(a[i]+x, a[j]+x) >= p, which is not coprime.
// But what is p? Prime factors.
// Every number >1 can be prime factorized. So, we just need to check divisibility
// of each prime factor for all pairs a[i] and a[j].

// Observation 3: a = x mod p => a = pm + x.
// Every number divided by p will have some remainder k where 0<=k<p.
// We can take advantage of this.
// Notice that, we will have p different remainders if we divide by p.
// Eg. divide 7 => 0,1,2,3,4,5,6 as remainders => 7 different remainders.
// Idea:
// We can divide each mumber by p, add its remainder to a cnt array.
// Then if there is at least on cnt[k] where cnt[k] < 2, we can subtract k
// to all elements in the array and no PAIRS of elements will be divisible 
// by p (except itself, but that is an exception since i<j).
// Eg, [3,6,7] and p==3, then remainders = [k=0: 2, k=1: 1, k=2: 0]
// so we can either add k=1 or k=2 to [3,6,7] and no pairs of elements
// will be divisible by 3.
// Why does this just work? Lets break it down.
// When cnt[k] < 2, this means that 1 or 0 elements in the given array
// share a common remainder k.
// Perhaps it might be confusing why we say subtract k. Here's why:
// In modular arithmetic, lets say the given array is [3,7,10], p=3, then 
// remainders = [k=0: 1, k=1: 2, k=2: 0]. We use contradiction to prove this.
// If we subtract k=1, this also means add k=2, because -1 mod p == p-1 mod p.
// So, we are basically adding k=2, which will make the array [5,9,12], and 
// obviously, (9,12) is a pair divisible by 3, so their gcd(9,12) >= 3,
// at least 3.
// So, thats why we take those that have cnt[k] < 2.
// Lets say now we take k=0, which is the equivalent of taking k=3 (because
// x > 0). Then, adding 3 to all elements gives [6,10,13]. Again, no pair
// of elements are divisible by 3 (except for (6,6) but again, i<j so that
// won't happen).
// In other words, if cnt[k] < 2, then we can subtract k, or in modular
// arithmetic, add (p-k) to all elements, and none will be divisible by p.

// Observation 4: Pigeonhole Principle.
// There remains one final question, since there are a lot of primes up
// to 10^18, we clearly need a point to stop early.
// Notice that, given n numbers, if we reach a prime p > n/2, we will
// always be able to find a slot where cnt[k] < 2 due to the pigeonhole 
// principle.
// Why? Because if p > n/2, then we have > n/2 slots for cnt[k].
// But, we only have n numbers, so even if we greedily fill
// every slot such that cnt[k] == 2, there will always be at least one slot
// with cnt[k] < 2. 
// Hence, we can terminate when p > n/2.

// Time complexity: O(NLOGN + N^2)

void solve() {
	int n, k, m;
    cin >> n;

    vll a(n);
    for (ll &x : a) cin >> x;
    
    sort(all(a));
    for (int i=1; i<n; i++){
        if (a[i-1] == a[i]){
            cout << "NO" << '\n';
            return;
        }
    }
    
    bool found = true;
    for (int p=2; p <= n/2; p++){ //pigeonhole principle
        if (!is_prime(p)) continue;
        vi cnt(p, 0);
        for (int i=0; i<n; i++) cnt[a[i]%p]++;
        if (*min_element(all(cnt)) >= 2) {found = false; break;}
    }

    cout << (found ? "YES" : "NO") << '\n';

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
