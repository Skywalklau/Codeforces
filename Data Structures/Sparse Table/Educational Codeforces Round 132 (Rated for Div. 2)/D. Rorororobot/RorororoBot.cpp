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

const int LOGN = 19; // sparse table interval
const int MAXN = 2e5+5; // fenwick = N, trie  = N * number of bits

// Nice problem. I solved it. Ez.
// Honestly at first I had no intuition at all on how to do this problem
// until I drew out the grid and simulated the problem on the testcase.
// Key observation: To get to any point we need to consider both the vertical
// and horizontal movements, and in order for point A to reach point B
// abs(xa-xb) % k == 0 && abs(ya-yb) % k == 0.
// Why? Because we can only move in k steps, we cannot stop midway.
// Then I noticed we need to figure out the largestWall between 2 points.
// and if the largestWall > ya, the path we take is basically a U-turn.
// otherwise, we just need to check for this: 
// abs(xa-xb) % k == 0 && abs(ya-yb) % k == 0.
// if largestWall > ya, then we need to calculate whether we can "fit" within
// the gap remaining to align ourselves to xb.
// To get the largestWall, we can use a sparse table.
// So now we can consider this problem now in to 2 cases:
// 1. largestWall < ya.
// In this scenario, we need to check abs(xa-xb) % k == 0 && abs(ya-yb) % k == 0.
// if this condition is satisfied, then we can make it to point B.
// 2. largestWall >= ya.
// In this scenario, we need to check "fit" within the remaining gap to get to xb.
// (xa,ya) x
//         x (xb,yb)
//         x
//         x
//         y
//         y
// x is the wall, y is the gap remaining, we just need to fit within the y to get
// to x after we check that horizontally we can get to B.
// To check if we can fit within the gap, we just take the ceil of (largestWall-ya)/k.
// which is the number of moves we need, then multiply by k and check if its within n.
// there is an edge case, that is, when (largestWall-ya) % k == 0.
// in this case, we need an extra move, because if we dont we will end up at 
// the largestWall position, but we want to go beyond the largestWall, and stay
// within n.
// so, if (largestWall-ya) % k == 0, then No. of moves will be (largestWall-ya)/k +1.
// Ok, if we can fit within the gap, and our horizontal movement is possible as well.
// then that means we just need to check from our currentY coords we are on,
// whether its possible to reach B
// and the way to do that is just if (currentY-yb) % k == 0, then its possible, so YES.
// otherwise, NO.
// The solution I wrote has x and y flipped, cuz I did it according to the question.
// So it might be a bit confusing but keep that in mind.
// Time complexity: O(MLOGM + Q)
// Space complexity: O(LOGM * M)
int sparse[LOGN][MAXN];

void createSparse(int m, vi& a){
    for (int i=0; i<m; i++) sparse[0][i] = a[i];
    for (int i=1; i<LOGN; i++){
        for (int j=0; j+(1<<i) <= m; j++){
            sparse[i][j] = max(sparse[i-1][j], sparse[i-1][j+(1<<(i-1))]);
        }
    }
}

int query(int l, int r){
    int k = 31 - __builtin_clz(r-l+1);
    return max(sparse[k][l], sparse[k][r-(1<<k)+1]);
}

bool check(int xs,int ys,int xe,int ye,int k,int n){
    int largestWall = query(min(ys,ye)-1, max(ys,ye)-1);
    //cout << largestWall << endl;
    //cout << "ss" << endl;
    if (largestWall == n) return false; // wall is blocking horizontal movement
    //cout << "ss" << endl;
    if (abs(ys-ye) % k != 0) return false; // horizontal movement
    // now we know horizontal movement is possible
    // check vertical movement.
    //cout << "ss" << endl;
    // if ((n-xs) < k) return false; // ensures that k fits within rows
    //cout << "ss" << endl;
    // case 1: xs > largestWall
    if (xs > largestWall){
        if (abs(xe-xs) % k != 0) return false; // vertical movement
    }
    else{ // case 2: xs <= largestWall
        if ((n-xs) < k) return false; // ensures that k fits within rows
        int numberOfMoves;
        if ((largestWall-xs) % k == 0) numberOfMoves = (largestWall-xs) / k + 1;
        else numberOfMoves = ((largestWall-xs) + k - 1) / k;

        int curX = xs + numberOfMoves*k;
        //cout << curX << endl;
        if (curX > n) return false;
        if (abs(xe-curX) % k != 0) return false; // vertical movement
    }
    return true;
}

void solve() {
	int n, m, q;
    cin >> n >> m;

    vi a(m);
    for (int& x: a) cin >> x;

    createSparse(m, a);
    cin >> q;

    while (q){
        int xs,ys,xe,ye,k;
        cin >> xs >> ys >> xe >> ye >> k;
        if (check(xs,ys,xe,ye,k,n)) cout << "YES" << '\n';
        else cout << "NO" << '\n';
        q--;
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
