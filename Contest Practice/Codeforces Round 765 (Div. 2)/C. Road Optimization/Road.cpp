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

// solve time ~ 1hr
// Tip: If dp[i-1][j] is not enough, then look at i-2,i-3,i-4...,i-k
// as well if it fits within time constraints.
// My biggest mistake was taking too long to realize that.
// Solved it eventually, but took too long.

// Alright, so how do we solve this problem?
// Greedy can't work because there is no such way to find an actual
// best move each turn, maybe there is, but I can't find it.
// So dp is the best way to go because we can just brute force this.
// at each sign, we can choose to take, or don't take it.
// We need 2 states for the dp because of this.
// Let dp[i][k] = min dist so far up to the ith sign, with k removals left.
// Base case: dp[1][k] = 0.
// Why? Because initially we start at the 1st sign, and we don't use any
// removals as we haven't moved yet. So, the min dist is just 0.
// Transition: This is the hard part.
// We can't just look at dp[i-1][each j up to k].
// This is not enough, because if the (i-1)th sign is removed as well, then
// we have to check the (i-2)th sign and so on.
// So, we have to do this in O(N^3).
// We check, for each sign before the ith sign, each valid dp state.
// So, the transition is:
// dp[i][j-z] = min(dp[i][j-z], dp[i-z-1][j] * (d[i] - d[i-z-1]) * a[i-z-1]);
// What does this mean?
// We are at the i-th sign, so if I want to skip z signs, then I need to 
// jump from i-z-1 to i.
// Thus, we need to check dp[i-z-1][j], ans since I skip z signs, the 
// new dp becomes dp[i][j-z] because we used z removals from j 
// removals remaining.
// And then obviously we want to add the cost, which is 
// (d[i] - d[i-z-1]) * a[i-z-1]).

// Another way we can do it is via dp[i][k] where dp[1][0] = 0.
// Which is the opposite way to think about it, instead of k removals left
// we say number of removals used.
// Alternative version is found after my solution.

void solve() {
	int n, k, m, l;
    cin >> n >> l >> k;

    n++;
    vi a(n+1), d(n+1);
    
    for (int i=1; i<n; i++) cin >> d[i];
    for (int i=1; i<n; i++) cin >> a[i];

    vvi dp(n+1, vi(k+1, MAX));

    d[n] = l;
    // base case: min dist at the 1st sign without using any removal is 0.
    dp[1][k] = 0; 

    for (int i=2; i<=n; i++){
        for (int j=k; j>=0; j--){
            for (int z=0; z<=j; z++){
                if (i-z-1 >= 1 && dp[i-z-1][j] != MAX){
                    dp[i][j-z] = min(dp[i][j-z], dp[i-z-1][j] + (d[i] - d[i-z-1]) * a[i-z-1]);
                }
            }
        }
    }

    int ans = MAX;
    for(int i=0; i<=k; i++) ans = min(ans,dp[n][i]);
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


// alternative solution: instead doing k moves left, we do k moves used.

// int dp[510][510],a[510],d[510];
 
// signed main()
// {
// 	memset(dp,0x3f,sizeof dp);
// 	int n,l,k;
// 	cin>>n>>l>>k;
 
// 	for(int i=1;i<=n;i++)cin>>d[i];
// 	for(int i=1;i<=n;i++)cin>>a[i];
	
// 	dp[1][0]=0;
// 	d[n+1]=l;
	
// 	for(int i=2;i<=n+1;i++){
// 		for(int j=0;j<=min(i-1,k);j++){
// 			for(int z=0;z<=j;z++){
// 				dp[i][j]=min(dp[i][j],dp[i-z-1][j-z]+(d[i]-d[i-z-1])*a[i-z-1]);
// 			}
// 		}
// 	}
	
// 	int ans=1e18;
// 	for(int i=0;i<=k;i++)ans=min(ans,dp[n+1][i]);
// 	cout<<ans;
// 	return 0;
// }