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

// solve time ~ 56 mins
// This was a nice problem.
// As usual, for game problems, we want to see what is the best move
// for Alice first, since she makes the first move. 
// First notice that we can sort the array, since order does not
// matter.
// Also, remove duplicates as well, since all instance of the 
// duplicate will be removed anyways.
// After doing this, notice that the goal now is to remove the last
// instance of the pile of stones since its the biggest.
// Now lets play around with some data.
// lets say we have an array:
// [2,3,4,5,6]
// Can Alice win? Yes.
// A : [2,3,4,5,6]
// B : [0,1,2,3,4]
// A : [0,0,1,2,3]
// B : [0,0,0,1,2]
// A : [0,0,0,0,1]
// B : [0,0,0,0,0]
// So Bob loses.
// Notice something broken? Alice can always force Bob to 
// pick 1 stone from a pile, since she has the first move.
// Lets consider another scenario:
// [2,3,4,5]
// Can Alice win? Yes!
// A : [2,3,4,5]
// B : [1,2,3,4]
// A : [0,1,2,3]
// B : [0,0,1,2]
// A : [0,0,0,1]
// B : [0,0,0,0]
// So Alice wins again.
// Notice something? Alice just chose to take k-1 stones instead of k
// This way the game results in a parity contest.
// And since Alice has the first move she can always control it 
// to win in her favor.
// But, notice that k>=2 for this to happen.
// In other words, Alice can always win if k>=2 for all elements in a.
// Why? Because Alice can always pick the stones to allow her
// to win from the first move onwards, even if the stones are sparse
// Eg. [14, 17, 142], in this case
// Alice can always just pick k-1, then force Bob to pick 1 stone.
// So that she always end up on the next index with her going first
// which always gives her the advantage.
// But, what if k == 1?
// Then the game becomes a parity game.
// Whoever breaks out of the consecutive elements first will be
// the winner.
// Eg. [1,2,3,4,9,10,32,532]
// Because 1 exists, Alice is forced to pick 1.
// then Bob is forced to pick 1, then Alice again and so on..
// until we reach 4, because that is the last consecutive element from
// 1.
// Whoever ends up on 9, will be the winner of the game, because
// that person will have control over the game afterwards.
// In this case, Alice still wins, because its 
//   1   -> 2   ->  3    ->  4  -> 9
// Alice -> Bob -> Alice -> Bob -> Alice
// So, Alice ends up at the non-consecutive element first, hence
// she has control over the game and so she will win.
// If we end up being Bob first, then Bob wins.

void solve() {
	int n, k, m;
    cin >> n;

    vll a(n);
    for (ll& x: a) cin >> x;

    sort(all(a));
    a.rs(unique(all(a)) - a.begin());
    // printVector(a);
    if (a[0] != 1) cout << "Alice" << '\n';
    else{
        bool AliceWin = 1;
        for (int i=0; i<sz(a)-1; i++){
            if (a[i]+1 == a[i+1]){
                AliceWin = (AliceWin + 1) % 2;
            } 
            else{
                // cout << i << endl;
                // cout << "dsa" << endl;
                AliceWin = (AliceWin + 1) % 2;
                break;
            }
        }
        if (AliceWin) cout << "Alice" << '\n';
        else cout << "Bob" << '\n';
    }
    
    

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
