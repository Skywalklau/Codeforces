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
const int MAXN = 1e5+5; // fenwick = N, trie  = N * number of bits

// THIS PROBLEM WAS WAY TOO HARD BRUH, TOOK ME LIKE 2 HRS TO UNDERSTAND
// The logic is easy to get, and I knew what to do, but the dp is soooo hard.
// Nonetheless, I learned a new trick for prefix + suffix count dp.
// My gosh, where do I even begin...
// So, the idea to solving this problem is pretty simple, and I could get it as well
// we want f(x,y) ^ f(y,z) > f(x,z)
// Notice that, f(x,y) ^ f(y,z) = f(x,z) ^ a[y].
// So, the inequality becomes f(x,z) ^ a[y] > f(x,z)
// What does this tell us?
// It tells that, for any subarray from x to z (indexes), where x<=z, 
// there can be any index y between x to z, where x<=y<=z,
// such that we want a[y] to decrease the value of f(x,z) when we include
// the contribution of a[y] to when we don't include the contribution of a[y]
// in f(x,z).
// Meaning: if I have a[x]^a[y]^a[z], then I want a[x]^a[z] > a[x]^a[y]^a[z]
// => I want the value of a[x]^a[z]=f(x,z)^a[y] to decrease when I plug in a[y],
// which becomes a[x]^a[y]^a[z]=f(x,z).
// So now, the question becomes:
// How many subarrays can I find such that a[y] decreases the XOR from x to z such
// that x<=y<=z.
// The next question to ask now is: How do we know when a[y] decreases f(x,z)
// from f(x,z)^a[y]?
// The answer is to look from the MSB of a[y].
// if at the MSB of a[y], the bit value of f(x,z) at that bit position is also set,
// then 1^1 can be equal to 0 at that bit position, therefore decreasing the value
// of f(x,z)^a[y] when we include a[y].
// Why MSB? Because of the well known inequality: 2^i > 2^(i-1) + 2^(i-2) + ... + 2^0
// Hence, if we can switch off the MSB of a[y], then regardless of what other bits
// behind the MSB of a[y] we turned on, it will never be greater than the MSB of a[y].
// Hence, we check from the MSB.
// Good, here comes the hard part.
// How do we find such subarrays?
// Answer: using prefix + suffix count dp.
// for each a[y], we consider its prefix and suffix to find all the combination
// of ways to turn off the MSB of a[y] in f(x,z)^a[y].
// And actually, there are only 2 ways: 
// Since the MSB of a[y] is 1 (duhh)
// then, if the prefix subarray is 1, then we take the suffix subarray of 0
// why? Because prefixAllSubarrays[1] ^ 1 ^ suffixAllSubarrays[0]
// = 1^1^0=0 => decrease f(x,z)^a[y]
// Likewise, if the prefix subarray is 0, then we take the suffix subarray of 1
// Why? Because prefixAllSubarrays[0] ^ 1 ^ suffixAllSubarrays[1]
// = 0^1^1=0 => decreases f(x,z)^a[y]
// Good, now lets talk about how to actually build the prefix + suffix counts
// There are 3 states (crazzy), the bit position, the number of elements,
// and the bit state
// Hence the prefix and suffix can be written as:
// int pref[30][MAXN][2];
// int suff[30][MAXN][2]; 
// The goal: We need to find the prefix and suffix subarrays starting points
// for every bit position, and for the 2 types of bits (0 and 1) at every element
// I will explain as you read the code below how the idea works.

int pref[30][MAXN][2];  // Prefix COUNT for each bit, 0 or 1
int suff[30][MAXN][2];  // Suffix COUNT for each bit, 0 or 1

