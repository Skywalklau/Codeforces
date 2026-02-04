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

// solve time ~ 1hr, index issues were so annoying...
// Nice problem tho.
// The key here is to notice that there is no benefit in considering
// i < l and i > r at the same time.
// Lets split the array into 3 parts.
// [x,x,x,l,y,y,y,r,z,z,z]
// into [x,x,x], [l,y,y,y,r], [z,z,z]
// our goal is to put the minimum elements somehow into the middle array
// but we can never achieve this if we take [x,x,x] [l,y,y,y,r] and [z,z,z]
// into consideration.
// because we are taking subseq. and reversing, we would just reverse the
// 1st array with 3rd array elements, making no changes to the middle array
// so its just left with mid, or mid with right array.

// The next thing to notice is that we obviously want to put the smaller 
// elements in [x,x,x] into [l,y,y,y,r]
// Realize that order does not matter. Because as long as the element is
// within the other array then it works since we are doing sum(a from l to r)
// So we can sort the arrays.
// Notice that once you sort the arrays, its suffix sums of the last k elements
// in reverse order, so we can sort in reverse order and take suffix sums for
// left and right.
// you want to take from left into mid.
// then now there are 3 cases:
// sz(left) == sz(mid):
// you start from k=0 to sz(left) for the suff
// you start from i=0 to sz(mid)
// sz(left) < sz(mid):
// you start from k=0 to sz(left) for the suff
// you start from i=sz(mid)-sz(left) to sz(mid)
// sz(left) > sz(mid):
// you start from k=sz(left)-sz(mid) for the suff
// you start from i=0 to sz(mid)
// then for each case, we can do prefMid[i] + suffLeft[i], and get the min sum.
// repeat the same for suffRight.
// this is done to ensure our number of elements in mid stays the same.


void solve() {
	int n, k, m, l, r;
    cin >> n >> l >> r;

    vll a(n+1);
    for (int i=1; i<=n; i++) cin >> a[i];

    if (l == 1 && r == n) {cout << accumulate(all(a),0LL) << '\n'; return;}

    vll b;
    for (int i=l; i<=r; i++) b.pb(a[i]);
    // printVector(b);

    vll left, right;
    for (int i=1; i<l; i++) left.pb(a[i]);
    for (int i=r+1; i<=n; i++) right.pb(a[i]);

    // printVector(left);
    // printVector(right);
    // printVector(b);

    sort(all(b));
    sort(all(left), greater<ll>());
    sort(all(right), greater<ll>());

    vll suffLeft(sz(left)+1), suffRight(sz(right)+1), pref;

    ll sum = 0;
    pref.pb(0);
    for (int i=0; i<sz(b); i++) {sum += b[i]; pref.pb(sum);}
    for (int i=sz(left)-1; i>=0; i--) suffLeft[i] = left[i] + suffLeft[i+1];
    for (int i=sz(right)-1; i>=0; i--) suffRight[i] = right[i] + suffRight[i+1];

    // printVector(pref);
    // printVector(suffLeft);
    // printVector(suffRight);

    // middle with left
    ll ans = accumulate(all(b), 0LL);
    int start = max(0, sz(b)-sz(left));
    int j = sz(b) >= sz(left) ? 0 : sz(left)-sz(b);
    for (int i=start; i<sz(b); i++,j++){
        if (ans > pref[i] + suffLeft[j]){
            ans = pref[i] + suffLeft[j];
        }
    }

    // middle with right
    start = max(0, sz(b)-sz(right));
    j = sz(b) >= sz(right) ? 0 : sz(right)-sz(b);
    for (int i=start; i<sz(b); i++,j++){
        if (ans > pref[i] + suffRight[j]){
            ans = pref[i] + suffRight[j];
        }
    }

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
