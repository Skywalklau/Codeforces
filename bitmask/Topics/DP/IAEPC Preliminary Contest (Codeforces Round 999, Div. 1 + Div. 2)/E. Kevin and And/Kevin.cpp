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
using vvch = vector<vector<char>>;

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

// Fun problem, I learned a new greedy trick.
// First things first, we need to realize the fact that 
// aplying AND operations to any number a[i] is convex
// meaning, when you apply a[i] & x to make it v.
// then you apply v & y to make it u.
// the difference: v-u <= a[i]-v
// meaning the more operations of AND you apply
// the smaller the difference (or contribution) to make it a smaller 
// number.
// Proof:
// let g(i) be the minimum number of operations to minimize the a number
// using i operations.
// we aim to prove that g(i-1) - g(i) <= g(i) - g(i+1), which is
// convexity.
// let v, u be the min value of g(i-1) and g(i+1) respectively.
// after one more operation from i-1, note that we can ALWAYS
// find a move such that we can turn off at least one bit from v.
// let that bit be in position w (that bit will be the largest bit
// we can turn off because we are trying to minimize our value).
// in this case, we have g(i-1) - v&x >= 2^w.
// where v&x corresponds to the min value of g(i) as we now made 1 more
// operation from g(i-1).
// explicitly speaking this means that the difference between the 
// g(i-1) and g(i) will be at least 2^w, because after turning off
// the largest bit from v, we might also turn off other bits in v.
// Moving on to the transition from v&x to u.
// Note that, the next largest bit we can potentially turn off
// will always be at most at position w-1 because the w bit is turned
// off already (and w is the largest bit we were able to turn off
// prior to this current move).
// Also from the well known property: 2^w > 2^0 + 2^1 +...+ 2^(w-1).
// Hence, even if we manage to turn off all the bits after the w bit
// we can never achieve a larger contribution than the transition
// from v to v&x.
// We can conclude that: g(i-1) - g(i) <= g(i) - g(i+1).
// Proving convexity of the AND operations.


// Knowing this property, we can then use a greedy technique to 
// solve this problem.
// since m is small, we can just go through all combinations 
// of AND operations on a number a[i].
// then, we can find the most significant contribution for every
// number of operations 1,2,3...m for each a[i] by finding the 
// difference between 2 consecutive operations.
// if I make k operations, I can find the best k operation move
// to minimize my a[i].
// I can then do the same thing for k+1 operations, where I will find
// the best k+1 operation move to minimize my a[i].
// the difference, between the two operations, will give me my 
// contribution to go to from k operations to k+1 operations.
// we repeat this for all numbers in a, and for up to m operations each.
// we can then sort the operations, or use a pq.
// then for the first k moves, we remove those contributions, because
// they are the most significant ones that contribute to the initial
// sum (our answer).
// removing those will greedily remove the most significant contributions
// to minimize our answer.

// Time complexity: O(n*2^m + m*2^m + k + logn)
// Space complexity: O(n+m+n*(m-1))
void solve() {
	int n, k, m;
    cin >> n >> m >> k;
    
    vi a(n);
    vi b(m);
    ll ans = 0;
    for (int &x: a) cin >> x, ans += x;
    for (int &x: b) cin >> x;

    vi d(1<<m, (1<<30)-1);
    // get each possible combination of AND
    for (int mask=0; mask<(1<<m); mask++){
        for (int bit=0; bit<m; bit++){
            if (mask & (1<<bit)){
                d[mask] &= b[bit];
            }
        }
    }

    pq<int> q;
    for (int i=0; i<n; i++){
        // t stores the minimum new result after 1,2,3...m operations.
        int t[m+1];
        // note to self: dont use memset(t,a[i],sizeof(t));
        // why? Because memset only works for -1 to 255 (1 byte).
        for (int j=0; j<=m; j++) t[j]=a[i];
        for (int mask=0; mask<(1<<m); mask++){
            int v = __builtin_popcount(mask);
            t[v] = min(t[v], a[i]&d[mask]); // get the best one 
        }
        // store the contribution from k operations to k+1 operations.
        for (int j=1; j<=m; j++) q.push(t[j-1] - t[j]);
    }

    // remove the first k significant contributions
    while (k--){
        ans -= q.top();
        q.pop();
    }

    cout << ans << '\n';

}

int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
