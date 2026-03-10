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
using vvld = vector<vector<ld>>;
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

// solve time ~ 54 mins
// Less goo solved a 1600 problem. Pretty fun combinatorics problem.
// We need to make some observations.
// 1. Notice that a[0] acts like a universal box, we can use it everywhere.
// 2. Is there a case where no permutation is possible? Yes.
// This happens when there exists some a[i] and a[j] such that abs(a[i]-a[j])>1.
// Greedily, we can use our universal box a[0] to distribute it to all the 
// other values s.t each a[i] is at most target-1, where target = max(all(a)).
// Why? Lets take [4,4,3,3].
// This is possible, because we can keep cycling through this to get to:
// [1,1,0,0] and then [0,0,0,0] in the end.
// So we can satisfy the requirements.
// But, Whereas if we used our a[0] but we cannot make it in our intended form:
// ie. [4,4,3,2].
// then as you can see its impossible, because we will reach:
// [2,2,1,0] and then [1,1,0,-1], uh oh, a[n-1] has nothing to decorate.
// So, its impossible.
// This means we can check if its possible by first greedily distributing everthing
// first.
// After greedily filling, we have some a[i] = target-1.
// But, if our a[0] is still > 0, then we can still use it.
// So, lets use it to make the rest of the a[i] == target instead of target-1.
// In the end, if we managed to make everything a[i] equal, this implies that
// there are actually n! ways to permute. 
// Why? Because everyone can just be assigned to one another and we can still
// decorate everything, with some a[0] >= 0, the remainder a[i] can take each
// a[0] each to fill the tree again. 
// 4. Otherwise, this means we have some a[i] == target and some a[i] == target-1.
// This is the trickiest part.
// We need to realize to keep track of a cnt of original values == target.
// Then, we also keep track of each new a[i] == target as well.
// ie. cnt = 2, newCnt = 4 means we have 2 more a[i] == target.
// Now, we need to make perhaps the most crucial observation.
// Since we can make newCnt-cnt new a[i] == target. This means we actually
// can assign this diff to exactly n-cnt values. 
// I.e lets say we have: [4,4,3,3,3,4,4,4,3]
// The last three 4's are originals, cnt.
// Then we know newCnt = 5.
// So, there are exactly 6C2 ways to assign this newCnt-cnt=2 values to the 
// remainder indexes.
// Then, also notice that between the 4's, there is exactly 5! ways to assign
// to one another.
// Likewise, among the 3's, there is exaclty 4! ways to assign to one another.
// Hence, the total is 6C2 * 4! * 5!.
// Deriving this, we get: (n-cnt)C(newCnt-cnt) * newCnt! * (n-newCnt)!
// And thats the solution.

void solve() {
	ll n, k, m;
    cin >> n;

    vi a(n+1);
    for (int &x : a) cin >> x;
    
    int target = *mxe(a.begin()+1, a.end());
    int cnt = 0;
    for (int i=1; i<n+1; i++){
        if (a[i] == target) cnt++;
    }

    int c = a[0];
    for (int i=1; i<n+1; i++){
        if (a[i] < target-1){
            if (c + a[i] >= target-1){
                c -= (target-1-a[i]);
                a[i] = target-1;
            }
            else {cout << 0 << '\n'; return;}
        }
    }

    int i=1;
    while (i<n+1 && c>0){
        if (a[i] == target-1) {a[i]++; c--;}
        i++;
    }

    bool ok = true;
    for (int i=1; i<n+1; i++){
        if (a[i] != a[1]) ok = false;
    }

    if (ok) cout << fact[n] << '\n'; 
    else{
        int newCnt = 0;
        for (int i=1; i<n+1; i++){
            if (a[i] == target) newCnt++;
        }

        cout << (((nCr(n-cnt, newCnt-cnt, MOD2) * fact[newCnt]) % MOD2) * fact[n-newCnt]) % MOD2 << '\n';
    }

}

int main() {
    fast_io();
    precompute_factorials(51, MOD2);
    // sieve();
    // precompute_prime_factors(); // modified sieve
    int t;
    cin >> t;
    while (t--) solve();
    // solve();
    return 0;
}
