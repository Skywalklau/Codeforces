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

// solve time ~ can't solve. Shit and its 1500.
// Honestly, my biggest mistake was reading the problem wrongly.
// I thought we had to always make first char of predecessor == 
// last char of successor, but thats only for the first and final king.
// In between, it should be last char of predecessor == first char of
// successor.
// HUGE MISTAKE. So I completely butchered my dp states.
// I realized that I apparently read the question wrong after
// reading the editorial. Bruh.
// Because of that I read the answers as well and I got spoiled, so 
// I can't genuinely attempt this problem properly anymore. Sadge.

// This problem is dp, very common path selection dp.
// let dp[i][j] = max length so far.
// i == first char of the current string
// j == last char of the current string
// base case: 
// we start with no string so all dp[i][j] is 0 initially.
// Let l = firt char of current string, r = last char of current string
// Transition:
// Case 1: dp[j][l] was defined previously, we can build upon it.
// if (dp[j][l] != 0) dp[j][r] = max(dp[j][r], dp[j][l] + sz(a[i]));
// Where j is all the potential starting characters from a to z.
// so if dp[j][l] exists, then our potentially new string is dp[j][r].
// Case 2: We make a new start point, with l and r.
// dp[l][r] = max(dp[l][r], sz(a[i]));
// Basically we build starting with this string (if possible).

// Time complexity: O(N*26)
// Space complexity: O(N + 27*27)

int dp[27][27];
// dp[i][j] = max length so far
// i == first char
// j == last char

void solve() {
	int n, k, m;
    cin >> n;

    vstr a(n+1);
    for (int i=1; i<=n; i++) cin >> a[i];

    for (int i=1; i<=n; i++){
        int l = a[i][0] - 'a';
        int r = a[i].back() -'a';
        for (int j=0; j<26; j++){
            if (dp[j][l] != 0){
                dp[j][r] = max(dp[j][r], dp[j][l] + sz(a[i]));
            }
        }
        dp[l][r] = max(dp[l][r], sz(a[i]));
    }
    
    int ans = 0;
    for (int i=0; i<26; i++) ans = max(ans, dp[i][i]);
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

// My initial sol - wrong.
// int dp[MAXN][26][2];
// // dp[i][j][k] = max length so far up to i
// // i == current king (index)
// // j == the first letter of the ith king
// // k == terminal or not (first and last character of the string is equal or not)

// void solve() {
// 	int n, k, m;
//     cin >> n;

//     vstr a(n+1);
//     for (int i=1; i<=n; i++) cin >> a[i];


//     for (int i=0; i<=n; i++){
//         for (int j=0; j<26; j++){
//             dp[i][j][0] = -MAX;
//             dp[i][j][1] = -MAX;
//         }
//     }

//     for (int i=1; i<=n; i++){
//         int firstChar = a[i][0] - 'a';
//         if (a[i][0] == a[i][sz(a[i])-1]) dp[i][firstChar][1] = sz(a[i]);
//         else dp[i][firstChar][0] = sz(a[i]);
//     }

//     for (int i=2; i<=n; i++){
//         for (int j=0; j<26; j++){
//             dp[i][j][0] = max(dp[i][j][0], dp[i-1][j][0]);
//             dp[i][j][1] = max(dp[i][j][1], dp[i-1][j][1]);
//         }
        
//         m = sz(a[i]);
//         int firstChar = a[i][0] - 'a';
//         int lastChar = a[i][m-1] - 'a';

//         // cout << a[i][0] << " " << a[i][m-1] << endl;

//         dp[i][firstChar][1] = max({dp[i][firstChar][1], 
//                                    dp[i-1][lastChar][0] + m, 
//                                    dp[i-1][lastChar][1] + m});
        
//         // cout << dp[i][firstChar][0] << " ddd" << endl;
//         dp[i][firstChar][0] = max({dp[i][firstChar][0], dp[i-1][lastChar][1] + m});
        
//         cout << dp[i][firstChar][1] << " " << dp[i][firstChar][0] << endl;
//     }

//     int ans = 0;
//     for (int i=0; i<26; i++) ans = max(ans, dp[n][i][1]);
    
//     cout << ans << '\n';

// }