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

// solve time ~ 1hr 8 mins
// This was quite a fun problem for me.
// Lets make some observations before solving.
// Observation 1: a[i] will | with elements up to i+m and down to i-m.
// Why? you can draw it out to understand and simulate it. I won't explain that here
// cuz its quite obvious when you draw it out.
// Observation 2: We cannot manually go up to i+m and down i-m.
// So, how can we speed this up?
// The trick is to look bit by bit.
// Lets consider going up to i+m first.
// Greedily, we obviously wanna set the first zero bit we see from bit 0 to bit 29.
// While we do that, we will go through some consecutive 1's, lets track this sum.
// On the first 0 bit we see, we need exactly 1 move to set this bit.
// So, we check if we have it, if yes, then we can set this bit.
// Then, we -= (1<<bit) to the number of moves we have.
// and ans |= (1<<bit) because we can set this bit.
// also add this new bit to our sum.
// Why do we -= (1<<bit) to the number of moves? 
// Because imagine you we have 001111
// then we wanna set the first 0 bit we see from right to left.
// if we have at least 1 moves left, we can set it.
// On to the next bit, how many moves we do we need? We need exactly (1<<bit) moves
// which includes that 1st move we used to set the first 0 bit to 1.
// Actually now that I think about it sum is redundant, because the diff is always 
// gonna be 1 anyways.
// So thats the idea for n+m.
// Now for n-m.
// Similar idea, we go from bit 0 to bit 29.
// Now we think differently, if this bit is set then we need exactly (1<<bit) moves
// to make this bit 0.
// So, we check if we can do it or not.
// if our number of move is at least 1, we can always do it.
// So, we -= (1<<bit) from our number of moves and we can | sum.
// where sum is all the bits we can flip on before this bit.
// Eg. 011000
// if we have at least 1 move, we can turn this bit off.
// and it becomes 010111. so we can do | 000111.
// and obviously we to then -= 000111 moves to remove the next bit in 011000
// so the total number of moves we will use is exactly (1<<bit). But
// to remove the current bit, we just need at least 1 move.
// Repeat this idea until we run out of moves.
// Then finally just return the ans.

void solve() {
	ll n, k, m;
    cin >> n >> m;

    ll ans = n, temp = m, sum = 0;

    // n+m
    for (int bit=0; bit<=30; bit++){
        int currentBit = (n >> bit) & 1;
        if (currentBit == 1) sum += (1 << bit);
        else{
            ll diff = (1<<bit) - sum;
            if (temp >= diff){
                ans |= (1 << bit);
                temp -= (1 << bit);
                sum += (1 << bit);
                // cout << temp << endl;
            }
            else break;
        }
    }

    ll x = n;
    temp = m, sum = 0;
    // n-m
    for (int bit=0; bit<=29; bit++){
        int currentBit = (x >> bit) & 1;
        if (currentBit == 1){
            if (temp >= 1){
                ans |= sum;
                temp -= (1 << bit);
            }
            else break;
        }
        sum += (1 << bit);
    }

    cout << ans << '\n';


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
