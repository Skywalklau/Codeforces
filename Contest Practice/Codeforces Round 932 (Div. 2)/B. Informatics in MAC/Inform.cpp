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

// solve time ~ 45 mins
// Fun problem. The trick is to notice that we can just take 2 segments,
// and we don't need more.
// Proof:
// Let the mex of the whole array be x.
// We aim to prove that we cannot split the segments in such a way
// that we can get a mex of y for each sub-segment, where y < x.
// Consider some array, we take its sub-segment the moment its mex
// is y, we note the range down, [1,i] for some i < n.
// then now we just need to look at [i,n].
// Now, there are 2 cases to consider:
// Case 1: we cannot even get mex of y.
// Because we lack the numbers < y to make the mex of y from the remaining
// elements.
// This case is trivial, because then obviously that means we cannot
// find a valid answer.
// Case 2: we can get a mex of y.
// In this case, we further break it down into 2 cases:
// sub-case 1: we get mex of y, but then we have remaining elements
// after this part which are >=y (because y is not the max mex).
// So, if that part has all the values up to y-1, since y is not
// the max mex, we will have values y, y+1,... MEANING, this subarray
// will have mex > y. Hence its impossible
// sub-case 2: we get mex of y, but the next part (or the final part)
// will not have some values up to y, MEANING, we have gaps before
// we even reach y-1, and we still values >= y.
// Hence, this case is also impossible, because our mex is < y.
// In both cases, we proved that the segments MUST have the same mex,
// which is the max mex itself.
// So, we never need to split it into more than 2 parts since our
// goal must be to achieve the max mex anyways, the first segment
// (or 2nd segment can just include as many elements possible) until
// we reach the max mex itself, then the remaining elements goes
// to the 2nd part, where we will do another check to see if the mex
// is actually the max mex as well.
// If yes, then its the answer.
// Otherwise, its impossible.

void solve() {
	int n, k, m;
    cin >> n;

    vll a(n);
    for (ll& x: a) cin >> x;

    vll temp = a;
    sort(all(temp));
    temp.rs(unique(all(temp)) - temp.begin());
    // printVector(temp);
    ll mex = 0;
    for (ll x : temp){
        if (x == mex) mex++;
        else break;
    }

    // cout << mex << endl;
    vb visited(n, false);
    int cnt = 0;
    int start = -1;
    for (int i=0; i<n; i++){
        if (a[i] < mex && !visited[a[i]]){
            visited[a[i]] = true;
            cnt++;
        }
        if (cnt == mex){start = i+1; break;}
    }

    if (start < n && start != -1){
        vi remain;
        for (int i=start; i<n; i++) remain.pb(a[i]);
        sort(all(remain));
        int curMex = 0;
        for (int i=0; i<sz(remain); i++){
            if (remain[i] == curMex) curMex++;
        }

        if (curMex == mex){
            cout << 2 << '\n';
            cout << 1 <<  " " << start << '\n';
            cout << start+1 << " " << n << '\n';
        }
        else cout << -1 << '\n';
    }
    else cout << -1 << '\n';

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
