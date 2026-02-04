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
const int MAXN = 1e6+5; // fenwick = N, trie  = N * number of bits

// This was a nice problem
// The trick to this problem is thinking in terms of brute force first.
// N^2 solution: get prefix XOR's for the whole array
// then in N^2 time, 
// for every pair we do pref[r] ^ pref[l-1].
// if pref[r] ^ pref[l-1] >= k, ans++;
// However, this is too slow.
// Can we speed things up? Yes, by using a trie!
// Using a trie allows us to solve this problem in Nlog(max(a)) time.
// The idea is the same, we still use prefix XOR's of the array
// add them to the trie.
// However, one thing to note is that we must do this on the fly, (similar to
// Lisa and the Martians)
// Why? Because if we add all the prefix XOR's all at once and compare it
// for each pref[l-1] we would overcount valid pairs.
// so we should do this on the fly.
// This way, we are basically saying: up to some r so far, using pref[r]
// and all pref[l-1] that are in the trie, how many pref[r] ^ pref[l-1] >= k?
// And we can take the valid pairs and add them properly that way.
// Also, an edge case is that we need to add pref[l-1] == 0 first, because
// otherwise we can't consider the case where pref[r] ^ (pref[l-1]==0).
// basically we won't be able to consider the largest subarray from 0 to r
// if we don't add 0 to the trie.

int trie[MAXN * 30][2], cnt[MAXN * 30], nxt = 1;

void addToTrie(int number){
    int v = 0;
    cnt[v]++;
    for (int bit=30; bit>=0; bit--) {
        int currentBit = (number >> bit) & 1;
        if (trie[v][currentBit] == -1){
            trie[v][currentBit] = nxt++;
        }
        v = trie[v][currentBit];
        cnt[v]++;
    }
}

int bfs(int number, int k){
    int v = 0;
    int result = 0;
    for (int bit=30; bit>=0 && v!=-1; bit--){
        int currentBit = (number >> bit) & 1;
        int kBit = (k >> bit) & 1;
        // let kBit be the bit of k at position bit
        // let currentBit be the bit of pref[r] at the position bit

        // if kBit == 0, currentBit == 0
        // then we need to choose the path where the bit is 1 so that 
        // pref[r] ^ pref[l-1] >= k, because since we start from the MSB
        // from the trie, (currentBit == 0) ^ (path == 1) == 1 > kBit==0
        // so we need to add cnt[trie[v][1^currentBit]] to result

        // if kBit == 0, currentBit == 1 
        // then we want the path where the bit is 0 because 1 ^ 0 > k 
        // so we add cnt[trie[v][1^currentBit]] to result

        // if kBit == 1, currentBit == 0
        // then we cannot choose the path with bit set as 0
        // because all the numbers down that path will just be < k because
        // currentBit == 0 ^ 0 < kBit == 1, so there is no point in considering
        // that path. So we go to the path of trie[v][1^currentBit]
        // for a chance for the number to be >= k
        // the path of 0 will always be < k, so dont add the count of that
        // path to result.

        // if kBit == 1, currentBit == 1
        // then we need to choose the path where the bit is set as 0 because
        // currentBit==1 ^ 0 >= kBit==1 for a chance for numbers in that path
        // to be at least k
        // the path of 0 will always be < k, so dont add the count of that
        // path to result.
        

        if (kBit == 0){
            result += cnt[trie[v][1^currentBit]];
            v = trie[v][currentBit];
        } else {
            v = trie[v][1^currentBit];
        }
    }
    // this line is crucial
    // we need this last line because we need to add the last node's count 
    // as well if it is valid as the for loop cannot catch it.
    // this is for all prefixXOR == k
    if (v != -1) result += cnt[v];
    return result;
}

void solve() {
    int n, k;
    cin >> n >> k;

    memset(trie, -1, sizeof(trie));
    memset(cnt, 0, sizeof(cnt));
    nxt = 1;

    // we find all the pairs for pref[r] ^ pref[l-1]
    // we need to addToTrie(0) for the case pref[r] ^ (pref[l-1]==0)
    // => taking the whole subarray so far.
    addToTrie(0); 

    ll result = 0;
    int prefixXOR = 0;
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        prefixXOR ^= x;
        result += bfs(prefixXOR, k);
        addToTrie(prefixXOR);
    }
    
    cout << result << '\n';
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