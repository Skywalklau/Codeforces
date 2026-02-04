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
using vpll = vector<pair<ll, ll>>;

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

// solve time ~ 2.5 hrs, please tell me I got solved it otherwise
// imma fucking crash out bruh
// Thank god I solved it.
// The most important observation is:
// To maximize the median, we must have (n+1)/2 elements >= median.
// and we must have a value at the midpoint as the median.
// Notice that we can use bs to solve this problem (my intution say so)
// Because we can just bs for the best median and check if this is the 
// best answer, something like that.
// There are 2 conditions for a valid median:
// 1. The sum of the array must be <= s.
// 2. The midpoint of the array must be == median.
// Initially, I failed to realize the fact that the midpoint could 
// be non-median value which dragged my pace significantly...

// Now, notice that we can greedily optimize the array formed with median x
// by first:
// lessX: finding all ranges that are purely < x.
// moreOrEqualX: finding all ranges that are purely >= x.
// bothX: finding all ranges that are both.
// Now, since we know that we need (n+1)/2 elements >= x.
// then we know for sure that we need n - (n+1)/2 elements < x.
// So, if the array containing elements < x has less than
// n - n(n+1)/2 elements, then we need to add more elements to it using
// bothX.
// However, we need to optimally do this (greedy), so we add the cheapest
// elements in bothX to lessX until it has n - (n+1)/2 elements.
// The remaining elements then go to moreOrEqualX, and we add x for each 
// element of bothX (because bothX means it can be >= x so we greedily just
// want to add x to minimize cost).
// Lastly, we can concatenate lessX with moreOrEqualX after sorting 
// moreOrEqualX.
// get their sum and their median.
// if the sum <= s && median == x.
// then this is a valid answer, but there could be a better answer.
// so low = mid+1.
// else high = mid-1.

pll check(vpll& R, int x, int n){
    vll lessX, moreOrEqualX; 
    vpii bothX;

    for (int i=0; i<sz(R); i++){
        if (R[i].S < x) lessX.pb(R[i].F);
        else if (R[i].F >= x) moreOrEqualX.pb(R[i].F);
        else bothX.pb(R[i]);
    }

    // printVector(lessX);
    // printVector(moreOrEqualX);
    // cout << sz(bothX) << endl;
    // cout << sz(lessX) << endl;
    // cout << sz(moreOrEqualX) << endl;

    sort(all(bothX), [](pii& a, pii& b){return a.F < b.F;});

    //ll ans = MAXL;
    int idx = max(0, min(sz(bothX), n - (n+1)/2 - sz(lessX)));
    //cout << idx << endl;

    for (int i=0; i<idx; i++) lessX.pb(bothX[i].F);
    
    for (int i=idx; i<sz(bothX); i++) moreOrEqualX.pb(x);

    // cout << x << endl;
    // printVector(lessX);
    // cout << sz(lessX) << endl;
    // printVector(moreOrEqualX);
    // cout << sz(moreOrEqualX) << endl;

    // if (sz(lessX) == n - (n+1)/2 && sz(moreOrEqualX) == (n+1)/2){
    //     // printVector(lessX);
    //     // cout << sz(lessX) << endl;
    //     // printVector(moreOrEqualX);
    //     // cout << sz(moreOrEqualX) << endl;
    //     ans = accumulate(all(lessX), 0) + accumulate(all(moreOrEqualX), 0);
    //     cout << x << endl;
    //     cout << "YES" << " " << ans << endl;
    // }

    ll ans = accumulate(all(lessX), 0LL) + accumulate(all(moreOrEqualX), 0LL);

    sort(all(moreOrEqualX));
    // cout << "x: " << x << endl; 
    lessX.insert(lessX.end(), all(moreOrEqualX));
    // printVector(lessX);
    // cout << "sum: " << ans << endl;

    return {lessX[(n-1)/2], ans};
}


void solve() {
	ll n, k, m, s;
    cin >> n >> s;

    vpll R(n);
    for (int i=0; i<n; i++){
        ll l, r;
        cin >> l >> r;
        R[i] = {l,r};
    }

    int low = 1, high = 1e9;
    int ans = 0;

    while (low <= high){
        int mid = low + (high-low)/2;

        //cout << mid << endl;
        pll p = check(R, mid, n);
        
        if (p.S <= s && p.F >= mid){
            low = mid+1;
            ans = mid;
        }
        else high = mid-1;
    }

    //cout << check(R, 29, n, s) << endl;
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
