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

// get all factors up to n
vvi factors(K);

void getAllFactors(){
    for (int i = 1; i <= K; i++) {
        for (int j = i; j <= K; j += i) {
            factors[j].push_back(i); // i is a divisor of j
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

// solve time ~ 1hr 8 mins
// This was a fun one.
// Think greedily, what is the best spot to put a gorilla?
// Its always going to be in the middle of the grid, because this way 
// we can cover as much of the square as possible.
// If we think by frequency, we obviously want to put the largest a[i] at the
// spot where the square can go through the most
// lets say we have a 3 x 3 grid.
// then k=2.
// this way, the point (1,1) can be gone through 4 times (area of the square).
// So, we can build from there.
// The idea is, for each cell, what is the number of times the square will
// go through it. If we can figure this out, then we can just sort them
// by frequency and greedy this.
// the cells that have the highest number of squares covering it will be 
// assigned to the largest a[i].
// and thats the idea.
// So, how do we know the contribution of each cell?
// We need to make some observations for this.
// Think of it like this, for each cell, we find all the positions of the 
// it can occupy if we put the square including this cell.
// Eg.
// if its n = m = 3, and k = 2, then (1,1) can cover all four corners, or
// all the cells of the square. Meaning the area is 4.
// So, how do we solve this?
// The trick is to check, for each cell, the width and height the square
// can move about this cell, meaning:
// In terms of height: 
// h = min({k, i, n-i+1, n-k+1});
// In terms of length:
// l = min({k, j, m-j+1, m-k+1});
// I will explain for h, the height. Similar argument can be said for l.
// if we fix any (x,y) as a fixed point, and we wanna see how many squares
// about this point we can fit into it, then in terms of height, we must first
// take the min(i, n-i+1). 
// Why? Because visually,
// lets say n = 10, and we are at i=4
// then from the top, we can put our square up to height of 4,
// then from the bottom, we can put our square up to height of 10 
// but this means we can cover only max of 4, because eventhough beneath us
// there is more space, we wanna also be able to shift the square up as well,
// and we can only move an extra 4 units up for any square, whereas bottom
// we can go 7 units in total.
// So that means we can actually only move in terms of 4 units up or down.
// Eg.
// xxxxxxx
// xx.xxxx
// xxxxxxx
// xxxxxxx
// xxxxxxx
// xxxxxxx
// We are considering the "." point. If k = 3. How many ways can I form a 3x3
// square including this "." point?
// The answer is only the first 2 rows with each column on the 3x3 square.
// which is h = min(2, 6-2+1) = 2.
// l = min(3, 7-3+1) = 3
// hence area is only 3*2 = 6.
// But, notice that this only assumes if we can actually freely move the 
// square after this "." point.
// What if the square is the size of the row || column?
// then actually we can never shift it at all, and hence we need 
// min({i, n-i+1, n-k+1}) and min({j, m-j+1, m-k+1})
// Here, n-k+1 is the bound to let us know if we can actually shift it in terms
// of row in the first place.
// Likewise, m-k+1 is by column.
// Also, don't forget that we need to bound everything by k as well.
// Why? Because if the min length is > k, then that means we can cover
// a larger length than k, but the square is only at most k in length.
// So, we must bound it by k as well if our min length is > k, meaning we 
// just take up to k units instead of > k as our square is only k units in 
// the first place.
// And thats the idea.
// Now, we can get the area, and store it in a mset.
// Then we can approach this problem greedily using the previously mentioned
// technique.

void solve() {
	ll n, k, m, w;
    cin >> n >> m >> k;
    cin >> w;
    vll a(w+1);
    for (int i=1; i<=w; i++) cin >> a[i];

    sort(a.begin()+1, a.end(), greater<ll>());
    mset<ll> s;
    for (ll i=1; i<=n; i++){
        for (ll j=1; j<=m; j++){
            ll h = min({k, i, n-i+1, n-k+1});
            ll l = min({k, j, m-j+1, m-k+1});
            ll area = l * h;
            // cout << i << " " << j << " " << area << endl;
            if (area >= k*k) s.insert(k*k);
            else s.insert(area);
        }
    }

    ll ans = 0;
    for (int i=1; i<=w; i++){
        ll val = *s.rbegin();
        // cout << val << endl;
        ans += a[i] * val;
        s.extract(val);
    }

    cout << ans << '\n';

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