void solve() {
    int n;
    cin >> n;
    vi a(n+1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // Initialize suffix count
    for (int i = 0; i < 30; i++) {
        suff[i][n+1][0] = suff[i][n+1][1] = 0;
    }

    // Precompute prefix and suffix count for each bit position
    for (int bit = 0; bit < 30; bit++){
        // Calculate prefix count for the current bit
        for (int i = 1; i <= n; i++){
            int currentBit = (a[i] & (1 << bit)) ? 1 : 0; // Check if the bit at position `bit` is set
            for (int xorValue = 0; xorValue < 2; xorValue++){
                // Now, for both states, let me explain.
                // We want up to every i for each bit position, both states
                // where the number of subarrays up to this point is set as
                // 0 or 1 at this index position.

                // case 1: when this bit is set for a[i]
                // when this bit is set, this means we have a new addition of 
                // a subarray starting point for when the prefix is 1 at this bit 
                // and index position.
                // Why? Because a[i] itself can be a new starting point for a subarray
                // with the bit set at this bit position
                // Hence we do pref[bit][i][1] = 1 + pref[bit][i-1][0];
                // the +1 comes from a[i] itself contributing to a new starting point
                // as for pref[bit][i-1][0], we take it because when we want
                // the number of subarrays starting point up to this point that is 1 
                // at this bit so we must take the prefix with 0 set previously so 
                // that 1^0=1
                // if we took pref[bit][i-1][1] it would be wrong because 1^1=0, but
                // we want the state for pref[bit][i][1], where the bit is set.

                // Now, we also want the state for pref[bit][i][0]
                // this would just be pref[bit][i][0] = pref[bit][i-1][1];
                // Why? Because since this bit for a[i] is set, when we want the 
                // number of starting points for which the prefix is 0 so far
                // it would be taking pref[bit][i-1][1] as 1^1=0.
                // So, taking this element a[i] itself with all the prefixes
                // starting points with 1 will make all the prefixes starting points
                // at this bit and index position to 0. Again, because 1^1=0.
                // And the reason why we don't add 1 is because we cannot just 
                // consider a[i] itself, as a[i] is set at this bit, but we want
                // the state where the prefix starting points are 0.
                // So we must take all prefix starting points previously with this
                // new element a[i] so that their xor will make 0.

                // case 2: when this bit is not set for a[i]
                // This is the same logic, but reversed.
                // for the case pref[bit][i][1], since the current bit in a[i] 
                // is not set, we want to take pref[bit][i][1] so that 1^0 = 1.
                // hence pref[bit][i][1] = pref[bit][i][1] when a[i] is not set
                // at this bit
                // similarly for pref[bit][i][0], since the current bit is a[i]
                // is not set, we want to take pref[bit][i][0]  so that 0^0 = 0.
                // hence pref[bit][i][0] = 1 + pref[bit][i][0].
                // again, the +1 comes from a[i] itself contribuing a new starting point
                // subarray.

                if (currentBit == xorValue){
                    pref[bit][i][xorValue] = 1 + pref[bit][i-1][0];
                } 
                else{
                    pref[bit][i][xorValue] = pref[bit][i-1][1];
                }
            }
        }

        // Calculate suffix count for the current bit
        for (int i = n; i >= 1; i--){
            int currentBit = (a[i] & (1 << bit)) ? 1 : 0;  // Check if the bit at position `bit` is set
            for (int xorValue = 0; xorValue < 2; xorValue++){
                // The exact same logic applies from prefix to suffix
                // except we do i+1 instead of i-1 (cuz its suffix bruh).
                if (currentBit == xorValue){
                    suff[bit][i][xorValue] = 1 + suff[bit][i + 1][0];
                } 
                else{
                    suff[bit][i][xorValue] = suff[bit][i + 1][1];
                }
            }
        }
    }

    ll ans = 0;

    // This is where we calculate the answer for each a[y].
    for (int i = 1; i <= n; i++){
        int MSB = 31 - __builtin_clz(a[i]);
        ans += 1LL * pref[MSB][i-1][1] * (1 + suff[MSB][i+1][0]);
        ans += 1LL * (1 + pref[MSB][i-1][0]) * suff[MSB][i+1][1];
        // Now you might be asking, why +1 again.
        // Its the same logic from the prefix + suffix computation.
        // Remember what our goal is, we are trying to get all the subarrays
        // such that f(x,z) ^ a[y] > f(x,z).
        // we know that a[y] is always set at the MSB (duhh), so in order for 
        // our f(x,z) to decrease when we include a[y], we want 1^1=0, and not other
        // scenario. Because 0^0=0, which does not decrease, and 1^0 || 0^1 increases.
        // so only 1^1 is suitable.
        // Knowing this, there are 2 ways to sum up the combinations.
        // when pref is 0, and suff is 1.
        // or when pref is 1, and suff is 0.
        // a[y] is always 1 at the MSB.
        // so the answer is (1+pref[0]) * suff[0] because we pair all the a[y] to
        // the pref[0] so that 1^0=1, and then with the suff[0] it becomes 1^1=0
        // which decreases. The +1 comes from the subarray a[y] itself. Because
        // for each calculation we are not including a[y] yet, so we need to include
        // a[y] into pref[0] || suff[0] so that 1^0=0 or if we consider just a[y]
        // by itself, then it would be just 1. In both cases, we will then
        // xor with pre[1] || suff[1] to make 1^1=0, ultimately decreasing f(x,z).
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
