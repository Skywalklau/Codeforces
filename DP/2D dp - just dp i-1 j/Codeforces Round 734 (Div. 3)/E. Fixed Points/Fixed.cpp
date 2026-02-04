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

// solve time ~ can't solve. But after watching some editorial I realized
// I was going in the right direction, and I solved it myself with my
// own method.
// Wow this was harder than I thought...
// I kept coming up with a O(n^3) solution, because of the sole fact that
// I did not realize that we can implicity just check the i+1,i+2,...n 
// elements in O(1) time via dp.
// I had the correct idea for the dp, but what I failed to notice is that
// if I decide to shift an element at i to some position j, then we can
// just ignore the i+1 elements onwards, because dp will handle them later.
// Why can we say this? Because in dp always solves sub-problems, and
// the sub-problem we are solving is basically the subarray itself, and
// we treat ith element as the last element in this subarray.
// So, if I removed j elements before the ith element, then a[i] shifts to
// i-j.
// We keep repeating this process for each i up to n.


// Let dp[i][j] = max number of elements that are fixed points, where:
// i: the current index we are on.
// j: the number of elements we want to keep up to the i-th element so far.
// Alternative idea: j = number of removals we made up to the i-th 
// element so far (my idea, which is the same thing but different perspective)

// Lets use my idea (alternative one)
// Base case:
// dp[1][1] = 0 && dp[1][0] = 1 if a[1] == 1 else 0
// Why? Because we removed 1 element, and there is only 1 element so far
// so dp[1][1] = 0.
// dp[1][0] means we don't remove the 1st element, so dp[1][0] = 1 if 
// a[1] = 1.

// Transition:
// case 1: remove ith element
// dp[i][j+1] = max(dp[i][j+1], dp[i-1][j]);
// j+1 because we made one more removal.
// Since we removed the ith element, we need to check dp[i-1][j] (the
// previous state it was before the removal).

// case 2: keep ith element
// dp[i][j] = max(dp[i][j], dp[i-1][j] + (a[i] == i-j));
// j because we didn't use an extra removal.
// So we need to check dp[i-1][j] (because this is the previous state
// as again we didn't make an extra removal)
// But, we add a[i] == i-j, because since we removed j elements up to i-1.
// then a[i] must be the (i-j)th element, and if its a fixed point we add
// 1 to dp[i][j] else 0.

// Like I'm actually so proud of myself for this one although I needed
// some guidance.
// I knew I was going in the right direction, I'm improving. LET'S GO!!!

// Time complexity: O(N^2)
// Space complexity: O(N^2), can be optimized to O(2*N) tho.

void solve() {
	int n, k, m;
    cin >> n >> k;

    vi a(n+1);
    for(int i=1; i<=n; i++) cin >> a[i];

    vvi dp(n+1, vi(n+1, 0));
    dp[1][1] = 0;
    dp[1][0] = (a[1] == 1 ? 1 : 0);
    

    for(int i=2; i<=n; i++){
        for(int j=0; j<=i-1; j++){
            // remove ith element
            dp[i][j+1] = max(dp[i][j+1], dp[i-1][j]);
            // keep ith element
            dp[i][j] = max(dp[i][j], dp[i-1][j] + (a[i] == i-j));
        }
    }

    int ans = MAX;
    for(int i=0; i<=n; i++) if(dp[n][i] >= k) {ans = i; break;}

    cout << (ans == MAX ? -1 : ans) << '\n';


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

// Non alternative solution where:
// Let dp[i][j] = max number of elements that are fixed points, where:
// i: the current index we are on.
// j: the number of elements we want to keep up to the i-th element so far.

// #include <bits/stdc++.h>
 
// using namespace std;
// int v[2003];
// int dp[2003][2003];
// int main()
// {
//     int t,n,i,j,k,cnt=0;
//     cin>>t;
//     while(t--)
//     {
//         cin>>n>>k;
//         for(i=1;i<=n;++i)
//         cin>>v[i];
//         for(i=1;i<=n;++i)
//             for(j=1;j<=i;++j)
//                 dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]+(v[i]==j));
//         for(i=n;i>=1;--i)
//             if(dp[n][i]>=k)
//                 break;
//         if(i==0)
//             cout<<"-1\n";
//         else
//             cout<<n-i<<'\n';
//     }
//     return 0;
// }
 