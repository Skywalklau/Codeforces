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


// This was a good problem, I learned rerooting technique.
// Actually, I managed to solve this problem for a single root.
// However, since the question wanted all the roots, and not just one root, I became
// stuck and I didn't know how to progress from there.
// The idea here is to use rerooting. But before that, let me explain how to solve 
// the problem for a single root.
// The answer is bfs/dfs + dp.
// Key observation: What should we make all the values on the tree equal to?
// Answer: the root of the tree.
// Why? Lets think its terms of base cases.
// if I have a tree of 3 nodes, say:
//       1
//      2 3
// what should the XOR of the values be in the end? For min cost. 
// if we say anything other than 1, the total cost will always be higher if we
// dont make everything equal to 1 (the parent node)
// Notice that, for 1, we only need to change the value of node 2 and 3 (the children).
// our cost will be (val[1]^val[2])*1 + (val[1]^val[3])*1
// if we want all the nodes to be anything else other than 1, we would always have an 
// extra cost: lets say we want 3.
// then: totalCost = (3^val[1])*3 + (3^val[2]^(3^val[1]))*1 + (3^val[3]^(3^val[1]))*1
// which will always be greater than if we set to the value of the root.
// Hence, we always set to the value of the root.
// Expanding from this, we can do a dfs, and repeat the same idea from there.
// first, we need to count the total number of nodes in each subtree.
// then, for every node, we want to make it equal to its parent.
// the cost for each node to make it equal to its parent will be:
// cost = (val[parent] ^ val[child]) * cnt[child] + costSoFar[child]
// where val[i] is the value of a node i, cnt[i] is the number of children of node i
// and costSoFar[i] is the cost so far to make every node (including i itself) into
// a subtree where all values are equal.
// And we keep repeating this logic, until we reach the root node, then we will
// have the answer for this particular tree with whatever root node we set.

// Note: We can also do this with bfs, but we would have to keep track of a cumulative
// XOR value as we go down the tree to calculate the total cost.

// However, this is not enough, as the question wants ALL the answers when each
// node is a root.
// Brute force is too slow, since there are too many nodes.
// Hence we need to use this technique call rerooting.
// Motivation: We use what we have already computed for a tree with some root node
// that we defined already, and use it to get the answer without actually computing
// all the values again.
// Essentially, we are "transferring" values over to another node when it becomes
// the root node.
// Given:       1
//             2 3
//            4   5
// right now the root is 1, lets say we already found all the values for this tree.
// which means we have the cnt, cost for each node calculated via dfs/bfs already.
// Lets say we want to make 2 as the root node now, how do we do it?
// Notice that, at node 2, we already computed via the dfs initialy, the cnt and 
// the cost up to that node already.
// cnt[2] = 2(because there are 2 nodes including 2 itself under 2), and 
// lets say costSoFar[2] = 3, which means the total cost so far to make all the children
// equal to val[2] is 3.
// Then, we also know that, at node 1, we also calculated the same thing already
// via the first dfs/bfs.
// cnt[1] = 5(including 1 itself), and lets say costSoFar[1]=10.
// Great! So now, if we want to make 2 as the root node when we have these values
// how do we do it? 
// Notice that, node 2 already has everything computed correctly below it (the branch
// from 2 to 4).
// We just need to change the branch: 1 -> 3 -> 5 to values for when node 2 is the root.
// Hence, we can do this:
// val[1] -= ((val[2] ^ val[1]) * cnt[2] + costSoFar[2])
// => 1 no longer has the value from the branch 2 in its value when 2 is the root 
// cnt[1] -= cnt[2] 
// => 1 no longer has the branch from 2 in its count when 2 is the root
// Doing this, we excluded the part where 1 is the root node including the costs
// and counts of the branch with node 2.
// We then do this:
// val[2] += ((val[2] ^ val[1]) * cnt[1] + costSoFar[1]);
// => we add back the branch of 1 which now excludes the branch of 2 into
// the total cost of node 2.
// cnt[2] += cnt[1]; 
// => we add back the number of nodes in branch 1 which node excludes the number of
// nodes in branch 2.
// And thats it! Now we just need to restore the states because its backtracking.
// To better visualize it: We basically split the graph into 2 components and
// calculate the correct values and counts before recombining them again
//   A: 2  B: 1
//   4         3
//              5
// we calulate the values and counts for each component, and then combine them back
// to node 2.
// BOOYAH! This is rerooting in a nutshell.

void solve() {
    int n;
    cin >> n;

    vll a(n);
    for (auto &e : a) cin >> e;

    vvi adjList(n);
    for (int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adjList[u].pb(v);
        adjList[v].pb(u);
    }

    vll cnt(n, 0);

    // First DFS to calculate subtree sizes
    function<void(int, int)> dfs = [&](int curNode, int parent){
        for (auto nextNode : adjList[curNode]){
            if (nextNode != parent){
                dfs(nextNode, curNode);
                cnt[curNode] += cnt[nextNode];
            }
        }
        cnt[curNode]++;
    };

    dfs(0, -1);

    vll val(n, 0);

    // Second DFS to calculate initial values
    function<void(int, int)> dfs1 = [&](int curNode, int parent){
        for (auto nextNode : adjList[curNode]) {
            if (nextNode != parent) {
                dfs1(nextNode, curNode);
                val[curNode] += (a[curNode] ^ a[nextNode]) * cnt[nextNode] + val[nextNode];
            }
        }
    };

    dfs1(0, -1);

    vll ans(n, 0);

    // Third DFS for rerooting
    function<void(int, int)> dfs2 = [&](int curNode, int parent){
        ans[curNode] = val[curNode];
        for (auto nextNode : adjList[curNode]) {
            if (nextNode == parent) continue;

            ll oldCurVal = val[curNode];
            ll oldCurCnt = cnt[curNode];
            ll oldNextVal = val[nextNode];
            ll oldNextCnt = cnt[nextNode];

            // Remove nextNode's contribution from curNode
            val[curNode] -= (a[curNode] ^ a[nextNode]) * cnt[nextNode];
            val[curNode] -= val[nextNode];
            cnt[curNode] -= cnt[nextNode];

            // Add curNode's contribution to nextNode
            cnt[nextNode] += cnt[curNode];
            val[nextNode] += (a[curNode] ^ a[nextNode]) * cnt[curNode];
            val[nextNode] += val[curNode];

            // Recurse with nextNode as the root
            dfs2(nextNode, curNode);

            // Undo the changes (restore the original state)
            val[curNode] = oldCurVal;
            cnt[curNode] = oldCurCnt;
            val[nextNode] = oldNextVal;
            cnt[nextNode] = oldNextCnt;
        }
    };


    dfs2(0, -1);

    for (auto e : ans) cout << e << " ";
    cout << "\n";
}


int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
