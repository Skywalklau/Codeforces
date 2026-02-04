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
using vvb = vector<vector<bool>>;
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

// Calculate nCr
// don't need to call precompute_factorials for this.
ll nCr_no_mod(int n, int r){
    if (r < 0 || r > n) return 0;
    ll res = 1;
    for (int i=1; i<=r; i++){
        res *= (n - i + 1);
        res /= i;
    }
    return res;
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
const int MAXN = 5e6+5; // fenwick = N, trie  = N * number of bits

// solve time ~ 50 mins. Ez
// The idea is that we can precompute all the possible coords that we need
// and then sort them by distance and use them accordingly.
// so its greedy + sorting.
// Notice that for t[i] == 0, we only ever want to pick the left corner
// of each unique table.
// so we can precompute that
// But for t[i] == 1 we need to compute all 4 corners.
// Now the question remains, how big can the coordinate get?
// Well, we know n <= 50000.
// So, lets think in terms of worst case scenario how big the coords 
// can get.
// if all t[i] == 0, then we need n different tables.
// and we want to find the best tables for each t[i].
// One crucial observation to notice is that the best tables form
// in a diagonal format.
// Eg.
// j
// y j
// z y j
// x z y j
// and so on...
// Knowing this, it forms an arithmetic sequence.
// so its just 50000 <= 1/2k(k+1) meaning we need at most 316 tables
// in the x and y directions. 
// This can be easily precomputed.
// What if all t[i] == 1?
// It is obvious that we will use < 316 tables in the x and y direction
// because now, we can use the 3 other corners of each table as well.
// What if some t[i] == 1 and some t[i] == 0?
// Again, it is obvious that we will use < 316 tbales in the x and y 
// direction because some t[i] == 1 guests can use the other corners
// of the tables.
// So, once we precompute the tables, we can sort them by distance.
// then do 2 pointers to get the corresponding coords of each guest
// according to their t[i].
// Don't forget to use a visited array to check for already used tables
// (we dont want overlaps).

// Time complexity: not sure how, because we are not using n.
// But ik it will fit. Let n = 317
// its n^2 + n^2log(n^2) + 4*n^2 + n^2 at most.
// which is < 2e8, so it will fit.
// Space complexity: O(4n)

vector<array<int, 3>> coord0;
vector<array<int, 3>> coord1;

void generateTableCoords(vector<array<int, 3>>& coord0, vector<array<int, 3>>& coord1){
    for (int i=0; i<=317; i++){ // tho 316 should be enuf i think
        for (int j=0; j<=317; j++){
            coord1.pb({3*i+1 + 3*j+1, 3*i+1, 3*j+1});
            coord1.pb({3*i+2 + 3*j+1, 3*i+2, 3*j+1});
            coord1.pb({3*i+1 + 3*j+2, 3*i+1, 3*j+2});
            coord1.pb({3*i+2 + 3*j+2 + 2, 3*i+2, 3*j+2});
            coord0.pb({3*i+1 + 3*j+1, 3*i+1, 3*j+1});
        }
    }

    sort(all(coord1), [&](const array<int, 3>& a, const array<int, 3>& b) {
        if (a[0] != b[0]) return a[0] < b[0]; // sort by distance
        if (a[1] != b[1]) return a[1] < b[1]; // then x
        return a[2] < b[2];                   // then y
    });

    sort(all(coord0), [&](const array<int, 3>& a, const array<int, 3>& b) {
        if (a[0] != b[0]) return a[0] < b[0]; // sort by distance
        if (a[1] != b[1]) return a[1] < b[1]; // then x
        return a[2] < b[2];                   // then y
    });
}


void solve() {
	int n, k, m;
    cin >> n;

    vvb visited(955, vb(955, false));

    int q;
    int pt0 = 0, pt1 = 0;
    for (int i=0; i<n; i++){
        cin >> q;
        if (q == 0){
            while (pt0 < sz(coord0) && visited[coord0[pt0][1]][coord0[pt0][2]]) pt0++;
            visited[coord0[pt0][1]][coord0[pt0][2]] = true;
            cout << coord0[pt0][1] << " " << coord0[pt0][2] << '\n';
        }
        else{
            while (pt1 < sz(coord1) && visited[coord1[pt1][1]][coord1[pt1][2]]) pt1++;
            // cout << "found: " << " " << coord1[pt1][1] << " " <<  coord1[pt1][2] << endl;
            visited[coord1[pt1][1]][coord1[pt1][2]] = true;
            cout << coord1[pt1][1] << " " << coord1[pt1][2] << '\n';
        }
    }


}

int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    generateTableCoords(coord0, coord1);
    int t;
    cin >> t;
    while (t--) solve();
    // solve();
    return 0;
}
