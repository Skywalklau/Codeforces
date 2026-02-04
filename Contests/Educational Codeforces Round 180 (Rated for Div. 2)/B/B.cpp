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

// can't solve, I really tried...
// When I read the problem, I didn't really have any intuition.
// The first thing that came to my mind was, I think we can use a map.
// We just need to track for each a[i], the indexes of a[i], a[i]-1, a[i]+1.
// then we get the difference of indexes and the min is the answer.
// But I was dead wrong.
// take [3,1,6], my code would give -1.
// Actually, the answer should be 1.
// because [1,6] -> [2 || 3 || 4], then [3,1,6] -> [3,3||2||4] which is 1 move.
// Then I got fucking stuck...
// Yea I failed my observation...
// Turns out, the answer is always going to be at most 1.
// Of course, if (abs(a[i]-a[i-1]) <= 1), then the answer is 0.
// Otherwise, if there is a valid way to get the beautiful array, the answer
// is just 1.
// The condition is that we must have a peak, or a trough.
// eg. [3,1,6], [32,1,6]
// one way for [3,1,6] is -> [3,3]
// one way for [32,1,6] is -> [6,6]
// so we just need to check for either of these 2 conditions, then immediately
// we can just return 1 when we found one.
// otherwise, the answer will just be 0.
// Now, why does this just work? Why can't the answer be >= 2?
// We can prove with contradiction.
// lets say we have [3,7,9,1]
// Obviously there is a peak at [7,9,1]
// so the answer is just 1.
// Now, 2 could've been the answer as well, by [3,7,9,1] -> [3,7,1] -> [3,3]
// But, why would you do that? Its unoptimal, greedily, the moment we see
// a peak/trough we can just immediately return 1 already!
// Otherwise, there is no peak or trough at all, and since we already checked
// no abs(a[i]-a[i-1]) <= 1, then its impossible to make the array beautiful!
// Because this means either:
// 1. the entire array is increasing, and the difference between consecutive element
// is >= 2.
// 2. the entire array is decreasing, and the difference between consecutive element
// is >= 2.
// In both ways, there is no way for us to make the array beautiful!
// Hence we just return -1

void solve() {
	int n, k, m;
    cin >> n;

    vi a(n+1);
    for(int i=0; i<n; i++) cin >> a[i];
	
    for(int i=1; i<n; i++){
		if(abs(a[i]-a[i-1]) <= 1){
			cout << "0" << '\n'; 
            return;
		}
	}
	
    for(int i=1; i<n-1; i++){
		if(a[i] > a[i-1] && a[i] > a[i+1]){
			cout << "1" << '\n';
            return;
		}
		if(a[i] < a[i-1] && a[i] < a[i+1]){
			cout << "1" << '\n';
            return;
		}
	}
	cout << "-1" << '\n';

}


// void solve() {
// 	int n, k, m;
//     cin >> n;

//     vi a(n);
//     map<int, vi> memo;
//     for (int i=0; i<n; i++){
//         cin >> a[i];
//         memo[a[i]].pb(i);
//     }

//     int ans = MAX;
//     for (auto p : memo){
//         for (int idx : p.S){
//             for (int idx2 : memo[p.F]){ // check a[i]
//                 if (idx != idx2){
//                     ans = min(ans, abs(idx - idx2)-1);
//                 }
//             }

//             for (int idx2 : memo[p.F-1]){ // check a[i]-1
//                 ans = min(ans, abs(idx - idx2)-1);
//             }
            
//             for (int idx2 : memo[p.F+1]){ // check a[i]+1
//                 ans = min(ans, abs(idx - idx2)-1);
//             }
//         }
//     }

//     if (ans == MAX) cout << -1 << '\n';
//     else cout << ans << '\n';
    

// }

int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    int t;
    cin >> t;
    while (t--) solve();
    // solve();
    return 0;
}