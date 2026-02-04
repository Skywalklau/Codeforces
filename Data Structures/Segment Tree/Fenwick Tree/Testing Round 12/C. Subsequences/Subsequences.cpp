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
 
ll binpow_by_mod(ll a, ll b, ll mod){
	ll ans = 1;
	while (b) {
		if ((b & 1) == 1) {
			ans *= a;
			ans %= mod;
		}
		b >>= 1;
		a *= a;
		a %= mod;
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


const int MAXN = 100005;
const int MAXK = 12;

// NOTE: THIS ALSO WORKS IF a[i] are NOT distinct!
// NOTE: IF a[i] > n, then just compress into n

ll tree[MAXK][MAXN]; // Fenwick Tree for each "k"

void update(int k, int idx, ll val, int n){
    while (idx <= n) {
        tree[k][idx] += val;
        idx += (idx & -idx);
    }
}

ll query(int k, int idx){
    ll sum = 0;
    while (idx > 0){
        sum += tree[k][idx];
        idx -= (idx & -idx);
    }
    return sum;
}

// I have written the code for the default O(K*N^2) solution, which is too slow.
// Using fenwick, the code run at O(K*N*logN)
// This is an introduction to dp via fenwick.
// essentially its just the same usual dp, but with fenwick we can do things 
// faster.

void solve() {
    int n, m, k;
    cin >> n >> k;

    vi a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // Dynamic Programming via Fenwick Trees (like on the fenwick tree itself!)
    for (int i = 0; i < n; i++){
        update(1, a[i], 1, n); // Update for subsequences of length 1 
        // => dp[1][a[i]] = 1; , yes its a[i] not i.
        for (int j = 2; j <= k + 1; j++){
            // get all the counts of subsequences of length j-1 such that 
            // its current elemtent is less than a[i].
            ll sum = query(j - 1, a[i] - 1); // Sum of all valid subsequences ending < a[i]
            update(j, a[i], sum, n);         // Update subsequences of length "j"
        }
    }

    // Final answer is the number of valid subsequences of length k+1
    cout << query(k + 1, n) << '\n';
}

int main() {
    fast_io();
    // int t;
    // cin >> t;
    // while (t--) solve();
    solve();
    return 0;
}

// Below is the solution in K * N^2, which is too slow.

// #include <bits/stdc++.h>
// using namespace std;

// using ll = long long;
// const int N = 100005;

// int n, k;
// int a[N];
// ll dp[N][11]; // dp[i][j]: number of subsequences of length j ending at index i

// void solve() {
//     cin >> n >> k;
//     for (int i = 0; i < n; ++i) {
//         cin >> a[i];
//     }

//     // Initialize dp array
//     memset(dp, 0, sizeof(dp));

//     // Base case: Subsequences of length 1
//     for (int i = 0; i < n; ++i) {
//         dp[i][1] = 1;
//     }

//     // Fill the DP table
//     for (int j = 2; j <= k+1; ++j) {        // Length of subsequence
//         for (int i = 0; i < n; ++i) {    // Ending at index i
//             for (int p = 0; p < i; ++p) { // Check all previous indices
//                 if (a[p] < a[i]) {        // Strictly increasing condition
//                     dp[i][j] += dp[p][j - 1];
//                 }
//             }
//         }
//     }

//     // Compute the result
//     ll result = 0;
//     for (int i = 0; i < n; ++i) {
//         result += dp[i][k+1];
//     }

//     cout << result << '\n';
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     solve();
//     return 0;
// }
