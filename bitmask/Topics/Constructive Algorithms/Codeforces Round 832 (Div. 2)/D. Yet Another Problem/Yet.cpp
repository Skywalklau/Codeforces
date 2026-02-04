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
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits

// I'll be honest, I had no idea how to solve this problem
// until I read the editorial.
// This problem is a harder version of Bakry and Partioning. Its just that
// we have an additional constraint, that we need to find an ODD length
// subarray such that the XOR on both sides are equal when [l,r] is even.
// Like, if the whole subarray is 0 and [l,r] is even, 
// you MUST select an odd length subarray to split it in 2, 
// such that both subarrays are x so that 
// x^x = 0 = pref[r]^prefXOR[l-1].
// Apart from that, its pretty much the same concept as Bakry and Partioning.

void solve() {
	int n, k, m, q;
    cin >> n >> q;

    vi a(n+1), pxor(n+1), last_nz(n+1, 0), last(n+1, -1);
    // last[i] = leftmost index from index i such that 
    // prefixXOR[i] == prefXOR[last[i]].
    map<int, int> odd, even;

    // Input the array and initialize prefix XOR
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        pxor[i] = pxor[i - 1] ^ a[i];
        last_nz[i] = (a[i] == 0 ? last_nz[i - 1] : i);
    }

    // Precompute `last` using parity-based maps
    for (int i = 1; i <= n; i++){
        if (i % 2 == 1){ // Odd index
            // odd - even = odd
            // so if odd idx, we want the even set that stores even indexes
            // Why? Lets say i == 3,
            // in terms of prefXOR, we can only perform operations on
            // odd length subarrays, so we must look for an even index.
            // because prefXOR[i==3] ^ prefXOR[j==lets say 0] == a[1]^a[2]^a[3]
            // which is odd in length.
            if (even.count(pxor[i])) last[i] = max(last[i], even[pxor[i]]);
            odd[pxor[i]] = i;
        }
        else{ // Even index
            // even - odd = odd
            // so if even idx, we want the odd set that stores odd indexes
            // Why? Lets say i == 8,
            // in terms of prefXOR, we can only perform operations on
            // odd length subarrays, so we must look for an odd index.
            // because prefXOR[i==8] ^ prefXOR[j==lets say 3] == 
            // a[4]^a[5]^a[6]^a[7]^a[8], which is odd in length.
            if (odd.count(pxor[i])) last[i] = max(last[i], odd[pxor[i]]);
            even[pxor[i]] = i;
        }
    }

    // Process each query
    while (q--){
        int l, r;
        cin >> l >> r;

        // XOR check for the subarray
        // for any range [l,r] to have XOR == 0.
        // prefXOR[l-1] ^ pref[r] == 0.
        if ((pxor[r] ^ pxor[l - 1]) != 0){
            cout << -1 << "\n";
            continue;
        }

        
        // Check if all elements in the range are zero
        // => 0 operations needed
        if (last_nz[r] < l){
            cout << 0 << "\n";
            continue;
        }

        // Odd-length subarray
        // => 1 operation needed on [l,r] itself (the whole subarray)
        if ((r - l + 1) % 2 == 1){
            cout << 1 << "\n";
            continue;
        }

        // Check for zero at the endpoints
        // we know its even length, 
        // so if either the left endpoint == 0|| right endpoint == 0, or both.
        // then the answer is 1
        // Why? Because since prefXOR[r] ^ prefXOR[l-1] == 0.
        // if we take out when endpoint that is 0, then the subarray
        // becomes odd and still maintains subarray XOR of 0.
        // say you take out a[l].
        // then the prefXor will still be 0, its now just
        // prefXOR[r] ^ prefXOR[l] ^ a[l] == 0
        // we know that prefXOR[r] ^ prefXOR[l-1] == 0.
        // and since a[l] == 0 => prefXOR[r] ^ prefXOR[l] ^ a[l] == 0.
        // and so a[l] == 0 => no operation needed.
        // prefXOR[r] ^ prefXOR[l] == 0, but the elements are not 0,
        // so we need one operation => 1 operation needed.
        // Similar argument can be made when we remove a[r] if a[r]==0. 
        if (a[l] == 0 || a[r] == 0){
            cout << 1 << "\n";
            continue;
        }

        // Check for valid split
        // Otherwise, if its even and a[l] != 0 and a[r] != 0
        // We need to check if there exist an odd length subarray from r
        // to last[r] where the XOR is 0.
        // and this depends of the parity of r.
        // if r is odd, we want to find an index that is even
        // if r is even, we want to find an index that is odd
        // Why? Because even-odd==odd, odd-even=odd.
        // and this index must exist within [l,r] (obviously).
        if (last[r] >= l){
            cout << 2 << "\n";
            continue;
        }

        // No valid case found
        cout << -1 << "\n";
    }
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
