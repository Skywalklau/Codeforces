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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vstr = vector<str>;
using vpvivi = vector<pair<vector<int>,vector<int>>>;

#define mset multiset
#define mmap multimap
#define uset unordered_set
#define umap unordered_map
#define umset unordered_multiset
#define ummap unordered_multimap
#define pqueue priority_queue

#define all(v) (v).begin(), (v).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define clr(x) x.clear()
#define pb push_back
#define rs resize
#define eb emplace_back
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

// This problem is ad hoc + understanding how to simplify the problem
// the resultant string s, must always be in the form of 
// 000...111...000...111...
// 111...000...111...000...
// if the first consecutive 0 or 1 is k
// then the next k elements must be the consecutive opposite
// this repeats for the next k elements again and again until the end of s.

// Knowing this, we essentially just want to find an index p such that we can
// perform the operation the question wants, to make s.
// notice that we can only do EXACTLY one operation
// which means that, if we find out that at any position, s[i] != s[i-1]
// it could mean either 2 things

// Case 1: it is a new interval k
// if it is new interval, we continue checking the string
// because up until that point, the string is in a valid form.

// Case 2: it is not a new interval k
// if it is not a new interval
// then we must perform an operation and check the resultant string s
// to see if the necessary condition holds, if not then it is impossible.
// Why? Because we can only perform one operation.
// If we see a case 2 scenario again, then we need to perform another operation
// which is invalid.

// With Case 2 in mind, there are a few more things to consider.
// if the number of consecutive characters up to s[i] != s[i-1] < k
// then we set p = i-1, and we can break since one operation is allowed only
// Why? Because that means the difference currently lies within the first interval
// if the number of consecutive characters up to s[i] != s[i-1] > k
// i.e. 0000 0011 0101 0111, k = 4
// then we need to set p = i-1-k;
// Why? Because the difference currently lies in the n-th interval, where n > 1.
// So essentially we can set this n-th interval as now the first interval in the
// new string s.

void solve() {
	int n, k, m;
    cin >> n >> k;

	str s;
	cin >> s;

	int count = 1;
	int p = -1;
    for (int i=1; i<=n; i++){
		if (i == n || s[i] != s[i-1]){
			if (count != k){
				p = i-1;
				if (count > k) p-=k;
				break; 
			}
			else count = 0;
		}
		count++;
	}

	if (p == -1){ // already k-proper, so just reverse the whole string
		cout << n << '\n';
		return;
	}
	else if (p == n-1){ // [n-1]s[n] becomes s[n][n-1] for any k is still wrong
		cout << -1 << '\n';
		return;
	}

	str a = s.substr(0, p+1);
	str b = s.substr(p+1, n-p-1);
	int left = 0, right = sz(a)-1;

	while (left <= right){
		swap(a[left], a[right]);
		left++;
		right--;
	}

	s = b + a; // make the new string s

	count = 1;
	for (int i=1; i<=n; i++){
		if (i == n || s[i] != s[i-1]){
			if (count != k){ // means more than one operation is needed so wrong
				cout << -1 << '\n';
				return;
			}
			else count = 0;
		}
		count++;
	}

	cout << p + 1 << '\n'; // 1-index
}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
