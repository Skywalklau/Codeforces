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

// Constants
const int MAX = int(1e9 + 5);
const ll MAXL = ll(1e18 + 5);
const ll MOD = ll(1e9 + 7);
const ll MOD2 = ll(998244353);

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

int n, k, m;
vpvivi d;
vpvivi temp;
vi a,b;
vi a1,a0,b1,b0;

// intution: initially i thought it was dp
// but it became clear it was divide and conquer later on.
// Let AND == bitwise and of the whole array for a[i] & b[i]
// Let XOR == bitwise xor of the whole array for a[i] ^ b[i]
// It is very obvious we must look at this problem bit by bit since the brute force
// can't work, and loop through 0 to 2^30 is too large.
// To maximize, we must always look from the MSF to the LSF.
// For every bit, if there exists a combination such that the XOR is 1
// then this bit can be taken and added to our result.
// How do we know?
// The answer is when the count of 0 bits in a == count of 1 bits in b at each bit and
// similarly when count of 1 bits in a == count of 0 bits in b at each bit
// Actually we just need to check one, because this condition is iff.
// so if one is true the other is automatically true.
// Lets say we found a valid bit that gives 1 when we AND the both arrays.
// now we must check this each subset from the array that we split
// and the same condition must hold then we can split again.
// in fact, the condition must hold for all subsets in order for the current bit to be 1
// so that we can add this current bit to our result.
// divide and conquer, rinse and repeat until the 0th bit.
// Time complexity: O(30 * N) == O(N)

void solve() {
    cin >> n;

    a.rs(n);
    b.rs(n);
    clr(d);

    for (auto& x: a) cin >> x;
    for (auto& y: b) cin >> y;

    d.pb(mp(a, b));
    int result = 0;
    bool flag = false;

    for (int bit=29; bit>=0; bit--){
        flag = false;
        clr(temp);
        for (int i=0; i<sz(d); i++){
            clr(a1), clr(a0), clr(b1), clr(b0);

            for (int j=0; j<sz(d[i].F); j++){
                if (d[i].F[j] & (1 << bit)) a1.pb(d[i].F[j]);
                else a0.pb(d[i].F[j]);
                if (d[i].S[j] & (1 << bit)) b1.pb(d[i].S[j]);
                else b0.pb(d[i].S[j]);
            }

            if (sz(a1) == sz(b0)){ // implicity handles sz(a0) == sz(b1)
                // VERY IMPORTANT: make sure its not 0 in size otherwise you get hacked!
                if (sz(a0)) temp.pb(mp(a0, b1));
                if (sz(a1)) temp.pb(mp(a1, b0));
            } 
            else{
                flag = true;
                break;
            }
        }

        if (flag) continue;
        result += (1 << bit);
        d = temp;
    }

    cout << result << '\n';

}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
