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
const int MAXN = 2e5+5; // fenwick = N, trie  = N * number of bits

int trie[20 * MAXN][2], nxt; 

void addToTrie(int number){
    int v = 0;
    for (int bit=20; bit>=0; bit--){
        int currentBit = (number >> bit) & 1;
        if (trie[v][currentBit] == -1){
            trie[v][currentBit] = nxt++;
        }
        v = trie[v][currentBit];
    }
}

int bfs(int x){
    int v = 0, result = 0;
    for (int bit=20; bit>=0 && v!=-1; bit--){
        int currentBit = (x >> bit) & 1;

        if (trie[v][1^currentBit] != -1){
            result |= (1 << bit);
            v = trie[v][1^currentBit];
        }
        else v = trie[v][currentBit];

    }
    return result;
}


void solve() {
	int n, k, m;
    cin >> n;

    memset(trie, -1, sizeof(trie));
    nxt = 1;
    
    vi a(n);
    // Read array and create [0, c1, c2, c3..., c(n-1)]
    for (int i=1; i<n; i++){
        cin >> a[i];
        a[i] ^= a[i-1];
    }

    for (int p : a) addToTrie(p);
    
    for (int x=0; x<n; x++){
        if (bfs(x) == n-1){
            for (int i=0; i<n; i++) a[i] ^= x;
            printVector(a);
            break;
        }
    }
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

// // Trie node structure
// struct TrieNode {
//     int nxt[2]; // Children for bit 0 and bit 1

//     TrieNode() {
//         nxt[0] = -1;
//         nxt[1] = -1;
//     }
// };

// vector<TrieNode> trie(1); // Trie initialization with root node

// void addToTrie(int nodeIndex, int number, int bitPos) {
//     if (bitPos < 0) {
//         return;
//     }

//     int currentBit = (number >> bitPos) & 1;

//     // If there's no next node for currentBit, create one
//     if (trie[nodeIndex].nxt[currentBit] == -1) {
//         trie[nodeIndex].nxt[currentBit] = sz(trie);
//         trie.pb(TrieNode());
//     }

//     // Recursively add the next bit to the trie
//     addToTrie(trie[nodeIndex].nxt[currentBit], number, bitPos - 1);
// }

// int dfs(int nodeIndex, int x, int bitPos) {
//     if (nodeIndex == -1) return x;

//     int currentBit = (x >> bitPos) & 1;
    
//     // Try to flip the bit to maximize XOR
//     // currentBit == 0 then we want 1 cuz 0^1 = 1
//     // curretBit == 1 then we want 0 cuz 1^0 = 1
//     if (trie[nodeIndex].nxt[currentBit ^ 1] != -1) {
//         currentBit ^= 1;
//     }

//     // XOR x with the currentBit if we can maximize
//     // Otherwise we still XOR x with currentBit to make it 0 for this bit
//     // Why still XOR eventhough we cannot maximize?
//     // let c be an array of numbers.
//     // Since x^c means all bits of x XOR with c
//     // eventhough we cannot maximize x^c at some current bit
//     // we still HAVE to XOR because x^c means XOR all the bits of x and c
//     x ^= currentBit << bitPos;

//     return dfs(trie[nodeIndex].nxt[currentBit], x, bitPos - 1);
// }

// void solve() {
//     int n;
//     cin >> n;

//     // we can always set the array as [0, c1, c2, c3..., c(n-1)], with 0 as first element
//     // where 0^c1 = a1, c1^c2=a2, c2^c3=a3...
//     // if the resultant array [0, c1, c2, c3, ..., c(n-1)] is invalid
//     // we can apply an xor of x to the whole array
//     // then the array becomes [0^x, c1^x, c2^x, c3^x, ..., c(n-1)^x]
//     // if the maximum of this new array is n-1, it means we found the valid array.
//     // => this is a trie problem, where we just want to find the valid x such that
//     // we can get n-1 as the maximum value.
//     // Time Complexity : (N*log(N))

//     vi a(n);
//     // Read array and create [0, c1, c2, c3..., c(n-1)]
//     for (int i = 1; i < n; ++i) {
//         cin >> a[i];
//         a[i] ^= a[i - 1];
//     }

//     for (int x : a) {
//         addToTrie(0, x, MAX_BITS - 1);
//     }

//     for (int x = 0; x < n; ++x) {
//         if (dfs(0, x, MAX_BITS - 1) == n - 1) {
//             for (int i : a) {
//                 cout << (x ^ i) << " ";
//             }
//             cout << "\n";
//             return;
//         }
//     }
// }

// int main() {
//     fast_io();
//     solve();
//     return 0;
// }
