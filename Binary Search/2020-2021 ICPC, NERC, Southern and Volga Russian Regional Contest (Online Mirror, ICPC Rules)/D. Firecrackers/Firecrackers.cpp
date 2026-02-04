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

// solve time ~ 33 mins
// Ez clap. I'm fucking ready for UKIEPC.
// We can use bs. The first thing to notice is that the 
// total number of fireworks the hooligan can light up is abs(a-b)-1.
// let x = abs(a-b)-1, this means that the total number of fireworks
// then can be lit is min(x, m), let y= min(x,m).
// since we want to light as many fireworks as possible, it makes
// sense to sort the m fireworks based on the time needed to explode
// we get the y smallest fireworks in terms of time to explode.
// Now, just because we can take y fireworks to light it up, this does
// not imply that the all y fireworks will explode, so it we need to 
// check how many of the y fireworks actually managed to explode.
// We solve this via greedy + bs.
// Obviously, you want to light the firework that takes the longest 
// to explode first (because otherwise you might not be able to 
// explode it when you could've if you lit it up earlier)
// So, we always light up the fireworks that take the longest first,
// from largest to smallest, and since y is sorted (because m is sorted)
// then we just need to go from right to left while keeping track of the 
// time needed to light up the fireworks.
// Now, what is the total time the hooligan can survive for?
// if a < b, then the total time is b-1.
// if a > b, then the total time is n-b.
// lets call it st. Then, we can bs y.
// we check, via getMaxT, the min time needed to light up ALL fireworks
// in this subset of y.
// if the min time needed is > st, then we need to take a smaller 
// subset of y.
// else we can take a larger subset.
// We can do this via bs.
// Then we keep repeating until we get the best answer.

// Time complexity: O(MLOGM)
// Space complexity: O(M)

int getMaxT(vi& nums, int mid){
    int maxt = 0, t = 1;
    for (int i=min(sz(nums)-1, mid); i>=0; i--, t++){
        //cout << nums[i] << " " << t << endl;
        maxt = max(maxt, t + nums[i]);
    }
    //cout << maxt << endl;
    return maxt;
}

void solve() {
	int n, k, m, a, b;
    cin >> n >> m >> a >> b;
    
    vi s(m);
    for (int &x : s) cin >> x;

    int x = abs(a-b)-1; // max no. of fireworks we can light before caught

    sort(all(s));
    vi nums;
    for (int i=0; i<min(x, m); i++) nums.pb(s[i]);

    int st = 0; // survival time
    if (a > b) st = n - b;
    else st = b-1;

    //printVector(nums);
    int low = 0, high = sz(nums)-1, ans = -1;
    while (low <= high){
        int mid = low + (high-low)/2;
        // cout << mid << endl;
        if (getMaxT(nums, mid) <= st){
            low = mid+1;
            ans = mid;
        }
        else high = mid-1;
    }

    cout << ((ans == -1) ? 0 : ans+1)<< '\n';
    

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
