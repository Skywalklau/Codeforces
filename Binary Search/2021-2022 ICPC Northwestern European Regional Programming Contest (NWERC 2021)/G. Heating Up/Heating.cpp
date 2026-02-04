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
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits

// This was a nice problem, I was quite close to solving it, but I just
// couldn't figure out the optimization for the 2 pointers.
// What I did right:
// 1. binary search for answer.
// 2. Check for each valid starting point, 2 pointers to branch out
// to see if I can eat the whole pizza
// What I did wrong:
// This would take too long, because it would be O(N^2),
// we needed a way to optimize.But how?
// we can save the state of previously visited indexes and "jump" to the left
// pointer.
// proof:
// when we eat a pizza slice at index y
// and we get stuck on some index x and z, where x<y<z.
// => we do not have enough spice tolerance to eat beyond z and x.
// so we can just skip this point and go to z+1 to find a valid point.
// Why? Because even if I start at y+1,y+2...y+k where y+k<z. I would
// never be able to eat the pizza slice at z+1, because the sum 
// between x to z is less than z+1, then for sure the sum from x to z with
// y+k<z as the starting point will also be less than the pizza slice at z+1.
// so we can just skip to z+1 onwards.
// Another skip we can do is by moving backwards when we consider eating 
// a pizza in the left direction instead of the right.
// we can store the states of the indexes ex. state[z] = x.
// this way we can also "jump" from z to x, saving time.
// Why? Note that, previously we couldn't eat z+1 pizza slice.
// but later on, if we found a starting point where can manage to eat the 
// z+1 pizza slice, then for sure we can eat the z to x pizza slice already.
// because the pizza slice value at z+1 > sum of all pizza slice values
// from x to z.
// so implicitly we can just skip from z to x.
// and that is the idea to optimize, which allows us to iterate up to 2n only.
// for every logn.
// (2n because its circular and its a common trick to duplicate the whole array
// if its circular for easier iterations).
// By doing so, we can reduce the time complexity to O(nlogn)
// space complexity will be O(n) 

bool check(ll tolerance, vll& s, int n, vll& pref){
    vi state(2*n+1);
    for (int i=1; i<=2*n; i++){
        if (tolerance >= s[i]){
            int left = i, right = i;
            while (right-left+1<n){
                ll curTolerance = pref[right] - pref[left-1] + tolerance;
                if (right+1 <= 2*n && curTolerance >= s[right+1]){ 
                    right++;
                    continue;
                }
                if (curTolerance >= s[left-1]){
                    left = state[left-1];
                    continue;
                }
                break;
            }

            if (right-left+1>=n) return true;
            state[right] = left; // save the state for jumping
            i = right; // jump to right+1 (i = right because for loop has i++)
        }
        else{
            state[i] = i; // not enough tolerance to eat s[i]
            // => we can only jump to itself.
        }
    }
    return false;
}


void solve() {
	int n, k, m;
    cin >> n;

    vll s(2*n+1);
    ll low = MAX,high = -1;
    for (int i=1; i<=n; i++){
        cin >> s[i];
        s[i+n] = s[i];
        low = min(low, s[i]);
        high = max(high, s[i]);
    }


    vll pref(2*n+1, 0LL);
    for (int i=1; i<=2*n; i++) pref[i] = s[i] + pref[i-1];

    ll ans;
    while (low<=high){
        ll mid = low + (high-low)/2;
        //cout << mid << endl;
        if (check(mid, s, n, pref)){
            high = mid-1;
            ans = mid;
        }
        else low = mid+1;
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
