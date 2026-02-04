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

// solve time ~ can't solve.
// Introduction to 2 colouring strategy on Bipartite graphs.
// The key here is that we can use this trick to solve the problem.
// Idea:
// We can represent crewmate and impostor as 2 different colours.
// Since we want to maximize impostors while still satisfying the 
// condition of having no contradiction, we can just take the maximum
// of the 2 colours (as there are multiple disjoint components),
// and if we see a contradiction (meaning a node can be both crewmate 
// and impostor), then just cout -1.

// See the code below for a better picture.

// Time complexity: O(N)
// Space complexity: O(N)

void solve() {
	int n, k, m;
    cin >> n >> m;

    vvpii adjList(n+1); // node1, node2, type
    // type 1: different colour
    // type 2: same colour

    for (int i=0; i<m; i++){
        int node1, node2;
        str s;
        cin >> node1 >> node2 >> s;

        if (s == "imposter"){
            // case 1: node1 is impostor => node2 is crewmate
            // case 2: node1 is crewmate => node2 is impostor
            // in both cases, node1 and node2 are opposite roles
            // => node1 and node2 must be different colour
            // which we will define as type 1.
            adjList[node1].pb({node2, 1});
            adjList[node2].pb({node1, 1});
        }
        else{
            // case 1: node1 is impostor => node2 is impostor
            // case 2: node1 is crewmate => node2 is crewmate
            // in both cases, node1 and node2 are the same roles
            // => node1 and node2 must be the same colour
            // which we will define as type 2.
            adjList[node1].pb({node2, 2});
            adjList[node2].pb({node1, 2});
        }
    }

    // -1 = unvisited, 1 = 1st colour, 2 = 2nd colour
    vi visited(n+1, -1);    

    queue<int> q;
    int ans = 0;
    bool contradict = false;

    for (int i=1; i<=n; i++){
        int colour1Count = 0, colour2Count = 0;

        if (visited[i] == -1){
            q.push(i);
            visited[i] = 1; // by default just set to 1st colour

            while (!q.empty()){
                int curNode = q.ft();
                q.pop();
                
                if (visited[curNode] == 1) colour1Count++;
                else colour2Count++;
                
                for (auto p : adjList[curNode]){
                    int nextNode = p.F, colourType = p.S;
                    
                    // type 1: diff colour
                    // type 2: same colour

                    // check for contradiction
                    if (visited[nextNode] != -1){ // nextNode is visited
                        if (colourType == 1 && visited[curNode] == visited[nextNode]){
                            contradict = true;
                        }
                        if (colourType == 2 && visited[curNode] != visited[nextNode]){
                            contradict = true;
                        }
                        continue; // since visited, we just check for contradiciton
                    }

                    // 3-1=2, 3-2=1, so its diff colour
                    if (colourType == 1) visited[nextNode] = 3 - visited[curNode];
                    else visited[nextNode] = visited[curNode]; // same colour
                    
                    q.push(nextNode);
                }
            }
            
            // choose the colour which appears more to maximize No. of impostors
            ans += max(colour1Count, colour2Count);
        }
    }

    if (contradict) cout << -1 << '\n';
    else cout << ans << '\n';

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
