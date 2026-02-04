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
#define rsv reserve
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

const int N = 1e6 + 5; // change according to your needs
vi mn(N, 0); // Smallest prime factor of each number
vvi fcv(N); // Prime factorization for each number (only returns each distinct factor once)


void precompute_prime_factors() { // Modified Sieve
    mn[1] = 1; // Base case: 1 has no prime factors
    for (int i = 2; i < N; i++) {
        if (!mn[i]) { // If i has no prime factor recorded yet, it is a prime number.
            for (int j = 1; j * i < N; ++j) {
                if (!mn[i * j])
                    mn[i * j] = i; // Mark i as the smallest prime factor for all multiples of i.
            }
        }
    }

    // Generate prime factor lists for every number up to N
    for (int i = 1; i < N; i++) {
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

// Constants
const int K = int(1e6) + 99;

// Globals
int nxt;                   // Next available node index
int to[K][26];             // Trie structure for transitions
int sum[K];                // Node frequencies
ll res;                    // Result accumulator


// Function to add a string to the trie
void addToTrie(const str& s) {
    int v = 0; // Start at the root
    sum[v]++;  // Increment root frequency, because every word pass through the root
    for (char c : s){
        int i = c - 'a'; // Convert character to index
        if (to[v][i] == -1){
            to[v][i] = nxt++; // Create a new node if it doesn't exist
        }
        v = to[v][i];
        sum[v]++; // Increment frequency of the current node
    }
}

// Function to update the result based on the trie
void bfs(const str& s) {
    int curLen = sz(s);
    int v = 0; // Start at the root

    // use first test case, with x, and ax as examples to simulate.
    for (char c : s){
        int i = c - 'a'; // Convert character to index
        if (to[v][i] == -1){
            res += sum[v] * 1LL * curLen; // Add remaining contributions
            break;
        } else {
            int nxtV = to[v][i];
            // the ones that are not the same we multiply with the curLen
            // then we continue on with the ones that are the same
            res += (sum[v] - sum[nxtV]) * 1LL * curLen; // Contribution of current level
            curLen--; // Decrease remaining length
            v = nxtV;
        }
    }
}


void solve(int n, vstr& words) {
    // Initialize the trie
    nxt = 1;
    memset(sum, 0, sizeof sum);
    memset(to, -1, sizeof to);

    // Add all words to the trie
    for (const auto& word : words) addToTrie(word);
    
    // Process words in reverse
    // we add the contribution of each string
    for (auto& word : words){
        reverse(all(word)); // if its suffix, reverse to prefix and vice versa
        bfs(word);
    }
}

int main() {
    fast_io();

    int n;
    cin >> n; // Number of strings
    vstr words(n);
    for (int i = 0; i < n; ++i) {
        cin >> words[i];
    }

    res = 0; // Reset result accumulator
    // Case 1: a string k has the same suffix as some prefix of other string(s).
    // we first create the trie (prefix tree)
    // then for each string we reverse it and go down the trie
    // Why? Because if the suffix of a string is the same as some string x
    // I can reverse it to make it so that its prefix is the same as the same string x
    // we add the contribution for each string, since they want every pair 
    solve(n, words); // first solve for prefix trie

    // Reverse back to original and solve again
    // Case 2: a string k has the same prefix as some suffix of other string(s).
    // now we create the reversed trie (suffix tree)
    // because just now we solved for prefixes, now we need to solve for suffixes.
    // so we reverse everything to make it so that we can construct the trie as suffixes
    // then for each word we reverse it again to get it in terms of prefixes.
    // then we compare all pairs again, adding their respective contributions
    for (auto& word : words) {
        reverse(all(word));
    }
    solve(n, words); // then solve for suffix trie

    cout << res << endl;
    return 0;
}