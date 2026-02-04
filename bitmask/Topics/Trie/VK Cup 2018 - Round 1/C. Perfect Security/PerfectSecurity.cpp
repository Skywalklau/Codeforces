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
const int MAXN = 3e5+5; // fenwick = N, trie  = N * number of bits

// I'm too fucking good with trie, I solved this problem in like 20 mins bruf
// 1800 aint got no shit on me
// First things first, we can change the eqn to O[i] = A[i] ^ P[i] for some P[i]
// but for a fixed A[i] (as per what the question wants)
// Since we want lexicographically smallest permutation.
// O[i] must be minimized.
// so now the question becomes find the minimum O[i] for each A[i] from all
// the available P[i] elements that you can choose from.
// To solve this problem, my approach was: What is the brute force solution?
// Well, its N^2, because for each A[i], we go through all P[i] and take the min
// from the XOR of all P[i] elements.
// And we do this for each A[i], which is N^2.
// Doing this also maintain lexicographical order because we are starting from 
// the first element of A, so we can pick the best P at this position 
// such that our O[i] is minimized everytime.
// Of course, doing this in N^2, is too slow, can we do better? 
// Yes, the answer is Trie.
// we store all the numbers of P in a Trie for efficient searching.
// For every A[i] we go through, we traverse the trie.
// at every bit position, if A[i]'s current bit is 0, we want to go to the path
// of the trie that has the bit 0 as well, because O[i] needs to be minimized,
// at this bit position: O[i] = 0 = A[i] ^ P[i] = 0 ^ 0 = 0
// so we want P[i] to be 0 as well for this bit.
// Similarly, if the current bit of A[i] is 1, we want the path with 1 as well.
// because 1 ^ 1 = 0 => O[i] can be 0 at this bit position => O[i] is minimized.
// However, if no same path exists for A[i] at some bit position, then we have
// no choise but to increment O[i] by this bit position, and swap to the other
// path as well since this path that we want does not exist.
// And we do this until the bottom most level, and return the result.
// One thing to note, each time we traverse through a node, we must decrement its
// count since this path had been traversed by the current iteration, which can tell
// us when all available paths from this level has been traversed.
// So, even if the same bit position exists for some A[i] in the trie, if the count
// is 0 through this path, that means we have taken all the available numbers from 
// this path already => we need to add this bit to O[i] and swap paths.

int trie[MAXN * 30][2], cnt[MAXN * 30], nxt;

void addToTrie(int number){
    int v = 0;
    cnt[v]++;
    for (int bit=30; bit>=0; bit--){
        int currentBit = (number >> bit) & 1;
        if (trie[v][currentBit] == -1) trie[v][currentBit] = nxt++;
        v = trie[v][currentBit];
        cnt[v]++;
    }
}

int bfs(int number){
    int v = 0, result = 0;
    cnt[v]--;
    for (int bit=30; bit>=0; bit--){
        int currentBit = (number >> bit) & 1;
        if (cnt[trie[v][currentBit]] > 0){
            v = trie[v][currentBit];
        }
        else{
            result |= (1 << bit);
            v = trie[v][1-currentBit];
        }
        cnt[v]--;
    }
    return result;
}

void solve() {
	int n, k, m;
    cin >> n;

    vi a(n);
    for (int& x: a) cin >> x;

    memset(cnt, 0, sizeof(cnt));
    for (int i=0; i<MAXN*30; i++){
        trie[i][0] = -1;
        trie[i][1] = -1;
    }
    nxt = 1;

    for (int i=0; i<n; i++){
        int p;
        cin >> p;
        addToTrie(p);
    }

    vi result(n);
    for (int i=0; i<n; i++){
        result[i] = bfs(a[i]);
    }

    printVector(result);

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
