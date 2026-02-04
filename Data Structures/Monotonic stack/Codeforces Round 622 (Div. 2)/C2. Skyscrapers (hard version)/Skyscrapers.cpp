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

// 1900 aint got no shit on me
// EZ problem, no cap.
// Idea: they say they dont want  a[j] > a[i] < a[k]
// => they want a[j] <= a[i] <= a[k] || a[j] >= a[i] >= a[k] 
// || a[j] <= a[i] >= a[k]
// Then start building the idea from here.
// Notice that, a[j] <= a[i] <= a[k] && a[j] >= a[i] >= a[k] is monotonic
// increasing and monotonic decreasing.
// while a[j] <= a[i] >= a[k] is monotonic increasing from 0 to i, then 
// monotonic decreasing from i to n-1.
// so from here, we know that the array will have a best "peak" position
// such that we can expand from there greedily.
// Initially, I thought we just needed to find the max value in the array.
// But, i'm wrong. Actually, the best way to do it is to just 
// try all positions.
// And we can do it with a monotonic stack.
// note that, greedily, whenever a[j] > a[i]. We want to set a[j] to a[i].
// This allows us to maximize our floors while still maintaining the condition
// stated above.
// so we can use a monotonic stack from left to right, and another from right
// to left.
// from left to right, we want the monotonic stack to be increasing.
// from right to left, we want the monotonic stack to be increasing.
// This allows us to be in the form:
// ... <= x3 <= x2 <= x1 <= i >= x4 >= x5 >= x6 >= ...
// and we calculate the maximum sum (or maximum floors) as we iterate.
// if st.top() > a[i], then we need to pop st.top()
// because we are currently in the form a[j] > a[i].
// so we need to set a[j] to a[i].
// and we keep popping until st.top() <= a[j].
// then finally we keep track of the sum.
// we repeat the same idea from left to right and right to left.
// Note that this take O(4N) time.
// each element will be popped at most twice.
// We can use a trick, I call it the "merging trick"
// if st.top() > a[i].
// we merge this st.top() value with a[i].
// so the count will +1, because a[i] is joined with it.
// see the code below for clarity.

// once done, we can then iterate through each position again.
// we get the total sum, and the one with the largest sum is the index we
// want to expand from (because that gives us the best result). 
// there could be multiple indexes, but it doesn't matter because there could
// be multiple answers.

// finally, we start expanding from target idx, right to left and left to right
// while obeying the rules stated above:
// ... <= x3 <= x2 <= x1 <= i >= x4 >= x5 >= x6 >= ...
// because this is the best way to construct the array for the maximal floors.
// if the current element is bigger than the previous element
// we just make it equal, otherwise we go to the next index.
// This part is just greedy.

void solve() {
	int n, k, m;
    cin >> n;

    vi a(n);
    for (int& x: a) cin >> x;

    stack<pll> st; // F=count,S=value 
    vll leftSum(n, 0);
    for (int i=0; i<n; i++){
        if (i > 0) leftSum[i] = leftSum[i-1];
        int count = 1;
        while (!st.empty() && st.top().S > a[i]){
            // cout << st.top().S << endl;
            count += st.top().F; // merging technique
            leftSum[i] -=  st.top().F*(st.top().S - a[i]);
            st.pop();
        }
        st.push({count, a[i]});
        leftSum[i] += a[i];
    }

    st = stack<pll>();
    vll rightSum(n, 0);
    for (int i=n-1; i>=0; i--){
        if (i < n-1) rightSum[i] = rightSum[i+1];
        int count = 1;
        while (!st.empty() && st.top().S > a[i]){
            // cout << st.top().S << endl;
            count += st.top().F; // merging technique
            rightSum[i] -=  st.top().F*(st.top().S - a[i]);
            st.pop();
        }
        st.push({count, a[i]}); // merging technique 
        rightSum[i] += a[i];
    }

    // printVector(leftSum);
    // printVector(rightSum);
    
    // find target index
    int bestIdx;
    ll maxAns = -1;
    for (int i=0; i<n; i++){
        // subtract a[i] because my code double counts a[i].
        if (leftSum[i]+rightSum[i]-a[i] > maxAns){
            bestIdx = i;
            maxAns = leftSum[i]+rightSum[i]-a[i];
        }
    }

    for (int i=bestIdx+1; i<n; i++){
        if (a[i] > a[i-1]) a[i] = a[i-1];
    }

    for (int i=bestIdx-1; i>=0; i--){
        if (a[i] > a[i+1]) a[i] = a[i+1];
    }

    printVector(a);

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
