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
#define pqpriority_queue

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
const int MAXN = 1e5; // fenwick = N, trie  = N * number of bits

// Two things: 
// 1. Could not solve this problem, but I learned something new!
// 2. Why does this problem have the bitmask tag??? 
// I was expecting a bitmask problem because I searched for one BRUH!

// Solution
// The trick to solving this problem is to first identify
// that an O(N^3) nor a O(N^2) solution is too slow
// O(N^3): brute force, would not work.
// O(N^2): brute force + sort, would not work (but we can build from this).
// Why sort?
// because implicity now all triplets will be in the form of 
// a[j] <= a[i] <= a[k], where j<i<k.
// in other words, we just need to sum gcd(a[j],a[i]) * (n-i-1) to our ans.
// (n-i-1) comes from the last value a[k] in the triplet (a[j],a[i],a[k])
// where a[k] can be anything for k>i onwards.
// and there are (n-i-1) elements remaining for a fixed a[j] and a[i].
// However, this is still too slow because the solution would be O(N^2) because
// we will have to do 2 nested for loops for i and j.
// So how do we optimize further?
// Modified sieve. But why?
// If you think about it, gcd means greatest common divisor.
// what if we compute all the divisors of each number?
// note that for a[i] <= 10^5.
// => It can only have up to distinct 128 divisors.
// which is small.
// lets say if we were to compute and find all the divisors for each
// number from 1 to 10^5.
// first of all the time complexity would be: O(NLOGN)
// Now, lets say we computed it.
// Then now we can go through each number in the array a.
// then for each divisor j in a[i]
// we can calculate its contribution to the sum via 
// ans += (n-i-1) * (nums[j]);
// where nums[j] is the count of divisors seen before a[i].
// but why? lets say you have (4,8) as the current pair (we can ignore
// the last value always because a[k] >= 4 and 8.
// the common divisors are 1, 2, 4, the gcd is 4.
// lets say nums[1] = 3
// then this means that for this index i,
// a[i] and some previous elements a[j] have a common divisor of 1 three times.
// So for each pair, we multiply with (n-i-1) to get the total contribution.
// hence its nums[j]*(n-i-1).
// and we do this for all the common divisors.
// But why do it like this? Why not find the contribution for the largest 
// divisor only?
// Think sky, the reason is simple, because for each a[i], you MUST be paired
// with some a[j] where j<i, and some k>i.
// If you simply just compute for the largest divisor only, you neglect
// other pairs of (a[j],a[i]) with different divisors that are not the largest
// divisors of a[i].
// [x,y,z,k,p,t]
// our middle element is k
// lets say the largest divisor of k is only shared with z and y.
// then you completely neglected x then.
// thats why you need to go through all divisors for different pairs.

// Now for the final step.
// after computing all the contributions of each divisor.
// It is CRUCIAL to notice that, we have overcounted contributions
// for each divisor.
// hence we need to trim the overcounted divisors.
// How do you notice that there are overcounted divisors?
// Ez, think hard sky, lets just take the contribution of 1.
// first of all, not all pairs will have a gcd of 1.
// but based on the way we did it, we included the fact that every pair
// will always have a divisor of 1.
// so the contribution of 1, cnt[1], will always be overcounted
// and so we need to subtract the contribution of ALL the divisors after 1.
// to get the ACTUAL contribution of 1.
// In other words, for each cnt[i], we need to minus ALL its multiples to 
// get its ACTUAL contribution to the sum.
// And that is the solution to the problem, vellly nice!!
// Time complexity: O(MLOGM + 128*N + NLOGN).
// M is the largest a[i] in a.
// N is the size of a.

// Reflection
// I was very much intimidated when I saw this problem.
// This was the type of problem where I just couldn't come up with an idea
// immediately (I had no intuition whatsoever)
// More practice is needed for this type of problem.
// But seriusly tho, this was a good ass problem.
// the mixture of number theory (sieve) + dp + inclusion exclusion is deadlllly 

// Tip: when thinking about gcd, we can think in terms of divisors
// and then use inclusion exclusion to cancel out the smaller divisors.
// See below the code for potential applications.


vvi d(MAXN + 1); // d[i] will store all divisors of i.

// get all the divisors of each number up to MAXN
void modifiedSieve(){
    for (int i=1; i<=MAXN; i++){
        for (int j=i; j<=MAXN; j+=i){
            d[j].pb(i);
        }
    }
}

void solve() {
    int n, m, k;
    cin >> n;
    vi a(n);
    for (int &x: a) cin >> x;
    
    // Sorting ensures that for any triple (i, j, k) with i < j < k, we have a[i] <= a[j] <= a[k].
    sort(all(a));
    
    // nums: counts how many times a divisor has been seen so far.
    // cnt: accumulates contributions for each divisor.
    vi nums(MAXN+1, 0);
    vll cnt(MAXN+1, 0LL);
    
    for (int i=0; i<n; i++) {
        // For each divisor j of a[i]
        for (int j : d[a[i]]) {
            // (n - i - 1) equals the number of choices for the third element a[k]
            // and nums[j] holds the count of earlier elements whose divisor list contained j.
            cnt[j] += (n - i - 1) * (nums[j]++);
        }
    }
    
    ll ans = 0;
    // Process divisors in descending order to remove overcounts.
    for (int i=MAXN; i>=1; i--){
        // For every multiple j of i, subtract its contributions.
        for (int j=i*2; j<=MAXN; j+=i){
            cnt[i] -= cnt[j];
        }
        // Each triplet with gcd equal to i contributes cnt[i] times to the answer.
        ans += cnt[i] * i;
    }
    cout << ans << "\n";
}


int main() {
    fast_io();
    modifiedSieve();
    // precompute_factorials(MAXN, MOD);
    int t;
    cin >> t;
    while (t--) solve();
    // solve();
    return 0;
}
