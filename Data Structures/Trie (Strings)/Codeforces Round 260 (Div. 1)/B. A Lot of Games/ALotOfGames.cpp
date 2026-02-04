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
const int MAXN = 1e5+5; // fenwick = N, trie  = N * number of bits

// This was a very nice problem, eventhough I had no idea how to do it.
// Introduction to DP + TRIE + Game Theory
// The trick here is to realise that we can solve this problem, or rather,
// simulate this problem via a trie.
// from there, we can do dp where:
// win is the dp to check if any player can WIN at this node
// => we want to play optimally so we can WIN for the dp win array
// lose is the dp to check if any player can LOSE at this node
// => we want to play optimally so we can LOSE for the dp lose array
// win[i] == true || false, lose[i] == true || false at any node i.
// win[i] == true => the current player can guarantee a win
// win[i] == false => the current player cannot guarantee a win
// lose[i] == true => the current player can guarantee a lost
// lose[i] == false => the current player cannot guarantee a lost

// base case: at any leaf node of a trie (end of the round)
// win[i] == false, lose[i] == true
// => current player can guarantee a lose if we reach this leaf node &&
// current player cannot guarantee a win. (makes sense right?)

// then as we go up the trie via dfs backtracking,
// at any node i, we check if win[i] == true

int trie[MAXN][26], nxt;
bool win[MAXN], lose[MAXN];


void addToTrie(str s) {
    int v = 0;
    for (int i = 0; i < sz(s); i++){
        int currentChar = s[i] - 'a';
        if (trie[v][currentChar] == -1){
            trie[v][currentChar] = nxt++;
        }
        v = trie[v][currentChar];
    }
}

// In the dfs,
// at every level, we check that if AT LEAST ONE of my children nodes
// have win[childNode] == false
// => I can always go to that node guarantee me a win (because win[childNode]
// == false means this node is a losing node, so I can win when I go to that
// node because at that child node, its my opponent's turn, meaning my opponent
// guarantees he cannot win => he will lose at this node => I will win, which
// is what I want)
// => win[currentNode] == true, because it is possible for me to win.

// Similarly, we check that if AT LEAST ONE of my children nodes
// have lose[childNode] == false
// => I can always go to that node guarantee me a lose (because lose[childNode]
// == false means this node is a winning node, so I can lose when I go to that
// node because at that child node, its my opponent's turn, meaning my opponent
// guarantees he cannot lose => he will win at this node => I will lose, which
// is what I want)
// => lose[currentNode] = true, because it is possible for me to lose.


void dfs(int v) {
    win[v] = false, lose[v] = false;
    int children = 0;

    for (int i=0; i<26; i++){
        int u = trie[v][i];
        if (u == -1) continue;
        children++;
        dfs(u);
        // at least one child is a losing node, I can go to that node to win
        if (!win[u]) win[v] = true;
        // at least one child is a winning node, I can go to that node to lose
        if (!lose[u]) lose[v] = true;
    }

    // we always lose at the leaf node for whoever's turn it is
    if (children == 0) lose[v] = true; 
}

void solve() {
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < 26; j++) {
            trie[i][j] = -1;
        }
    }
    nxt = 1;

    for (int i = 0; i < n; i++) {
        str s;
        cin >> s;
        addToTrie(s);
    }

    dfs(0);
    // if win[0] == true, player 1 can guarantee a win at this round
    // but there are 2 scenarios to consider:

    // if lose[0] == true:
    // => player 1 can force a lost to himself
    // => player 1 always wins. Why? Since the loser goes first,
    // he can purposely lose every round until the last round 
    // where he will purposely choose the winning move.

    // if lose[0] == false:
    // => player 1 cannot force a lost to himself
    // => all the children nodes are losing nodes for player 2, 
    // i.e lose[childNode] == true for all children.
    // so no matter where player 1 goes, he will always win because at any
    // node that he goes next, player 2 will lose since its his turn next.
    // => no matter what, player 1 always wins this round.
    // win[0] == true, lose[0] == false
    // => if I can only win and I cannot lose on the root node
    // then I can only win on the root node.
    // => whoever goes first wins the round.
    // since the loser goes next, the perspective changes
    // => we just need to check the parity of k.
    // if k is odd, player 1 wins, else player 2 wins.

    // if win[0] == false
    // regardless of lose[0] state
    // player 1 will always lose because the 2nd player will always win
    // Why? Because on the next move, i.e the children of the 1st layer node
    // will have ALL nodes where win[childNode] == true
    // Since its player 1's turn, he will go to any node which will
    // cause player 2 to be on a winning node
    // => player 2 will win => player 1 loses
    // then every round after, player 1 will always go first again, which is 
    // just a cycle of player 1 constanly losing and player 2 constanly winning.

    if (win[0]){
        if (lose[0]) cout << "First" << '\n';
        else cout << (k % 2 == 1 ? "First" : "Second") << '\n';
    }
    else cout << "Second" << '\n';
    
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
