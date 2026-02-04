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
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits

// solve time ~ can't solve (>.<)
// I need to do more game theory on trees...
// Idea:
// For Alice to get any points.
// The path from root -> leaf must be != 0.
// Lets say we have 0100101000111101
// We can always simplify it to 0101010101 because the digits in 
// between don't contribute to anything.
// Now, in this scenario, Alice will win because 01 occurs 1 more 
// than 10.
// Similary, our path can also look like 1010...10.
// In this scenario, Alice will also win because 10 occurs 1 more 
// than 01.
// So, for 1010...10 and 0101...01 paths, Alice will win.
// But when will Alice lose? When 10 and 01 occurs same amount of time.
// So what will the path be? It has to be in the form:
// 1010...01 or 0101...10
// because this way 10 and 01 occurs the same number of times.
// So, for Bob to win, the path must either be 1010...01 || 0101..10 
// Crucial Observation:
// if the root node is 1 then Alice wants to make the leaf 0 and vice
// versa.
// On the contrary, if the root node is 1, then Bob wants to make 
// leaf 1 and vice versa.
// The nodes in between don't matter, because they will always be
// in the form: x0101...01y || x1010...10y || x0y || x1y
// where x is the root, y is the leaf.
// In other words, we only need to look at the leaf and root.

// Case 1: if the root and leaf is already determined.
// subCase 1: 1???...?1 || 0???...?0
// If root == leaf, then there is nothing we can do to make Alice win.
// because the nodes in between don't matter.
// Proof: 
// ???...? is odd: 
// length 1: then no matter what Alice puts, the score is 
// still 0 because 101 || 111 ||| 000 ||| 010 still results in 0.
// length 3: same thing, the score is still 0 because Bob just needs
// to mirror what Alice plays to cancel her move.
// Eg. 1???1 => 10101 || 10111 || 11000 ...
// No matter what, Bob just needs to follow Alice's opposite move to 
// cancel her score.
// ???...? is even:
// length 2: no matter what Alice puts, the score is still 0.
// 1??1 => 1011 || 1101.
// Same thing, Bob can just cancel out Alice's move each time.

// If the root and leaf is already determined, and they are the same
// Alice just loses.
// What if different? Then Alice wins.
// Proof:
// Since Alice goes first, she can put either 0 or 1.
// For whatever move she decides to choose, Bob will want to cancel it.
// If there are odd ???, then Alice has the final move.
// since the path is 0???1, Alice will make whatever move, and Bob
// will cancel it. But Alice has the final move, and the path
// will always be in the form 0101...?0 or 1010...?0 so 
// Alice can just put the same character instead of the opposite one
// and she will always win.
// If ??? is even, then Alice and Bob will always cancel each other
// out, but the final 0 and 1 or 1 and 0 will always make Alice win.

// so, if root != leaf, Alice wins no matter what nodes are in between.
// and if root == leaf, Bob wins, no matter what nodes are in between.

// Conclusion:
// case 1: if both terminal nodes are determined:
// equal => automatic Alice W else Bob W.

// case 2: if the root is determined:
// leaves that are opposite bit => Alice W
// leaves that are ? => only half or half + 1 if odd for Alice
// because Bob will know the strat and minimize Alice's Ws (they will
// only focus on leaves because any nodes in between don't matter)

// case 3: if the root is not determined:
// Alice can't just choose a bit for the root (because she will be 
// at a disadvantage as now Bob will go first from the 2nd scenario cuz
// now Bob could get half + 1 nodes away from Alice if leaves that are
// ? is odd)
// Instead, she has to first check if x == y, if No. leaf nodes that are
// 1 == No. leaf nodes that are 0.

// If yes, then it depends on w, the number of unimportant nodes that 
// are ?, if its parity is odd, then we can return to the state of scenario
// 2, because after the final move of colouring all w unimportant nodes,
// Bob has to colour the root node. Then its just case 2 again.

// If no, then obviously Alice want to monopolize on picking the leaf
// nodes of a higher count.
// Eg. if there are more 1-valued leaf nodes than 0-valued leaf nodes,
// then Alice will pick 0 as the root node so she can monopolize on the 
// most score.
// But doing so means she sacrifices her first turn, and now Bob will go
// next, meaning now Bob has an advantage after the first turn.
// So Bob will not allow Alice to pick half+1 ? leaf nodes anymore. 
// It will always just be half, hence we take the floor of z/2.

// I love game theory. Fucking hell.

void solve() {
	int n, k, m;
    cin >> n;

    vvi adjList(n+1);
    for (int i=0; i<n-1; i++){
        int node1, node2;
        cin >> node1 >> node2;
        adjList[node1].pb(node2);
        adjList[node2].pb(node1);
    }
    
    str s;
    cin >> s;

    int x = 0, y = 0, w = 0, z = 0;
    for (int node=2; node<=n; node++){
        if (sz(adjList[node]) == 1){
            if (s[node-1] == '1') y++;
            else if (s[node-1] == '0') x++;
            else z++;
        }
        else{
            if (s[node-1] == '?') w++;
        }
    }

    if (s[0] == '1'){ // root node is coloured with 1
        // => all x leaf nodes that are '0' => automatic W for Alice
        // => remaining z leaf nodes that are '?' depends on parity.
        // Alice always just wants to fill leaf first
        // since that guarantees W for Alice for any path.
        // Knowing this, Bob will try to reduce her W's as much as possible
        // by taking over her leaf nodes so she can't get W's
        // it will be exactly half.
        // Since Alice goes first, she has an advantange if z is odd
        // because she can fill one more leaf node in the end.
        cout << x + (z+1)/2 << '\n';
    }
    else if (s[0] == '0'){ // root node is coloured with 0
        // => all y leaf nodes that are '1' => automatic W for Alice
        // => remaining z leaf nodes that are '?' depends on parity.
        // Alice always just wants to fill leaf first
        // since that guarantees W for Alice for any path.
        // Knowing this, Bob will try to reduce her W's as much as possible
        // by taking over her leaf nodes so she can't get W's
        // it will be exactly half.
        // Since Alice goes first, she has an advantange if z is odd
        // because she can fill one more leaf node in the end.
        cout << y + (z+1)/2 << '\n';
    }
    else{ // root node not coloured
        cout << max(x,y) + (z + (x == y ? w % 2 : 0)) / 2 << '\n';
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
