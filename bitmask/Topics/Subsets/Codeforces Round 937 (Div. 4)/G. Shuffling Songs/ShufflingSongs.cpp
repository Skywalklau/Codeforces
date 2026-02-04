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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vstr = vector<str>;
using vpii = vector<pair<int, int>>;
using vpstrstr = vector<pair<str, str>>;
using vpvivi = vector<pair<vector<int>,vector<int>>>;

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

// My attempt, which was wrong.
// void solve() {
// 	int n, k, m;
//     cin >> n;
 
//     int genreIdx = 0;
//     int artistIdx = 0;
//     umap<str, int> genreMap;
//     umap<str, int> artistMap;
//     vpii songs(n);
 
//     for (int i=0; i<n; i++){
//         str genre, artist;
//         cin >> genre >> artist;
//         if (genreMap.find(genre) == genreMap.end()){
//             genreMap[genre] = genreIdx;
//             genreIdx++;
//         }
//         if (artistMap.find(artist) == artistMap.end()){
//             artistMap[artist] = artistIdx;
//             artistIdx++;
//         }
 
//         songs[i].F = 1 << genreMap[genre];
//         songs[i].S = 1 << artistMap[artist];
//     }
 
//     vi dp(1<<n, -1);
//     for (int i=0; i<n; i++) dp[1 << i] = 1;
 
//     for (int mask = 0; mask < (1 << n); mask++){
//         if (dp[mask] == -1) continue; // skip invalid states
//         for (int i=0; i<n; i++){
//             if ((mask & (1 << i))) continue;
//             for (int j=0; j<n; j++){
//                 if (!(mask & (1 << j))) continue;
//                 if ((songs[i].F & songs[j].F) || (songs[i].S & songs[j].S)){
//                     dp[mask | (1 << i)] = max(dp[mask | (1 << i)], dp[mask] + 1);
//                 }
//             }
//         }
//     }
 
//     cout << n - *max_element(all(dp)) << '\n';
// }


// What I learned from this problem:
// In problems where the compatibility of adding a new element depends on the 
// "last chosen" element, you typically need to track that explicitly. 
// Without this, your code could not handle the "history" of transitions accurately.
// Why? Since each consecutive element is dependent on one another
// let say you have pop taylor, rap taylor, and rap eminem
// so far this subset is correct
// however, since we don't know which is the last element chosen
// lets say our next element is pop kanye
// this song can only pair with pop taylor, not rap taylor || rap eminem
// but because I did not explicity handle this case to exclude rap taylor && rap eminem
// our dp implicitly handles some invalid subsets (I will include just some invalid ones):
// [rap taylor, rap eminem, pop kanye, pop taylor]
// [rap taylor, pop kanye, rap eminem, pop taylor]
// [pop kanye, rap taylor, rap eminem, pop taylor]
// and more...

// When 2D DP is Necessary
// The key distinction is state representation:

// If transitions depend on the last element, you typically need an additional dimension 
// to explicitly track it. This is where dp[mask][last] becomes useful.
// In my case, the compatibility of adding song j depends on the last song added, so 
// tracking this dimension avoids ambiguity.

void solve() {
    int n;
    cin >> n;

    int genreIdx = 0, artistIdx = 0;
    map<str, int> genreMap, artistMap;
    vpii songs(n);

    for (int i = 0; i < n; i++){
        str genre, artist;
        cin >> genre >> artist;

        if (genreMap.find(genre) == genreMap.end()){
            genreMap[genre] = genreIdx++;
        }
        if (artistMap.find(artist) == artistMap.end()){
            artistMap[artist] = artistIdx++;
        }

        songs[i].F = genreMap[genre];
        songs[i].S = artistMap[artist];
    }

    // dp[mask][last]: maximum size of a valid subset ending with song `last`
    vvi dp(1 << n, vi(n, -1));

    // base case: each song can form an exciting playlist
    for (int i = 0; i < n; i++) dp[1 << i][i] = 1;

    for (int mask = 0; mask < (1 << n); mask++){
        for (int last = 0; last < n; last++){
            if (dp[mask][last] == -1) continue; // Skip invalid states
            if (!(mask & (1 << last))) continue; // the last song must be in the playlist 
            for (int next = 0; next < n; next++){
                if (mask & (1 << next)) continue; // Skip already used songs
                if (songs[last].F == songs[next].F || songs[last].S == songs[next].S){
                    dp[mask | (1 << next)][next] = max(dp[mask | (1 << next)][next], dp[mask][last] + 1);
                }
            }
        }
    }

    int maxSubset = 0, mx;
    for (int mask = 0; mask < (1 << n); mask++){
        mx = *max_element(all(dp[mask]));
        if (maxSubset < mx) maxSubset = mx;
    }

    cout << n - maxSubset << '\n';
}


int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
