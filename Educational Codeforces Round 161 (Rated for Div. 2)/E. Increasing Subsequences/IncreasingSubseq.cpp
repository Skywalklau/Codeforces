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

// nice problem
// Reading the problem, my intution told me instantly that we can very easily 
// find an array >= X
// by making a sorted array of stricly increasing elements
// But after some sketces I noticed it would be hard to get exactly X
// So we have to figure out something else.
// Initially, I noticed that by adding a new maximum element each time,
// we can increase our total increasing subseq by 2 times.
// Which gave me the idea to think of X as binary
// And we should obviously start from MSF to build a binary number from a decimal number
// if the ith bit of X is set,
// lets say i = 42
// then we can make an array [1,2,3...,42] which can fulfill the 42nd bit of X
// and we repeat this for the next consecutive bits
// if the next bit is 40
// now our array would be [1,2,3,...,42,1-40,1-39,1-38...1,1]
// this would work, but its too big
// so we have to optimize it more
// then I noticed that, since we start from the MSF
// lets say if the MSF is 39
// then our array can be [1,2,3...39]
// then lets say the next bit is 25
// so actually we can just add 26 at the end of the array [1,2,3,...,39,26]
// why this works?
// so we know the number of increasing subseq from [1,2,3...39] is 2^39-1 (excluding
// empty subset)
// then by adding 26, we can form the rest of the increasing subseq with these 
// numbers [1,2,3...26], where 26 is the last element, not the first occurence
// of 26
// from here, its just combinations, given that 26 is included in our set
// how many ways can we choose numbers from [1,2,3...25] to include in our set
// the answer is 2^25
// hence now we have successfully added the 25th bit to X
// and we just repeat this process, for each bit that is found
// we just add bit+1 to get another 2^bit combinations to our answer such
// that we can form X in terms of binary.
// Also, not that I said 2^39-1, so you would think we need to add any number
// number <= 1 explicitly in the end
// but no, because when the final array is formed, we can now include the 
// empty subsequence as an increasing subsequence which implicitly handles
// the 2^39-1 to 2^39-1+1 = 2^39.

void solve() {
	int n, k, m;
    ll X;
    cin >> X;

    vll result;
    ll num = 1;
    int count = 0;
    bool firstSubseq = true;
    for (ll bit=59; bit>=0; bit--){
        if (X & (1LL << bit)){
            if (firstSubseq){
                for (int i=num; i<num+bit; i++) result.pb(i);
                firstSubseq = false;
            }

            else{
                result.pb(bit+1);
                count++;
            }
        }
    }

    cout << sz(result) << '\n';
    printVector(result);

}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
