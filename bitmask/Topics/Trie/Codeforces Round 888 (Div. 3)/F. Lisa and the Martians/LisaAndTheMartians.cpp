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
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits

int nxt;

void addToTrie(int number, int id, int k, int (&trie)[][2], int (&idx)[]){
    int v = 0;
    for (int bit=k; bit>=0; bit--){
        int currentBit = (number >> bit) & 1;
        if (trie[v][currentBit] == -1){
            trie[v][currentBit] = nxt++;
        }
        v = trie[v][currentBit];
    }
    idx[v] = id;
}

pii bfs(int number, int k, int (&trie)[][2], int (&idx)[]){
    int v = 0, x = 0;
    for (int bit=k; bit>=0; bit--){
        int currentBit = (number >> bit) & 1;
        if (trie[v][currentBit] != -1){
            x |= ((1^currentBit) << bit);    
            v = trie[v][currentBit];    
        }
        else v = trie[v][1-currentBit];
    }
    
    return {idx[v], x};
}

void solve() {
	int n, k, m;
    cin >> n >> k;

    int trie[k*n+1][2], idx[k*n+1];
    for (int i=0; i<=k*n+1; i++) trie[i][0] = -1, trie[i][1] = -1, idx[i] = -1;
    nxt = 1;

    vi a(n+1);
    for (int i=1; i<=n; i++) cin >> a[i];

    addToTrie(a[1], 1, k-1, trie, idx);
    int ansi = 1, ansj = 1, ansx = 1, best = -1;
    for (int i=2; i<=n; i++){
        pii p = bfs(a[i], k-1, trie, idx);
        int j = p.F, x = p.S;

        // cout << j << " " << i <<  " " << x << endl;
        // cout << best << " " << ((a[i]^x) & (a[j]^x)) << endl;
        if (best < ((a[i]^x) & (a[j]^x))){ // the outer bracket fucked me...
            best = (a[i]^x) & (a[j]^x);
            // cout << "update" << endl;
            ansx = x;
            ansi = i;
            ansj = j;
        }
        addToTrie(a[i], i, k-1, trie, idx);
    }
    // cout << best << endl;
    cout << ansj << " " << ansi << " " << ansx << '\n';

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

// // Note: I tried solving this problem via divide and conquer, it failed, not sure why.
// // In any case, this is a very good problem, solving it via trie is just so genius here
// // because of how we build the trie
// // It is obvious that we need to think in terms of bits for this problem.
// // Now, the problem mentioned that x can be anything, so long as it is martian.
// // so we just need to worry about a[i] and a[j] then build x from there.
// // Think about this in terms of brute force, how would you find a pair of (a[i], a[j])
// // such that it is (a[i] ^ x) & (a[j] ^ x) is maximised?
// // Well its quite straightforward, double for loop then do (a[i] ^ x) & (a[j] ^ x)
// // for every pair.
// // Unfortunately this would not work.
// // BUT, here is where the genius comes in, we can use a trie.
// // However, we don't just add all the elements given straight to the trie
// // in fact, we build it one by one through the loop, and search for each a[i],
// // what is the current a[j] that gives the maximum (a[i] ^ x) & (a[j] ^ x).

// // The way we build the trie is just the default way of building one
// // One small tweak would just be to add an index to indicate the index
// // of the current number added to the trie at the bottom of the trie
// // since in a trie, the bottommost layer is basically all the numbers up to k bits
// // so for each node at the bottom we can assign an index to indicate the index of that
// // number
// // we need this to find the index of the best pair currently since thats what the 
// // question wants, we need i,j and x.

// struct TrieNode {
//     int nxt[2]; // Children for bit 0 and bit 1
//     int idx;     // Stores the ID of the number

//     TrieNode() {
//         nxt[0] = nxt[1] = -1;
//         idx = -1;
//     }
// };

// vector<TrieNode> trie; // Trie as a vector of nodes
// vector<int> arr;       // Array of martian numbers
// int n, k;

// // Function to add a number to the trie
// void addToTrie(int nodeIndex, int number, int bitPos, int idx){
//     if (bitPos < 0) {
//         trie[nodeIndex].idx = idx; // assign its index at the bottommos layer
//         return;
//     }

//     int currentBit = (number >> bitPos) & 1;
//     if (trie[nodeIndex].nxt[currentBit] == -1){
//         trie[nodeIndex].nxt[currentBit] = sz(trie);
//         trie.pb(TrieNode());
//     }

//     addToTrie(trie[nodeIndex].nxt[currentBit], number, bitPos - 1, idx);
// }

// // Function to traverse the trie and find the best pair
// int findBestPair(int nodeIndex, int number, int bitPos, int& x, int& jans){
//     if (bitPos < 0){
//         jans = trie[nodeIndex].idx; // we found our number, return its index.
//         return 0;
//     }

//     int currentBit = (number >> bitPos) & 1;

//     // if the current bit is 0 for a[i], then a[j] must be 0 at this currentbit as well
//     // so that (a[i] ^ x) & (a[j] ^ x) = 1
//     // Similarly, if the current bit is 1 for a[i], then a[j] must be 1 at this currentbit as well
//     // so that (a[i] ^ x) & (a[j] ^ x) = 1
//     // hence we want to take the path of currentBit first
//     // and if it exists, we take x to be the opposite bit since its a[i] ^ x, a[j] ^ x
//     // also we add (1 << bitPos) because this can contribute to our current sum
//     // we continue with this path
    
//     // if the currentBit path does not exist,
//     // then the current bit of x can be set as anything 
//     // (0 ^ currentBit) << bitPos is not really needed, I just added it for symmetry
//     // x can be 1 or 0, doesn't matter since a[i] and all a[j] have different bit
//     // at this current bit position
//     // we have to change paths, flip currentBit

//     if (trie[nodeIndex].nxt[currentBit] != -1) {
//         x |= (1 ^ currentBit) << bitPos;
//         return findBestPair(trie[nodeIndex].nxt[currentBit], number, bitPos - 1, x, jans) + (1 << bitPos);
//     } else {
//         x |= (0 ^ currentBit) << bitPos;
//         return findBestPair(trie[nodeIndex].nxt[currentBit ^ 1], number, bitPos - 1, x, jans);
//     }
// }

// // Solve function to find the best i, j, and x
// tuple<int, int, int> solve() {
//     // since i != j
//     int ians = 0, jans = 1, xans = 0;


//     // this is where the true genius begins.
//     // the code here is basically going through all the pairs implicitly.
//     // which is the generic double for loop to go through all pairs.
//     // but since that is too slow, we use a trie
//     // which for every new number we encounter, we search, for this current number,
//     // what is the best number in the trie currently that gives the max (a[i] ^ x) & (a[j] ^ x)

//     for (int i = 1; i < n; ++i){
//         int x = 0, j = -1;
//         int cur = findBestPair(0, arr[i], k - 1, x, j);
        
//         // if this current pair with its x is better than our best so far
//         if (cur > ((arr[ians] ^ xans) & (arr[jans] ^ xans))){
//             ians = j;
//             jans = i;
//             xans = x;
//         }

//         addToTrie(0, arr[i], k - 1, i);
//     }

//     return {ians, jans, xans};
// }

// // Time complexity: O(N * K)
// // Space complexity: O(N * K)

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int t;
//     cin >> t;
//     while (t--) {
//         cin >> n >> k;

//         arr.resize(n);
//         for (int i = 0; i < n; ++i){
//             cin >> arr[i];
//         }

//         clr(trie);
//         trie.pb(TrieNode()); // Start with a root node
//         addToTrie(0, arr[0], k - 1, 0); // Add the first number to the trie

//         auto [ians, jans, xans] = solve();
//         cout << ians + 1 << ' ' << jans + 1 << ' ' << xans << '\n';
//     }

//     return 0;
// }

// // void solve() {
// // 	int n, k, m;
// //     cin >> n >> k;
    
// //     vi a(n), c1, c0;
// //     for (auto &x : a) cin >> x;
    
// //     vpvii b; // {array, x}
// //     vpvii temp;
// //     map<int, int> memo;

// //     for (int i=0; i<n; i++){
// //         memo[a[i]] = i+1;
// //         if (a[i] & (1 << (k-1))) c1.pb(a[i]);
// //         else c0.pb(a[i]);
// //     }

// //     if (sz(c1) >= 2) b.pb(mp(c1, 0));
// //     if (sz(c0) >= 2) b.pb(mp(c0, 1 << (k-1)));

// //     for (int bit=k-2; bit>=0; bit--){
// //         clr(c1), clr(c0), clr(temp);
// //         for (int i=0; i<sz(b); i++){
// //             for (int j=0; j<sz(b[i].F); j++){
// //                 if (b[i].F[j] & (1 << bit)) c1.pb(b[i].F[j]);
// //                 else c0.pb(b[i].F[j]);
// //             }

// //             if (sz(c1) >= 2){
// //                 temp.pb(mp(c1, b[i].S));
// //             }

// //             if (sz(c0) >= 2){
// //                 temp.pb(mp(c0, b[i].S + (1 << bit)));
// //             }

// //         }

// //         b = temp;
// //     }

// //     cout << memo[b[0].F[0]] << " " << memo[b[0].F[1]] << " " << b[0].S << '\n';

// // } 

// // int main() {
// //     fast_io();
// //     int t;
// //     cin >> t;
// //     while (t--) solve();
// //     return 0;
// // }