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

const int LOGN = 20; // sparse table interval
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits

// This problem is very similar to Zuma
// However what confused me was the fact that we are treating it almost the same 
// way as Zuma, which I thought wasn't supposed to be the case.
// My initial idea: O(N^3)
// let say our [j,i] window is dcbbaaa(a)
// then we use a flag to indicate isContiguous
// eg. if (a) meet until the first b, then isContiguous is turned off
// and then we can just do dp[j][i] = dp[j][k] + 1 for everything else until j
// and before we reach the b, we do dp[j][i] = dp[j][k-1] + 1 since its 
// still contiguous.
// But actually, this is wrong,
// proof by counterexample: let use aaadcbbaaa(a)
// it is obvious, that the best move is the remove dcbb, then all the a's
// However, with my dp transition, it will never be the case.
// it fact, it would return 5.
// So how do we solve it?
// Very similar to Zuma in terms of code, however the perspective/idea is very
// different.
// Let me explain:
// lets use aaadcbbaaa(a) as the example
// we are at (a) currently, we go through each index behind (a) until j
// which is the last element in this window aaadcbbaaa(a), which is "a".
// Now, for each element, we want to remove it if s[k] == s[i]
// and our transition would be:
// case 1, we remove s[i] itself:
// dp[j][i] = 1 + dp[j][i-1]
// case 2, we remove s[i] and s[k]:
// dp[j][i] = min(dp[j][i], dp[j][k] + dp[k+1][i-1])
// I think an imminent question is (at least for myself), why 
// do we do it like this in the first place?
// In terms of greedy, we obviously want to remove contiguous elements 
// wherever possible right? eg. aaaaabb
// you dont just remove one a or one b at a time, thats just not minimal.
// That is true, however, with dp, one IMPORTANT thing to notice is that 
// this is a reccurrence relation for the MOST OPTIMAL move (minimal in this
// case) for each range already
// meaning, dp[j][i] = min number of moves to remove all elements between
// j to i inclusive, [j,i].
// therefore, case 1 makes sense
// say we have aaaa(a)
// sure it sounds dumb that we do dp[j][i] = 1 + dp[j][i-1], which is 
// clearly unoptimal because it should just be 1 (remove the whole string).
// but thats why we have the other dp transition, which is case 2, to handle
// the scenario.
// from j<=k<=i-1, we compare each position and if s[k] == s[i], then we can
// remove it
// lets take aaa[a](a).
// index k is at [], i is at ().
// notice that, now dp[j][i] = min(dp[j][i], dp[j][k] + dp[k+1][i-1])
// and that dp[j][k] + dp[k+1][i-1] == 1 + 0 == 1.
// so then now our dp[j][i] == 1, which is the answer we want!
// Its very intuitive, lets take a more complex example, aaadcbbaa[a](a)
// we know that in our heads the answer should be 4, more specifically, we can
// break it into aaa (dcbb) aaaa, remove (dcbb) first, then remove aaaaaaa in 
// 1 move, so total moves is == 4.
// we start at (a), then we reach [a], we remove it, now we are left with
// aaadcbbaaa, since we already computed the dp for this, the dp[j][k] == 4
// hence the answer for d[j][i] == 4 as well.
// we can go further down but it can be proven that this is already the best
// answer, so I wont go further down the index to j.
// What was really bugging me however, was why the fuck are we doing 
// dp[j][k] + dp[k+1][i-1] and not dp[j][k-1] + dp[k+1][i-1] instead?
// Because I initially thought that since we are removing s[k] and s[i],
// it makes sense that our dp should instead be dp[j][k-1] + dp[k+1][i-1],
// which is exactly like the dp transition in Zuma. But I was dead wrong!
// here is why:
// from aaadcbbaaa(a), lets take a smaller sub window [a](a)
// notice that, if you do dp[j][i] = dp[j][k] + dp[k+1][i-1], then
// dp[j][i] == 1 + 0 == 1.
// however if we took dp[j][i] as:
// dp[j][i] = dp[j][k-1] + dp[k+1][i-1], then
// dp[j][i] == 0 + 0 == 0.
// Of course, our actual answer for aa is 1 (we can remove aa in one move)
// => we need to include k.
// which ultimately makes sense, because otherwise we would be neglecting
// aa, thinking that it actually cost 0 moves when it should cost 1.
// Whereas in Zuma, the reason why we can do k-1 is because of the problem
// statement itself, we can remove the 2 characters, and consider whatever
// remains in the window, and if k-1 < j, then its fine because we
// already defined an invalid state to be 0, so it would just add 0 which
// contributes nothing.
// However, in this problem, we need it.


// Think of this problem like this:
// For this problem:
// we delete k and i together along with the substring from k-1 to j
// using the last move to delete k-1 to j entirely. And that is why
// we need to do dp[j][k] instead of dp[j][k-1], because we want to 
// consider i and k as a single entity in k, hence we have to consider
// the limit up to k as well, because its not removed yet. Otherwise it
// would be something like xx, which is only 1 move, when it should be 
// xx[a(a)], which is 2 moves (we would be counting less when it should 
// be more)
// For Zuma:
// we delete k and i together along with the substring from k+1 to i-1
// using the last move to delete k+1 to i-1 entirely. And that is why
// we need to do dp[k+1][i-1] instead of dp[k][i-1], because we want to 
// consider k and i as 2 separate entities at the back of k+1, and at 
// the front of i-1. Otherwise it would be something like [a](a)xx
// which would take 2 moves when it should be [a]xx(a), which is
// 1 move (we would be counting more when it should be less).

void solve() {
	int n, k, m;
    cin >> n;
    str s;
    cin >> s;

    vvi dp(n+2, vi(n+2, MAX));

    for (int i=1; i<=n; i++){
        for (int j=i; j>=1; j--){
            if (i == j) {
                dp[j][i] = 1;  // A single character takes one move to remove.
                continue;
            }

            // Case 1: Remove s[i-1] by itself
            dp[j][i] = 1 + dp[j][i-1];

            // case 2: remove any pair of element similar to itself.
            for (int k=i-1; k>=j; k--){
                // cout << k << " " << i << endl;
                // cout << s[k-1] << " " << s[i-1] << endl;
                if (s[i-1] == s[k-1]){
                    //cout << s[k-1] << " " << s[i-1] << endl;
                    //cout << k << " " << i << endl;
                    // Ensuring valid bounds for dp[k+1][i-1]
                    int rightPart = (k+1 <= i-1) ? dp[k+1][i-1] : 0;
                    // at some k, become [j,k], [k+1,i-1]
                    // because (xxxaaa)(fcsfdw)(a)
                    // we can try all moves == a.
                    // after removing (fcsfdw)
                    // hence need to include k
                    dp[j][i] = min(dp[j][i], dp[j][k] + rightPart);
                    // if (dp[j][i] == 4){
                    //     cout << j << " " << k << " " << i << endl;
                    //     cout << dp[j][k] << " " << rightPart << endl;
                    // }
                    // cout << j << " " << k << " " << i << endl;
                    // cout << dp[j][k] << " " << rightPart << endl;
                    // cout << dp[j][i] << endl;
                }
            }
        }
        // [dacbaaa](a)(a)
    }

    cout << dp[1][n] << '\n';
    
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
