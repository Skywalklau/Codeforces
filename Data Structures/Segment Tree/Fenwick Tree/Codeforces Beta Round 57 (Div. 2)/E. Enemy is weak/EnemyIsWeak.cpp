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

const int N = 1e6 + 5; // change according to your needs
vi mn(N, 0); // Smallest prime factor of each number
vvi fcv(N); // Prime factorization for each number (only returns each distinct factor once)


void precompute_prime_factors() { // Modified Sieve
    mn[1] = 1; // Base case: 1 has no prime factors
    for (int i = 2; i < N; i++) {
        if (!mn[i]) { // If i has no prime factor recorded yet, it is a prime number.
            for (int j = 1; j * i < N; ++j) {
                if (!mn[i * j])
                    mn[i * j] = i; // Mark i as the smallest prime factor for all multiples of i.
            }
        }
    }

    // Generate prime factor lists for every number up to N
    for (int i = 1; i < N; i++) {
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

const int LOGN = 20; // sparse table
const int MAXN = 1e6+5; // fenwick

int fenL[MAXN], fenR[MAXN];

void update(int i, int val, int n, int fen[]){
	while (i <= n){
		fen[i] += val;
		i += i & -i;
	}
}

int query(int i, int fen[]){
	int ans = 0;
	while (i > 0){
		ans += fen[i];
		i -= i & -i;
	}
	return ans;
}


// I did not solve this problem, but I learned to familiarise myself with
// fenwick at least...
// I tried finding a[i] then count how many a[j] and a[k] exists
// such that a[i] > a[j] > a[k]
// but the thing is, from right to left (which is what I did)
// I update on the fly each value encountered, but lets say if
// at i there are 4 values < a[i]
// I thought we can just do 4C2...
// But its wrong because a[j] could be < a[k] for some j and k
// Like if a[i] = 6
// [6,4,5,2,1]
// then its not 4C2, because 4 < 5...
// So the idea is to actuall find a[j], then find how many a[i] and a[j]
// exists at this kth position such that a[j] < a[i] and a[j] > a[k].
// We can do this via 2 fenwicks.

void solve() {
    int n, k, m;
    cin >> n;

    vi a(n);
    map<int, int> freq;
    map<int, int> pos;
    for (int& x: a) {
        cin >> x;
        freq[x]++;
    }

    int idx = 1; // fenwick is 1-indexed so start with idx == 1
    for (auto x : freq) pos[x.F] = idx++;

    // Compress values of a to 1 <= a[i] <= n
    for (int& x : a) x = pos[x];

    ll ans = 0;
    ll rightCount[n];
    
    for (int i=n-1; i>=0; i--){
        rightCount[i] = query(a[i]-1, fenR);  // Count how many smaller elements exist to the right of a[i]
        update(a[i], 1, MAXN, fenR);
    }

    for (int i=0; i<n; i++){
        // a[i] > a[j] > a[k], at every a[j]
        // we find how many a[i] exists
        // and with the a[k] precomputed
        // we can just do left * right to get the total count for a[j]
        // such that a[i] > a[j] > a[k];
        ll leftCount = query(MAXN, fenL) - query(a[i], fenL);  // Count how many larger elements exist to the left of a[i]
        // ll rightCount = query(a[i]-1, fenR);
        ans += leftCount * rightCount[i];  // Add the result to the total
        update(a[i], 1, MAXN, fenL);
        // update(a[i], -1, MAXN, fenR);
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