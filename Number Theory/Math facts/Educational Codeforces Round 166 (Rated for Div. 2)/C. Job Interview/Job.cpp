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
using vpll = vector<pair<long long, long long>>;
using vvpii = vector<vector<pair<int, int>>>;
using vpstrstr = vector<pair<str, str>>;
using vpvivi = vector<pair<vector<int>,vector<int>>>;
using vvb = vector<vector<bool>>;
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
#define mne min_element

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
    if (x == 1) return false;
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
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits

// solve time ~ can't solve, but this was a really good problem.
// I learned a new trick.
// The most important thing to notice is that the order matters.
// Meaning whoever comes first, and is a better programmer / tester will be
// give that role, even if later on we found a better candidate for a certain 
// role but we don't have space anymore, this person will be selected for the
// other role instead.
// So, we can't dp this, because we cannot choose for ourselves the order
// in which to selected the candidates.
// Remember, who comes first, and has a better role will get that role if we
// have space, otherwise this candidate is forced to pick the other role.
// So, we can simulate this for all n+m+1 candidates rather than n+m
// candidates.
// Why?
// Lets picture this. When you remove a candidate at some index i.
// How will the sum change?
// There are 2 cases:
// Case 1: This person was a programmer.
// Then now, we need to select a new programmer > i (because for < i whatever
// programmer we can choose, we already chosen).
// And notice that we only need to choose 1 more of such programmer > i.
// Here's the trick, we can use a sum, call it sum1 which holds n+1 programmers
// and m testers, so it will be a total of n+m+1 candidates.
// We do this process linearly, we first calculate the score without removing
// anyone, and we choose the first n+1 viable programmers, then the remaining
// are testers.
// Now, if the person we removed is a programmer, then all we need to do is 
// just do sum1 - a[i].
// Makes sense if you think about it. Because sum1 is for n+m+1 candidates with
// one extra programmer, if we remove a programmer we get n+m candidates with
// n progammers and m testers.
// Visually it looks like this:
// a  a  a     a
//   b  b  b  b
// a are programmers, b are testers.
// so lets say we removed the first candidate, which is a programmer.
// Then who is the next programmer we can pick? It will be the last a that we 
// chosen from n+m+1 candidates.
// The same follows are the 2nd and 3rd programmer.
// Except the last progammer, when we remove this guy, we already have all
// n programmers we need behind this person already, so implicitly this guy
// is also handled if he is a programmer.
// We can extrapolate this idea to testers now.
// so instead of n+1 programmers, m testers. We do n programmers, m+1 testers.
// And if this person we wanna remove is chosen as a tester, we do sum2 - b[i]
// to implicitly get the next best tester which is in sum2.
// And thats all we need, insanely smart solution. I love it.

void solve() {
	ll n, k, m;
    cin >> n >> m;

    int N = n + m + 1;
	vll a(N), b(N), c(N);
	for (ll&x : a) cin >> x;
	for (ll&x : b) cin >> x;
 
	int cnt1 = n+1, cnt2 = m;
	ll sum1 = 0;
	for(int i=0; i<N; i++){
		if((cnt1 > 0 && a[i] > b[i]) || cnt2 == 0){
			cnt1--;
			sum1 += a[i];
			c[i] = 1;
		} 
        else{
			cnt2--;
			sum1 += b[i];
			c[i] = 2;
		}
	}
    
	cnt1 = n, cnt2 = m+1;
	ll sum2 = 0;
	for(int i=0; i<N; i++){
		if((cnt1 > 0 && a[i] > b[i]) || cnt2 == 0){
			cnt1--;
			sum2 += a[i];
		} 
        else{
			cnt2--;
			sum2 += b[i];
		}
	}
	
	for(int i=0; i<N; i++){
		if(c[i] == 1) cout << sum1 - a[i] << " ";
        else cout << sum2 - b[i] << " ";
		
	}
	cout << '\n';

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
