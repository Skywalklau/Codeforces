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
using vpll = vector<pair<long long, long long>>;
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
#define mne min_element

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
    if (x == 1) return false;
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

const ll K = 6e6+5; // change according to your needs
vll mn(K, 0); // Smallest prime factor of each number
vvll fcv(K); // Prime factorization for each number (only returns each distinct factor once)


void precompute_prime_factors() { // Modified Sieve
    mn[1] = 1; // Base case: 1 has no prime factors
    for (ll i = 2; i < K; i++) {
        if (!mn[i]) { // If i has no prime factor recorded yet, it is a prime number.
            for (ll j = 1; j * i < K; ++j) {
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

void sieve() {
    mn[1] = 1; // 1 is not prime
    for (ll i = 2; i < K; i++) {
        if (mn[i] == 0) { // i is prime
            mn[i] = i;
            for (ll j = i * i; j < K; j += i) {
                if (mn[j] == 0) {
                    mn[j] = i; // smallest prime factor of j
                }
            }
        }
    }
}

vi get_primes_up_to_K() {
    vi primes;
    for (ll i = 2; i < K; i++) {
        if (mn[i] == i) primes.pb(i);
    }
    return primes;
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
const int MAXN = 3e5+5; // fenwick = N, trie  = N * number of bits

// solve time ~ 1hr 10 mins
// LETS GOOO I SOLVED A PROBLEM D!!!!!
// We need many things, this is a sparse table + bs + prefix sums problem
// First lets make some observations.
// For any slime to be eaten, note that its always AT most going to be
// the min pos of the next greater element, or the previous greater element.
// That is the upper bound, so can we use monotonic stacks?
// No. Because that is not necessarily the best answer.
// Lets say we have [3,2,2,5]
// We check 3, the next greater element is 5, so the no. of seconds needed
// is 3.
// But, actually, 2 is the answer, because we can use slime 2 to eat
// slime 3, then their cumulative sum is 4 now, which is enough to eat
// slime 1. This requires only 2 seconds.
// So, monotonic stack does not work here, but it does give an upper bound.
// What do we do then?
// First, notice that for each slime, it will be eaten by another
// slime either from the left or right, and this slime must have
// a size > a[i] itself.
// This suggest that we can use prefix sums + bs.
// Why? Because as soon as the sum from the left or right of a[i] is 
// > a[i], that means the chain of slimes can eat each other to be 
// big enough to consume a[i] now.
// There is an edge case tho, lets say we have [3,1,1,1,1]
// from the right, the last 4 slimes can be bigger than 3 now, which 
// is sufficient to consume slime 1. But, because all of their 
// sizes are equal, they actually cannot eat each other in the first place.
// So, this does not count, even when their sum is > a[i].
// Hence we need to search for a larger range.
// Another thing to notice, is that so long as we have a slime that
// is different size from the other slimes, and their cumulative sum
// is > a[i], its always possible to consume a[u] now, because the 
// biggest slime can eat all other slimes to be even bigger to eat
// all the other smaller slimes.
// Even in the worst case, where all slimes are equal, then 
// because we have one slime that is not equal, then the slimes next
// to it can eat it, and now we have a disparity because this slime
// is now big enough to consume all the other slimes.
// Eg. [2,2,2,2,1,2,2,2], slime 4 || 6 can eat slime 5 to eat everything
// else later.
// So, its always possible as long as the slims are not all equal.
// But, how do we know this? Can we somehow efficiently query
// whether all the elements are equal or not?
// Yes, with sparse table.
// If the max within the range is not equal to the min of the range.
// This implicitly tells us that not all the elements are equal, so
// that means its possible for the one slimes to eat all other slimes
// in this range.
// And that is the idea to solve this problem.
// We extrapolate this idea to the left and right side because
// a slime can be eaten from the left or from the right.
// There is an edge case tho, that is if the slime next to a[i] is 
// already bigger than it, then the answer is just 1.
// We need to do this because we are binary searching from i+1 to n, and
// from 0 to i-1.
// Hence we are assuming a[i-1] and a[i+1] are both < a[i] when doing
// the bs + sparse table.

int sparseMin[LOGN][MAXN], sparseMax[LOGN][MAXN];

void createSparseMax(vll& a){ 
    for (int i=0; i<sz(a); i++) sparseMax[0][i] = a[i];
    for (int i=1; i<LOGN; i++){
        for (int j=0; j+(1<<i)<=sz(a); j++){
            sparseMax[i][j] = max(sparseMax[i-1][j], sparseMax[i-1][j+(1<<(i-1))]);
        }
    }
}

void createSparseMin(vll& a){
    for (int i=0; i<sz(a); i++) sparseMin[0][i] = a[i];
    for (int i=1; i<LOGN; i++){
        for (int j=0; j+(1<<i)<=sz(a); j++){
            sparseMin[i][j] = min(sparseMin[i-1][j], sparseMin[i-1][j+(1<<(i-1))]);
        }
    }
}

int queryMin(int l, int r){
    int k = 31 - __builtin_clz(r-l+1);
    return min(sparseMin[k][l], sparseMin[k][r-(1<<k)+1]); 
}

int queryMax(int l, int r){
    int k = 31 - __builtin_clz(r-l+1);
    return max(sparseMax[k][l], sparseMax[k][r-(1<<k)+1]); 
}

int binarySearchLeft(int i, vll& pref, ll target){
    int low = 0, high = i, ans = -1;
    while (low <= high){
        int mid = low + (high-low)/2;
        ll sum = mid-1>=0 ? pref[i] - pref[mid-1] : pref[i];
        if (queryMax(mid, i) > queryMin(mid, i) && (sum > target)){
            ans = mid;
            low = mid + 1;
        } 
        else high = mid - 1;
    }
    return ans;
}

int binarySearchRight(int i, vll& pref, ll target){
    int low = i, high = sz(pref)-1, ans = -1;
    while (low <= high){
        int mid = low + (high-low)/2;
        ll sum = mid-1>=0 ? pref[mid] - pref[i-1] : pref[mid];
        // cout << sum << endl;
        if (queryMax(i, mid) > queryMin(i, mid) && (sum > target)){
            ans = mid;
            high = mid - 1;
        } 
        else low = mid + 1;
    }
    return ans;
}

void solve() {
	int n, k, m;
    cin >> n;

    vll a(n);
    for (ll& x : a) cin >> x;

    vll pref(n, a[0]);
    for (int i=1; i<n; i++) pref[i] = pref[i-1] + a[i];

    createSparseMax(a);
    createSparseMin(a);

    vll result(n);
    for (int i=0; i<n; i++){
        if (i > 0 && a[i-1] > a[i]) result[i] = 1;
        else if (i < n-1 && a[i+1] > a[i]) result[i] = 1;
        else{
            int left = binarySearchLeft(i-1, pref, a[i]);
            int right = binarySearchRight(i+1, pref, a[i]);
            // cout << left << " " << right << endl;
            int leftAns = left == -1 ? MAX : i - left;
            int rightAns = right == -1 ? MAX : right - i;
            int ans = min(leftAns, rightAns);
            result[i] = ans == MAX ? -1 : ans;
        }
    }

    printVector(result);

}

int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    // sieve();
    // precompute_prime_factors(); // modified sieve
    int t;
    cin >> t;
    while (t--) solve();
    // solve();
    return 0;
}
