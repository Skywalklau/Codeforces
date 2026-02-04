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
const int MAXN = 1e6+5; // fenwick = N, trie  = N * number of bits

// No way this shit is 1800, felt like 2000+. THIS WAS SUCH A HARD PROBLEM
// We can solve this problem by doing 3D dp
// The hard part of this problem is knowing what to use as your states for
// the dp
// dp[i][x][y]
// i: The first i number from the array
// x: The parity of the 2nd last number in the subseq (0 for "even", 
// 1 for "odd", 2 for "does not exist")
// y: The parity of the last number in the subseq (0 for "even", 
// 1 for "odd", 2 for "does not exist")


const ll N = 200002;

ll dp[N][3][3];

void solve() {
    ll n;
    cin >> n;

    vll a(n + 1); // Array with 1-based indexing
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] %= 2; // Store parity (0 for even, 1 for odd)
    }

    // There is 1 way to build an empty subseq with no elements initially.
    // This may seem weird, but we actually will not be counting this state
    // at the end, we only count from >= 3 elements onwards
    // this dp is just used as a "building block" for the next states
    // Without this state we cannot build our valid states.
    dp[0][2][2] = 1; // Initialize base case
    ll ans = 0;

    for (ll i=1; i<=n; i++){
        // Carry forward previous states
        for (ll x = 0; x < 3; x++){
            for (ll y = 0; y < 3; y++) {
                dp[i][x][y] = (dp[i][x][y] + dp[i - 1][x][y]) % MOD2;
            }
        }

        // Add current number to subsequences
        // This chunk handles transition for new elements as the 1st/2nd
        // element in the subseq.
        // Why? Because at every index i a new subseq can form with
        // a[i] as either: 1st element(or last) || 2nd element (or 2nd last)
        for (ll y=0; y<3; y++){
            dp[i][y][a[i]] = (dp[i][y][a[i]] + dp[i - 1][2][y]) % MOD2;
            // Explanation: Why add dp[i-1][2][y]?
            // First of all, we need to understand that at every point
            // this current elememt can be the STARTING POINT (1st element)
            // of a subseq. So this is what we are handling.
            // To handle this, there are 3 scenarios:

            // Case 1: the last element exists, and its odd, i.e y==1
            // if this is the case, then our current element will now be 
            // the LAST/2nd element for this subseq, and y will be the 
            // 2nd last element/1st element in the subseq. 
            // Hence dp[i][y==1][a[i]] is the current state we 
            // are dealing with.
            // So what is the transition? We need to add it with the previous
            // state, which is dp[i-1][2][y==1].
            // => we add the state when y==1 was the last element (or the 
            // 1st depending on how you look at it) for the subseq when we
            // went through i-1 numbers so far. 
            
            // Case 2: the last element exists, and its even, i.e y==0
            // if this is the case, then our current element will now be 
            // the LAST/2nd element for this subseq, and y will be 
            // the 2nd last/1st element 
            // in the subseq. Hence dp[i][y==0][a[i]] is the current
            // state we are dealing with.
            // So what is the transition? We need to add it with the previous
            // state, which is dp[i-1][2][y==0].
            // => we add the state when y==0 was the last element (or the 
            // 1st depending on how you look at it) for the subseq when we
            // went through i-1 numbers so far.

            // Case 3: the last element doesn't exists,i.e y==2
            // if this is the case, then our current element will now be 
            // the LAST/FIRST element for this subseq, and y will be the 2nd last
            // element in the subseq. Hence dp[i][y==0][a[i]] is the current
            // state we are dealing with.
            // So what is the transition? We need to add it with the previous
            // state, which is dp[i-1][2][y==0].
            // => we add the state when y==0 was the last element (or the 
            // 1st depending on how you look at it) for the subseq when we
            // went through i-1 numbers so far.
        }

        // Handle transitions based on parity
        // This chunk of the dp handles when we have >= 2 elements
        // so adding this element will make the subseq have a length of >= 3
        if (a[i] == 1){
            // Current number is odd
            // There are 2 scenarios in which we can satisfy the condition:
            // sum of every three consecutive numbers is even.
            
            // Case 1: x==1 && y==0
            // => 2nd last element is odd, last element is even
            // => odd + even + (odd) == even, so its a valid subseq
            // Transition:
            // we add this element to the end of the subseq, so now the 
            // last element is an even number, and the 2nd last element
            // will be an odd number
            // Hence dp[i][0][1] would be the current state we are handling
            // we need to add this state from its previous state, which is
            // before adding the a[i] element as the last element in the subseq
            // so before adding, its state was dp[i-1][1][0].
            // hence the transition dp[i][0][1] += dp[i - 1][1][0]


            // Case 2: x==0 && y==1
            // => 2nd last element is even, last element is odd
            // => x=even + y=odd + (odd) == even, so its a valid subseq
            // Transition:
            // we add this element to the end of the subseq, so now the 
            // last element is an odd number, and the 2nd last element
            // will be an odd number
            // Hence dp[i][1][1] would be the current state we are handling
            // we need to add this state from its previous state, which is
            // before adding the a[i] element as the last element in the subseq
            // so before adding, its state was dp[i-1][0][1].
            // hence the transition dp[i][1][1] += dp[i - 1][0][1]

            dp[i][0][1] = (dp[i][0][1] + dp[i - 1][1][0]) % MOD2;
            dp[i][1][1] = (dp[i][1][1] + dp[i - 1][0][1]) % MOD2;
            ans = (ans + dp[i - 1][1][0] + dp[i - 1][0][1]) % MOD2;
        } 
        else{
            // Current number is even
            // There are 2 scenarios in which we can satisfy the condition:
            // sum of every three consecutive numbers is even.
            
            // Case 1: x==1 && y==1
            // => 2nd last element is odd, last element is odd
            // => x=odd + y=odd + (even) == even, so its a valid subseq
            // Transition:
            // we add this element to the end of the subseq, so now the 
            // last element is an even number, and the 2nd last element
            // will be an odd number
            // Hence dp[i][1][0] would be the current state we are handling
            // we need to add this state from its previous state, which is
            // before adding the a[i] element as the last element in the subseq
            // so before adding, its state was dp[i-1][1][1].
            // hence the transition dp[i][1][0] += dp[i - 1][1][1]


            // Case 2: x==0 && y==0
            // => 2nd last element is even, last element is even
            // => x=even + y=even + (even) == even, so its a valid subseq
            // Transition:
            // we add this element to the end of the subseq, so now the 
            // last element is an even number, and the 2nd last element
            // will be an even number
            // Hence dp[i][0][0] would be the current state we are handling
            // we need to add this state from its previous state, which is
            // before adding the a[i] element as the last element in the subseq
            // so before adding, its state was dp[i-1][0][0].
            // hence the transition dp[i][0][0] += dp[i - 1][0][0]

            dp[i][1][0] = (dp[i][1][0] + dp[i - 1][1][1]) % MOD2;
            dp[i][0][0] = (dp[i][0][0] + dp[i - 1][0][0]) % MOD2;
            ans = (ans + dp[i - 1][1][1] + dp[i - 1][0][0]) % MOD2;
        }

        // Ensure all values are modulo MOD2
        for (ll x=0; x<3; x++){
            for (ll y=0; y<3; y++){
                dp[i][x][y] %= MOD2;
            }
        }
        ans %= MOD2;
    }

    // we can also do sum(dp[n][0][0]+dp[n][1][0]+dp[n][0][1]+dp[n][1][1])
    // but due to big numbers we added ans on the fly and MOD2 on the way.
    cout << ans << '\n';
}


int main() {
    //fast_io();
    // precompute_factorials(MAXN, MOD);
    // int t;
    // cin >> t;
    // while (t--) solve();
    solve();
    return 0;
}
