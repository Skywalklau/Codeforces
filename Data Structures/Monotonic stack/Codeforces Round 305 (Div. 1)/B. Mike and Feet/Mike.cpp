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

// Nice problem, classic USACO gold type problem.
// The intuition to solve this problem
// is to first realize that essentially what we are trying to find
// is the max value of all window sizes.
// where the max value is the min of a window.
// This gives quite an obvious hint for monotonic stacks.
// Why? min/max values within a certain window => monotonic stacks (usually).
// In any case, monotonic stacks are a good candidate solution.
// But before we conclude its monotonic stacks, we need to determine how 
// to solve this problem first, and see if it can be used.
// Realize that, to solve this problem, we actually can compute, for each 
// a[i], the largest window it contributes towards.
// [1,2,3,4,5,6].
// lets take a[2] == 3, the largest window it contributes is of size 4, that is,
// [1,2,(3,4,5,6)].
// and we can propagate this idea to all elements.
// then once we are done, we can then compute for all the sizes that we have
// found, the maximum at each size (since multiple a[i] for some i will
// contribute to the same window size as the min value within the window).
// And thats the intuition to solve this problem.
// A brute force solution would be O(n^2), via two pointers at each index.
// However, notice that, we want to find the maximum window size for each
// element, what does that mean?
// First of all, what dictates a window size? Well, the moment a[i] < a[j]
// for some j<i or j>i.
// then we take the window size from there.
// in other words, the window will look something like [3,2,1,2,3]
// if we start at a[2]==1.
// the reason we dont go beyond a[0] is because a[-1] < a[2], and a[2] > a[5].
// thats why our window stops at [0,4].
// Observation: there is a monotonic property.
// => monotonic stacks
// or more specifically, this is a variant of next greater element type problem.
// Instead, we want to find the next smaller element, on both left and right
// perspectives.
// then we can use the 2 edge index points, call it k, and h, where h>k.
// and do h-k-1 to get the window size.
// and then from there ans[h-k-1] = max(ans[h-k-1], a[i]).
// for every single element that has the window size of h-k-1.

// Time complexity: O(N)
// Space complexity: O(N)

void solve() {
	int n, k, m;
    cin >> n;

    vi a(n);
    for (int& x: a) cin >> x;

    vi prev_smaller(n, -1), next_smaller(n, n);
    stack<int> st;

    // get next smaller element
    // monotonic increasing stack
    for (int i=0; i<n; i++){
        // while (!st.empty() && a[st.top()] >= a[i]) st.pop();
        // if (!st.empty()) prev_smaller[i] = st.top();
        while (!st.empty() && a[st.top()] > a[i]){
            next_smaller[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    //printVector(prev_smaller);

    while (!st.empty()) st.pop();
    
    // get previous smaller element
    // monotonic increasing stack
    for (int i=n-1; i>=0; i--){
        // while (!st.empty() && a[st.top()] >= a[i]) st.pop();
        // if (!st.empty()) next_smaller[i] = st.top();
        while (!st.empty() && a[st.top()] > a[i]){
            prev_smaller[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    //printVector(next_smaller);
    // printVector(next_smaller);
    // printVector(prev_smaller);

    vi max_strength(n+1, 0);
    for (int i=0; i<n; i++){
        int size = next_smaller[i] - prev_smaller[i] - 1;
        max_strength[size] = max(max_strength[size], a[i]);
    }

    // since ans[i] >= ans[i+1] >= ans[i+2]...
    // Claim: if ans[k] == 0, then ans[k] == ans[k+1].
    // proof: lets say we found an answer for a window of size k
    // then the we aim to show that the answer for a window of size k
    // is the same as the ans of k+1 iff ans[k] == 0 initially.
    // ie. ans[k] == ans[k+1].
    // we know that, the ans array has a monotonic decreasing property.
    // because each consecutive index is a larger window, we know the 
    // answer for that window is always at least the previous answer from
    // the previous window (right to left perspective)
    // ie. ans[i] >= ans[i+1] >= a[i+2] ...
    // Now, if we didn't manage to find an answer for the size of k.
    // we can look at the answer of k+1.
    // and we know that the answer for index at k, is AT LEAST ans[k+1].
    // ie. ans[k] >= ans[k+1]
    // we aim to prove that actually, ans[k] == ans[k+1] iff ans[k] == 0.
    // we know that we have the answer for ans[k].
    // its window is [x1,x2,...,xk]
    // now, notice that, since this is the best answer for the size of k.
    // => one of the elements within this window is ans[k+1].
    // ie. ans[k+1] == x(n) where 1<=n<=k.
    // ex. x3 could be the answer, or xk, or x1 or anything else in between.
    // now, consider ans[k].
    // since window [x1,x2,...,xk] is the "best" window for ans[k+1].
    // => we know ans[k] lies in this window as well, because again we know
    // that ans[k] >= ans[k+1] >= ans[k+2] >= ...
    // now the question remains, how do we form the window of size k within
    // the window of size k+1.
    // It is obvious that there is only 2 ways to do this, which are:
    // [x1,(x2,...,xk+1)] or [(x1,x2,...),xk+1]
    // where the () denotes the window of size k+1.
    // we want to choose the best answer from (x2,...,xk+1) and (x1,x2...)
    // Notice that, actually, x1 == xk.
    // Why? We know that, x1 ends at x(k+2) because x(k+2) < x1.
    // similarly, xk+1 ends at x1 because x0 < xk+1.
    // => lets use contradiction to prove this.
    // assume that the numbers are not equal, xk+1 != x1.
    // for simplicity, although not formal, lets say x1==5, xk+1==4.
    // from k to 1, our window would be valid in because x1==5 > xk+1==4
    // and then it terminates at x0 becuase x0 < xk+1==4
    // however, from right to left, x1 would terminate before xk because x1>xk.
    // => our window would be smaller than k+1.
    // but that contradicts the statement that our window is of size k+1.
    // Hence, x1 == xk+1.
    // Knowing this, notice that regardless of which window, (x2,...,xk+1)
    // and (x1,x2...) we choose, since x1 == xk+1.
    // any other values chosen lies within both windows.
    // so regardless of where ans[k] lies within this window of size k+1,
    // both sub-windows of size k will contain ans[k+1].
    // => ans[k] = ans[k+1], because we always choose the min, and the min, 
    // which is ans[k+1], lies in both sub-windows.
    //printVector(max_strength);
    for (int i=n-1; i>=1; i--){
        max_strength[i] = max(max_strength[i], max_strength[i+1]);
    }

    for (int sz=1; sz<=n; sz++) cout << max_strength[sz] << " ";
    
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
