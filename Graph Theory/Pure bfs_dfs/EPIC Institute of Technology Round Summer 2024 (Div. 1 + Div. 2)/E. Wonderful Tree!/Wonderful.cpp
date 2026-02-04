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


// Can't solve...
// This was such a nice problem, I figured it was greedy + dfs/bfs.
// But my solution is way too dumb, I just did one dfs and carried the 
// states upwards, without considering max potential of each node before
// its sum of children will be less than the node itself.
// The proper greedy way to solve this, is to do a bottom up approach, 
// starting from the leaves, and we can in fact use bfs, because of the 
// given input, every p[i] < i, and i>=2 => i will always be a child
// of p[i], meaning larger indexed nodes will always be the child of
// smaller indexed nodes.
// The idea is that, for every node we can calculate its potential of 
// being able to add 1 to its parent without affecting its path at all.
// potential is calculated as : b[i] = sum(a[each child]) - a[i].
// b[i] >= 0 => wondeful
// b[i] < 0 => not wonderful
// Then, notice now that our goal becomes to make all b[i] >= 0.
// So via bottom-up bfs, we can then do this:
// if b[i] < 0, this means that its not wonderful, so we need to keep
// adding some cnt until b[i] >= 0.
// But how? The answer is greedy.
// for each of the children of i. We say:
// if the b[child] > 0, then we can take cnt = min(b[child], -b[i]).
// meaning cnt is the maximum potential that we can add to b[i] without
// changing the states of the entire path of b[child] to a leaf.
// Because if we take cnt > b[child], then the child of the child will
// have a smaller value now, and that means we need to go down another level
// to add the cnt again for that child of the current child, and we need
// to consider the depth as well, so basically we are adding cnt twice 
// which is undesirable...
// Instead, greedily, we go level by level, if I can make b[i] >= 0 in
// 1 level (from my direct children), then that is the best move.
// In fact, optimally, we should go level by level, because for each
// level that we go down, we need to add cnt * (depth[v] - depth[i]), 
// where v is the current node we are on in the bfs.
// For more clarity, here is path with nodes 4, 7, 9. 9 is the leaf node.
// And the values of each node is 12, 6 and 10 respectively.
// 4 [12] -> 7 [6] -> 9 [10].
// bfs from 9, b[9] = INF, so its valid.
// bfs from 7, b[7] = 10 - 6 = 4 >= 0, so its valid.
// bfs from 4, b[4] = 6 - 12 = -6 < 0, so its invalid.
// hence we need to check, what is the maximum potential I can add to
// b[4] before I need to change the entirety of the path of node 7?
// In this case, cnt = min(b[7]=4, -b[4]=6) = 4. 
// meaning, I can add b[4] by 4, and subtract b[7] by 4, to still
// satisfy the fact that b[7] >= 0, which is what we want.
// We also add 4 to out ans, ans+=4.
// However, b[4] = -2 even after adding 4, and since we have no other
// direct children to 4, we must go down one more level.
// Then, we take cnt = min(b[9]=INF, -b[4]=2) = 2.
// so we can now add b[4] by 2, and it become b[4] >= 0.
// However, now that we are 2 level apart, we need to add ans += 2 * 2.
// Or to make it clearer, we always need to add 
// ans += cnt * (depth[v] - depth[i]).
// Why? Because IMPLICITLY, we also need to change the value of a[7] to 
// 12 as a[9] is also 12 now.
// Like, in the 1st iteration of the bfs, we actually IMPLICITLY say
// that now, a[7] = 10, which is the max potential before we need to 
// change both a[7] and a[9] together if b[4] < 0 still, which in this 
// case yes.
// Then on the 2nd iteration of the bfs, since we need to add another 2
// to b[4] to make it >= 0, both a[7] and a[9] IMPLICITLY have to be 
// added by another 2 make both of them satisfy their inequalities too.
// because a[7]=12 <= a[9]=12 is still b[7] >= 0.
// And that is the idea behind the bfs + greedy approach.

// Time complexity: O(N^2)

ll a[10000],b[10000],dep[10000],cl[10000];
vi e[10000];

void solve() {
	int n, k, m;
    cin >> n;

    for(int i=1; i<=n; i++) cin>>a[i];
	for(int i=1; i<=n; i++) clr(e[i]),cl[i]=0,b[i]=0,dep[i]=0;

	for(int i=2; i<=n; i++){
		int x;cin>>x;
		e[x].pb(i);
		cl[x]+=a[i];
		dep[i]=dep[x]+1;
	}
 
	for(int i=1; i<=n; i++){
		if(e[i].empty()) b[i]=MAX;
		else b[i]=cl[i]-a[i];
	}
 
	ll ans=0;
 
	for(int i=n; i>=0; i--){
		queue<int> q;
		q.push(i);
		if(b[i]>=0) continue;
		while(!q.empty() && b[i] < 0){
			int u=q.ft();
			q.pop();
			for(auto v:e[u]){
				if(b[v]>0){
					ll cnt=min(b[v],-b[i]);
					b[v]-=cnt,b[i]+=cnt;
                    //cout << v << " " <<  i << endl;
                    //cout << cnt << " " << dep[v] << " " << dep[i] << '\n';
					ans+=cnt*(dep[v]-dep[i]);
				}
				q.push(v);
			}
		}
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
