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

// To be honest, while this fun problem, I did not learn anything from it
// The key is is noticing that prime numbers are always odd, except 2.
// To construct the graph, we first need to realise 3 cases:
// case 1: even ^ even = 2 (since its prime)
// so we need 2 colours for this.
// case 2: odd ^ odd = 2 (since its prime)
// so we need 2 colours for this
// case 3: even ^ odd || odd ^ even = prime
// we need 2 colours for this

// what is the minimum colours we need for N>=7?
// lets look at this case by case
// even ^ even = 2 => we need 2 colours, 1 and 2
// odd ^ odd = 2 => we need 2 colours, can it be 1 and 2?
// lets try, if lets say we have 2 even to even nodes connected such that their XOR
// is prime which is 2.
// then we must have 2 colours
// then same thing for odd ^ odd = 2, we need 2 colours, lets say its 1 and 2 as well
// since we want the minimum number of colours
// so now even ^ even = 2 is coloured 1 and 2 respectively
// odd ^ odd = 2 is coloured 1 and 2 respectively
// note that for case 3, even ^ odd = prime is the problem
// why? Because if we take the even ^ odd = prime, then since even is coloured 1
// and an odd is also coloured 1, 1 connects to 1 is wrong
// so we must have 3 colours at least
// ok, then we make odd ^ odd = prime to be 3 and 2 respectively
// again, if even ^ odd = prime, lets say that the even node is 2,
// it could again connect to an odd node which is colored 2.
// => we need 4 unique colours at least to satisfy all case conditions
// hence from here we can conclude that we only need 4 colours for N>=7

// Now, the question is, how do we assign the colours to the numbers
// we know even ^ even, odd ^ odd need 4 colours respectively
// then how do we know what to assign for even ^ odd nodes?
// lets say for even ^ even nodes we make them 1 and 2 respectively
// and for odd ^ odd nods we make them 3 and 4 respectively
// now we just need to handle even ^ odd (odd ^ even is handled as well implicitly)
// so if a node is even, and it connects to an odd, it needs to be either 1 or 2
// since its odd nodes are 3 or 4
// a nice pattern that is the easiest to implement is to set
// even ^ even to 4 and 2 
// odd ^ odd, to 1 and 3
// then even ^ odd is (2 || 4) ^ (1 || 3)
// actually we can just do even ^ odd as 2 and 3, as an ascending sequence
// notice that, from 1 to 6
// if we put it in this pattern 1 2 3 4 1 2 3 4 1 2 3 4...
// its perfectly valid and easy to implement.

// The editorial is decent, although sus because a difference of multiple of d does not
// just imply xor is a multiple of d.
// d=4 is just a special case.
// Counterexample: x=6,y=3, so d=3, but 6^3=5.

void solve() {
	int n, k, m;
    cin >> n;
    if (n <= 6){
        if (n == 1) cout << 1 << '\n' << "1" << '\n';
        else if (n == 2) cout << 2 << '\n' << "1 2" << '\n';
        else if (n == 3) cout << 2 << '\n' << "1 2 2" << '\n';
        else if (n == 4) cout << 3 << '\n' << "1 2 2 3" << '\n';
        else if (n == 5) cout << 3 << '\n' << "1 2 2 3 3" << '\n';
        else cout << 4 << '\n' << "1 2 2 3 3 4" << '\n';
    }
	else{
        cout << 4 << '\n';
        for (int i = 0; i < n; i++) cout << i % 4 + 1 << ' ';
        cout << '\n';
    }
    
}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
