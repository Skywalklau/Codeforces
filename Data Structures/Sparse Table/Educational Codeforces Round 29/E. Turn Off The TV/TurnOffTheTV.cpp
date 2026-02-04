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

const int LOGN = 20; // sparse table
const int MAXN = 1e6+5; // fenwick, trie

const int LIMIT = 6e5 + 5;

int sparse[LOGN][LIMIT];

// Introduction to range query + sweep line via sparse table
// I will be honest, I had no idea how to do this problem.
// But its ok, I learned something new! This was also a really fun problem!
// New trick obtained: Difference array via prefix sums to perform range updates
// between intervals.
// The trick to solving this problem is to first compress everything into
// indexes (since its l and r > n we can just fit them within n)
// Then from there we perform bs to search for a particular element's idx (similar to 
// fenwick tree compressions style problems via prefix sums, e.g Petya and Array)
// After compression, here is where this genius trick comes into play, we use 
// we first initialize our prefix sum with whatever intervals exists
// via bs and update indexes of l by 1, and update indexes of r+1 by -1.
// Why? This is done to indicate that at the mapped index of l, a new interval
// starts, and at the mapped index of r+1, this interval ends.
// After doing so, we can compute our prefix sums on the prefix sum array itself.
// then boom, now our prefix sum contains all the ranges present within the interval
// where they exists.
// Like if there is an interval (3,6) and (4,9)
// our prefix sum would look something like [0, 1, 2, 2, 1]
// indicating that, in a number line, 0 to 2 has no interval present,
// 3 has one interval present, 4 has 2 intervals present, 
// 5 has 2 intervals present, and 5 to 9 there is 1 interval present
// Now, there is one thing to note, we need to add l-1 into our interval.
// This is a necessary condition, because if we don't we may leave out 
// "gaps" in our number line, incorrectly labelling numbers in the number line 
// that should have less intervals than it should.
// consider (1,7),(0,3),(5,8).
// our array would look something like [0,1,2,2,1,2,2,1]
// but without l-1, the array would look something like [1,2,2,2,2,1]
// Notice that, in between the 2's there is a 1 present in the first array, this
// correctly indicates that there is a "gap" in that number, which is 4.
// There should only be 1 interval present at the number 4
// But at the 2nd array, we did not indicate that, in fact, we assumed that its 
// continuous and at 4 there is 2 intervals present, when there isn't.
// Hence we need l-1.

// Proof that we need l-1:
// There are two cases to consider when comparing two intervals [l1, r1] and [l2, r2]:
// Case 1: The intervals overlap or are adjacent.
// Case 2: There's a gap between the intervals.
// In case 1, if the intervals overlap or touch, there is no gap. 
// We don't need to worry about these because the intervals are already "connected."
// In case 2, if there's a gap between the intervals (i.e., r1 < l2), we need to
// ensure that the compressed representation correctly includes the "gap."

// Non-gap case (overlapping or adjacent intervals): If r1 >= l2 - 1, then the 
// intervals are either overlapping or adjacent, meaning there is no actual gap. 
// In this case, adding l2 - 1 to the list does not cause any issue because the 
// intervals are still "connected" in the compressed space.

// Gap case (no overlap between intervals): If r1 < l2 - 1, then there is a gap
// between the intervals. By adding l2 - 1 to the compressed coordinate list, we 
// introduce a new point in the compressed space that correctly represents the gap. 
// This ensures that the gap between r1 and l2 is accounted for in the prefix sum 
// array.

// Specifically, the point l2 - 1 represents the "last" point of the first interval 
// [l1, r1] before the start of the second interval [l2, r2]. The prefix sum will 
// correctly mark that the first interval ends at r1, and there is no coverage after
// r1 until the second interval begins at l2. Thus, by introducing this gap point, 
// we effectively capture the transition from one interval to the other.

void createSparse(vi& pref, int n){
    for (int i=0; i<n; i++){
        sparse[0][i] = (pref[i] == 0 ? 1e9 : pref[i]);
    }
    for (int i=1; i<LOGN; i++){
        for (int j=0; j+(1<<i)<=n; j++){
            sparse[i][j] = min(sparse[i-1][j], sparse[i-1][j+(1<<(i-1))]);
        }
    }
}

int query(int l, int r){
    int k = 31 - __builtin_clz(r-l+1);
    return min(sparse[k][l], sparse[k][r-(1<<k)+1]);
}


void solve() {
	int n, k, m;
    cin >> n;

    vpii intervals;
    vi comp; // compressed array;
    for (int i=0; i<n; i++){
        int l, r;
        cin >> l >> r;
        intervals.pb({l, r});
        comp.pb(l-1);
        comp.pb(l);
        comp.pb(r);
    }

    
    sort(all(comp));
    comp.rs(unique(all(comp)) - comp.begin());
    auto getIdx = [&](int i){
        return lb(all(comp), i) - comp.begin();
    };

    vi pref(sz(comp), 0);
    // printVector(comp);
    for (int i=0; i<n; i++){
        int l = intervals[i].F, r = intervals[i].S; 
        pref[getIdx(l)]++;
        // cout << l << " " << getIdx(l) << endl;
        if (getIdx(r+1) < sz(comp)) pref[getIdx(r+1)]--;
    }

    for (int i=1; i<sz(comp); i++){
        pref[i] += pref[i-1];
    }

    //printVector(pref);
    createSparse(pref, sz(pref));
    
    for (int i=0; i<n; i++){
        int l = intervals[i].F, r = intervals[i].S;
        int li = getIdx(l), ri = getIdx(r);
        if (query(li, ri) > 1){
            cout << i+1 << '\n';
            return;   
        }
    }

    cout << -1 << '\n';

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
