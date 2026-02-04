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

const int N = 1e6 + 5; // change according to your needs
vi mn(N, 0); // Smallest prime factor of each number
vvi fcv(N); // Prime factorization for each number (only returns each distinct factor once)


void precompute_prime_factors() { // Modified Sieve
    mn[1] = 1; // Base case: 1 has no prime factors
    for (int i = 2; i < N; i++) {
        if (!mn[i]) { // If i has no prime factor recorded yet, it is a prime number.
            for (int j = 1; j * i < N; ++j) {
                if (!mn[i * j])
                    mn[i * j] = i; // Mark i as the smallest prime factor for all multiples of i.
            }
        }
    }

    // Generate prime factor lists for every number up to N
    for (int i = 1; i < N; i++) {
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
 
ll binpow_by_mod(ll a, ll b, ll mod){
	ll ans = 1;
	while (b) {
		if ((b & 1) == 1) {
			ans *= a;
			ans %= mod;
		}
		b >>= 1;
		a *= a;
		a %= mod;
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


// This is a very nice problem, eventhough I did not solve it
// I am quite satisfied with my approach.
// I identified we needed binary search + dp
// then we needed to figure out how to assign w and f optimally
// so I thought about binary searching for t
// then the total f is t*f and total w is t*w
// then from there we can dp with 3 states
// dp[f || w][x (number of monsters, which can be 2 1D arrays)][strength left of f || w]
// stores the minimum time so far to kill x monsters
// but from here I kept confusing myself because I had too many states at this point
// and I couldn't continue
// This is a well-known knapsack problem:
// Since we know the strengths of each monster (or the weight of each item)
// and we can assign two things in some order optimally
// we can use knapsack dp for each item up to their total strength (or weights)
// the recurrence relation will be dp[i] = dp[i] || d[i - strength (or weight)]
// base case is dp[0] = true, because it is always possible to assign nothing to 
// a sum of subsets that equals to 0

// I was very close to solving this problem, but I didn't know the trick to the dp
// But now I know...

void solve() {
	int n, w, f;
    cin >> w >> f >> n;

    vi monsters(n);
    int totalStrength = 0;

    for (int &x : monsters){
        cin >> x;
        totalStrength += x;
    }

    // dp[i] = true : It is possible to allocate i water mana using a SUBSET
    // of monster strengths
    // Example: Let’s say:
    // strength = 6 (current monster’s strength).
    // dp[10] = true (it’s possible to achieve a sum of 10 using previous monsters).
    // Then, we update dp[16] = true because:
    // If we can achieve 10 mana and we add this monster's 6 mana, we can achieve 
    // 16 mana.
    // we move backwards from totalStrength to strenth to prevent overwriting current
    // dp states.
    vb dp(totalStrength + 1, false);
    dp[0] = true; // allocating 0 mana is always possible.
    for (int strength : monsters){
        for (int j = totalStrength; j >= strength; j--){
            dp[j] = dp[j] || dp[j - strength];
        }
    }

    // Binary search for minimum seconds `t`
    // max t needed for any array of monsters:
    // high = ceil(totalStrength / min(w, f))
    // I could figure this part out as well, just not the dp transition...
    int low = 1, high = (totalStrength + max(w, f) - 1) / max(w, f);
    while (low <= high){
        int mid = (low + high) / 2;

        // Total mana available at time `mid`
        ll maxWater = 1LL * mid * w;
        ll maxFire = 1LL * mid * f;

        bool possible = false;
        for (int waterUsed = 0; waterUsed <= totalStrength; waterUsed++){
            if (dp[waterUsed]){
                ll fireRequired = totalStrength - waterUsed;
                if (waterUsed <= maxWater && fireRequired <= maxFire){
                    possible = true;
                    break;
                }
            }
        }

        if (possible) high = mid - 1;
        else low = mid + 1;
    }

    // Linear approach:
    // int ans = 2e9;
    // for (int i = 0; i <= totalStrength; ++i){
    //     if (dp[i]){
    //         I could figure out this part as well... 
    //         at least for the total time of w and f, and we need to take the max.
    //         time of w : (i + w - 1) / w
    //         time of f : (totalStrength - i + f - 1) / f)
    //         ans = min(ans, max((i + w - 1) / w, (totalStrength - i + f - 1) / f));
    //     }
    // }
    // cout << ans << '\n';
    cout << low << '\n';
}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
