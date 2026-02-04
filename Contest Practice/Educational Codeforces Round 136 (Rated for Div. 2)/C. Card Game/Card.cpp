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
using vvld = vector<vector<ld>>;
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

const ll K = 6e6+5; // change according to your needs
vll mn(K, 0); // Smallest prime factor of each number
vvll fcv(K); // Prime factorization for each number (only returns each distinct factor once)


void precompute_prime_factors() { // Modified Sieve
    mn[1] = 1; // Base case: 1 has no prime factors
    for (ll i = 2; i < K; i++) {
        if (!mn[i]) { // If i has no prime factor recorded yet, it is a prime number.
            for (ll j = 1; j * i < K; ++j) {
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

void sieve() {
    mn[1] = 1; // 1 is not prime
    for (ll i = 2; i < K; i++) {
        if (mn[i] == 0) { // i is prime
            mn[i] = i;
            for (ll j = i * i; j < K; j += i) {
                if (mn[j] == 0) {
                    mn[j] = i; // smallest prime factor of j
                }
            }
        }
    }
}

vi get_primes_up_to_K() {
    vi primes;
    for (ll i = 2; i < K; i++) {
        if (mn[i] == i) primes.pb(i);
    }
    return primes;
}

// get all factors up to n
vvi factors(K);

void getAllFactors(){
    for (int i = 1; i <= K; i++) {
        for (int j = i; j <= K; j += i) {
            factors[j].push_back(i); // i is a divisor of j
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

// solve time ~ 1hr
// Interesting problem, mixture of game theory + combinatorics.
// The trick to solving is quite simple, we need to find the optimal move for Alex.
// Once we know the all the moves for Alex, we can easily find all the moves for Boris.
// since we know draw is always 1 (hint: the samples cases are all 1 for draw). 
// So, what is the best move for Alex?
// 1st round: if Alex has the biggest card, he plays that and wins immediately.
// So there is n-1Cn/2-1 ways.
// 2nd round: meaning 1st round cannot conclude.
// then what observations can we make?
// That means Alex must have the 2nd largest card.
// Because if Boris has both largest and 2nd largest card, he will win. 
// So, Alex has the 2nd largest card if the game continues to the 2nd round.
// Now, the perspective changes to Boris going first, but the idea is exactly the same.
// If we want Alex to win, then he must have the 2 largest cards left to win now (since
// Boris plays first).
// 3rd round: Alex goes first, same idea, Alex plays the largest card available, he wins.
// 4th round: Boris goes first, Alex must have the 2 largest cards remaining to win.
// we keep going on and on until the end.
// Now, lets think about the number of ways this can happen for Alex to win.
// at some ith round (1 indexed), this means we played (i-1)*2 cards already.
// Optimally, both players will play the largest card available, because they want to
// bait out the largest card of the opponent.
// But, the game ends when the opponent has no bigger card available to survive.

// So, odd rounds, notice that the number of ways is just:
// nCr(n-(i-1)*2-1, n/2-(i-1)-1)
// where i is the round number, n is the number of cards.
// since we are on the ith round, then for sure that means we played (i-1)*2 cards
// up till this round so far (excluding the current round).
// we -1 because we will fix the largest card of Alex at this current round (which
// is the biggest card currently at this point).
// Then Bob has no cards to play so he loses.
// Hence Alex has n/2-(i-1)-1 slots left which can be any card
// and he can choose from n-(i-1)*2-1 cards left.
// Again, -1 because we fix the largest card remaining at the current round so that
// Alex wins in this round. So, we have n-(i-1)*2-1 cards left.

// For even rounds, the number of ways is just:
// nCr(n-(i-1)*2-2, n/2-(i-1)-2)
// this follows the same idea, except now we play 2 cards to guarantee Alex wins.
// Because now the perspective is Boris goes first.
// So, to guarantee a win, Alex must have the 2 largest cards remaining at any current
// round.
// hence, we fix 2 cards.
// We have n-(i-1)*2-2 choices to choose from.
// and we have n/2-(i-1)-2 slots left to place the cards.
// There is a pitfall tho, n/2-(i-1)-2 can be < 0, because it could be the case
// that on the last round, we have 1 slot left, but for Alex to win this round, he 
// must have 2 of the biggest cards.
// But obviously we can't even put 2 cards with 1 slot. Implicitly, this means draw/loss
// is the only option left. So we can just quit the loop or continue (since next
// round the game ends).

// Now we proof why draw is only 1 way.
// At this point, I think its obvious why after reading the description.
// The idea is that we basically keep extrapolating odd and even round cases until
// the end, and there is exactly 1 way to draw.
// Basically, the observation is quite simple:
// Notice that, whoever goes first will play the current biggest card they have
// to bait the opponent's largest card.
// if the current round is player A goes first, then:
// player A wins: if player A has the current biggest card.
// player B wins: if player B has the current largest and 2nd largest card.
// undecided: if player A has the 2nd largest card, player B has the largest card.
// Then we keep extrapolating this idea, regardless of whose turn it is until the end.
// In the end, no one wins. And there is exacltly 1 way this can happen.
// And thats the solution.
// The number of ways for Boris will just be total - Alex - 1.

void solve() {
	int n, k, m;
    cin >> n;

    ll ans = 0;
    for (int i=1; i<=n/2; i++){
        if (i % 2 == 1){
            ans = (ans + nCr(n-(i-1)*2-1, n/2-(i-1)-1, MOD2)) % MOD2; 
        }
        else{
            if (n/2-(i-1)-2 < 0) continue;
            ans = (ans + nCr(n-(i-1)*2-2, n/2-(i-1)-2, MOD2)) % MOD2; 
        }
    }
    
    ll total = nCr(n, n/2, MOD2);
    cout << ans << " " << (total - ans - 1 + MOD2) % MOD2 << " " << 1 << '\n';

}

int main() {
    fast_io();
    precompute_factorials(60, MOD2);
    // sieve();
    // precompute_prime_factors(); // modified sieve
    int t;
    cin >> t;
    while (t--) solve();
    // solve();
    return 0;
}
