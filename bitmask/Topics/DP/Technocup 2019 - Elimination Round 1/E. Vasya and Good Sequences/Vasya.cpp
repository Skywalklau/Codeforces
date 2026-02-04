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
const int MAXN = 3e5+5; // fenwick = N, trie  = N * number of bits

int pre[MAXN], cnt[MAXN], dp[2];

// Time spent to attempt to solve without editorial: ~2hrs (and failed to solve)
// Had to use editorial.
// Tough problem, tried solving it but had no clue how to approach this problem
// at all. 
// I knew it was dp, tried to do it, but got lost.
// Nonetheless I enjoyed this problem. And I learned a new trick!

// Observation 1: In other words, the problem boils down to number of bits
// because we can always just rearrange the numbers to align them so that
// the bits cancel. (I noticed this)

// Observation 2: for any [l,r], the number of bits present must be even.
// Why? Because only even number of bits can ever cancel out to give XOR == 0.
// lets prove by counterexample. Let x=1001, y=1000
// the total number of set bits is 3, which is odd.
// now, we can rearrange them to try to remove the XOR, but we can never do it.
// because x^y even after rearanging will always have 1 extra set bit.
// => odd number of bits can never cancel out to give XOR == 0 even after 
// optimal rearangement

// Obervation 3: Even if the number of set bits is even, it is not always the case
// that the XOR can be 0.
// But when? Lets analyze.
// we have a subarray [x,y,z], we want to check if it is valid.
// lets say x = 101011111, y=1011, z=10011
// we can rearrange x to x=1111111, y=111, z=111.
// so the total number of set bits is 8+3+3=14, which is even number of set bits
// (so there is a chance that is it valid, but is it? Lets see below)
// can we rearrange this so that x,y,z ever cancels out to 0?
// Never, the best we get is 11 (base 2), not 0.
// because 11111111
//       ^ 111
//       ^    111
//               11
// which is 11. not 0.
// So it is proven that, even with an even number of set bits, it is not neccesarily
// the case that it is a valid subarray such that XOR == 0.
// But when is it the case that it is invalid?
// 1. check that the subarray has an even number of bits (proven above), and we 
// can use prefix sums for this.
// 2. find the number with the max number of bits set, call it maxn, and check if
// maxn > pref[i]-pref[j-1]-maxn.
// where pref is the prefix sum of the NUMBER of set bits up to some idx i.
// in this case, we are checking the subarray [j,i].
// Why? Because if maxn still has extra bits after we use pref[i]-[j-1] to cancel
// the bits in maxn.
// => invalid subarray because XOR != 0.
// Therefore, we remove this subarray, or don't add it to our answer (depending
// on how you do it).

// Observation 4: Knowing that the number of bits needs to be even.
// there are only 2 ways this can happen.
// odd-odd || even-even.
// so at any point of the prefix sum of set bits.
// we only consider the starting points where the set bits have an even value.
// if pref[i] is odd, then i only consider the odd pref[j] up to this point.
// if pref[i] is even, then i only conside the even pref[j] up to this point.
// and we can just add the total number of subarrays that satisfy this condition
// first.

// Obervation 5: After adding the subarrays that satisfy condition 1.
// we need to eliminate subarrays that do not satisfy condition 2.
// the check will be if maxn > pre[i]-pre[j-1]-maxn && (pre[i] -pre[j-1]) % 2 == 0
// maxn > pre[i]-pre[j-1]-maxn for condition 2 (make sure all bits cancel out).
// (pre[i] -pre[j-1]) % 2 == 0 for condition 1 (make sure its even number of set bits)
// if both of these condition is satisfied:
// => at the current [j,i], we have even number of set bits, but the bits 
// cannot cancel each other to give XOR == 0, so ans--, because its an invalid 
// subarray

// Final observation: maxn > pre[i]-pre[j-1]-maxn will only ever be true
// for up to 60 bits. So we only need to loop until j = i-60 at most.
// Why? Because a[i] <= 10^18, this means we only use up to 60 bits.
// In the worst case scenario, we can use pigeonhole-principle.
// if len(j,i) >= 61. Lets say that the number of set bits is 1 for all the values
// of a[i] in [j,i], so the total number of bits will be 61.
// then even if maxn=1 (lowest number of set bits available, note that a[i]>=1 so
// there is always at least 1 bit set) or maxn=60 (largest number of set bits)
// then maxn=1 > 62-1=61 || maxn=60 > 121-60=61 are always false.
// And any other values beyond length of 60 will always be false
// already.
// In other words, the condition that maxn > pre[i]-pre[j-1]-maxn will NEVER be true
// once we go beyond length of 60 (when we consider worse case scenario where each
// a[i] in [j,i] only has 1 set bit or 60 set bits).
// Therefore, we only need to loop for at most i-61 backwards to find the INVALID 
// subarrays.

// Time complexity: O(N*61)
// Space complexity: O(N)

void solve() {
    int n, m, k;
    cin >> n;
    ll ans = 0;
    dp[0] = 1; // base case, 0 is even, so we add 1 to even parity count.
    
    for (ll i = 1, x; i <= n; i++) {
        cin >> x; 
        cnt[i] = __builtin_popcountll(x);
        pre[i] = pre[i-1] + cnt[i];
        ans += dp[pre[i] % 2]; // Increment answer based on parity of prefix sum

        // Check for conditions within the range of i-61 to i
        for (int j = i, maxn = 0; j >= 1 && j>=i-61; j--){
            maxn = max(maxn, cnt[j]); // Track the maximum number of 1-bits
            if (maxn > pre[i]-pre[j-1]-maxn && (pre[i]-pre[j-1]) % 2 == 0) ans--;
            
        }
        dp[pre[i] % 2]++; // increment the count for the next transition.
    }
    
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
