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

// solve time ~ 1hr 15 mins, wrong intuition at first rly fucked me...
// I tried greedy, but it don't work, should've known...
// I swear I did this problem somewhere before. It feels familiar, especially
// after noticing that the greedy strat don't work.
// My greedy idea was 2 pointers, left and right, we always have a choice.
// Do I pick the left side or right side of the cake?
// We take the cake with the smaller sum and give it out.
// Actually, its not correct.
// Because taking the bigger valued cake might be better for a future move.
// take m=3,v=4.
// [1,4,4,3,3]
// my code would take [1,4] and give it instead of [3,3] at first, thats the 
// wrong move.
// then [4] is given, then [3,3] is given. So, I end up with 0.
// Actually, we should do [3,3], then [4], then [4] again. So I am left with
// [1], hence my value is 1, which is bigger.
// So greedy cannot work.
// Instead, we can do bs + pref + suff.
// pref[i] = number of ppl that can be satisfied with first i cakes.
// suff[i] = number of ppl that can be satisfied with last i cakes.
// Then, we try in O(NLOGN), the best range st. pref[i-1] + suff[mid+1] >= m
// and my own subarray sum is maximized.
// Another edge case, it could be the case that ans = -1, meaning we can't give
// to all friends.
// Which is true, but what if we just have enough to satisfy everyone, but not
// myself? In this case ans should be 0, not -1.
// So, before the bs, we check if pref[n] >= m, ensuring that it is possible
// to give everyone a cake.
// So, if ans == -1 but its possible to give everyone a cake, then ans == 0.

void solve() {
	ll n, k, m, v;
    cin >> n >> m >> v;

    vll a(n+1);
    for (int i=1; i<=n; i++) cin >> a[i];

    vll pref(n+1, 0ll), suff(n+3, 0ll), prefSum(n+1, 0ll);
    ll sum = 0;
    for (int i=1; i<=n; i++){
        prefSum[i] = a[i] + prefSum[i-1];
        sum += a[i];
        if (sum >= v) {pref[i]++; sum = 0;}
        pref[i] += pref[i-1];
    }
    sum = 0;
    for (int i=n; i>=1; i--){
        sum += a[i];
        if (sum >= v) {suff[i]++; sum = 0;}
        suff[i] += suff[i+1];
    }

    // printVector(pref);
    // printVector(suff);

    bool isPossible = false;
    // for (int i=1; i<=n; i++) if (pref[i] + suff[i+1] >= m) {isPossible = true; break;}
    if (pref[n] >= m) isPossible = true;

    ll ans = -1;
    for (int i=1; i<=n; i++){
        int low = i, high = n;
        int x = -1;
        while (low <= high){
            int mid = low + (high-low)/2;
            if (pref[i-1] + suff[mid+1] >= m){
                x = mid;
                low = mid+1;
            }
            else{
                high = mid-1;
            }
        }

        if (x != -1){
            // cout << i << " " << x << endl;
            ans = max(ans, prefSum[x] - prefSum[i-1]);
        }
    }

    if (isPossible && ans == -1) cout << 0 << '\n';
    else cout << ans << '\n';

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
