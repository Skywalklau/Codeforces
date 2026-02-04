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


// solve time ~ 1hr 25 mins
// bruh, stupid ass implementation problem man...
// Like, its not even hard, just annoying to implement.
// Lets make some observations.
// they want a and b to be ascending, and each a[i] < b[i].
// What does this tell us?
// that means actually there are only 2 ways this can happen.
// Case 1:
// 1 2 3 ... n
// n+1 n+2 n+3 ... 2n
// Case 2:
// 1 3 5 ... 2n-1
// 2 4 6 ... 2n
// And in no other way can we form another valid combo.
// Proof:
// lets look at what a[1] can be.
// lets say a[1] != 1, then fix any number to it, lets say 2.
// then, where will 1 go?
// if you put it anywhere for j > 1 for a[j], then its no increasing.
// if you put below, then a[j] > b[j] for any j from 1 to n.
// So, a[1] must be 1.
// ok, then what about a[2]?
// lets say we put a number != 2 or 3 for contradiction.
// then maybe say put 4.
// ok, then we know a[1] is 1.
// so the seq. look like this :
// 1 4 x x x ...
// y x x x x ...
// what is y then?
// it must be > 1, we defo cannot put > 3 because
// then where will 2 and 3 go? You can't put in a anymore because 4 > 2
// and 4 > 3.
// So, they must be below, and in front.
// Ok, then put 2 (because if put 3 first then where will 2 go?) 
// as b[1], now what about b[2]?
// well, the next best candidate is 3, but a[2] = 4 > b[3] = 3
// So, its impossible to form the condition that they want now.
// Hence, it a[2] can only be 2 choices, 2 or 3.
// and if we put 2,
// then the sequence must be case 1.
// otherwise it must be case 2 because we set a[2] = 3.
// Since they guarantee a valid solution exists, we can just try both.
// And thats the solution.


void solve() {
	int n, k, m;
    cin >> n;
    
    vi a(n+1), b(n+1);
    map<int, int> A;
    map<int, int> B;
    for (int i=1; i<=n; i++){
        cin >> a[i];
        A[a[i]] = i;
    }
    for (int i=1; i<=n; i++){
        cin >> b[i];
        B[b[i]] = i;
    } 

    vi tempa = a, tempb = b;
    map<int,int> tempA = A;
    map<int, int> tempB = B;

    vpii result;
    for (int i=1; i<=n; i++){
        if (a[i] == i) continue;

        if (A.count(i)){ // i is in a
            int pos = A[i];
            while (pos > i){
                swap(a[pos], a[pos-1]);
                result.pb({1, pos-1});
                A[a[pos]] = pos;
                A[a[pos-1]] = pos-1;
                pos--;
            }
            while (pos < i){
                swap(a[pos], a[pos+1]);
                result.pb({1, pos});
                A[a[pos]] = pos;
                A[a[pos+1]] = pos+1;
                pos++;
            }
        } 
        else{ // i is in b
            int pos = B[i];
            while (pos > i){
                swap(b[pos], b[pos-1]);
                result.pb({2, pos-1});
                B[b[pos]] = pos;
                B[b[pos-1]] = pos-1;
                pos--;
            }
            while (pos < i){
                swap(b[pos], b[pos+1]);
                result.pb({2, pos});
                B[b[pos]] = pos;
                B[b[pos+1]] = pos+1;
                pos++;
            }
            // swap between a and b
            swap(a[i], b[i]);
            result.pb({3, i});
            A[a[i]] = i;
            B[b[i]] = i;
            A.erase(b[i]);
            B.erase(a[i]);
        }
    }
    // b only contains n+1 to n in some order now 
    for (int i=n+1; i<=2*n; i++){
        int idx = i-n;
        if (b[idx] == i) continue;

        int pos = B[i];
        while (pos > idx){
            swap(b[pos], b[pos-1]);
            result.pb({2, pos-1});
            B[b[pos]] = pos;
            B[b[pos-1]] = pos-1;
            pos--;
        }
        while (pos < idx){
            swap(b[pos], b[pos+1]);
            result.pb({2, pos});
            B[b[pos]] = pos;
            B[b[pos+1]] = pos+1;
            pos++;
        }
    }

    // cout << "ddddddddddddddddddddddddddddd" << endl;
    // printVector(a);
    // printVector(b);
    // cout << "ddddddddddddddddddddddddddddd" << endl;

    if (sz(result) <= 1709){
        cout << sz(result) << '\n';
        for (int i=0; i<sz(result); i++){
            cout << result[i].F << " " << result[i].S << '\n';
        } 
        return;
    }
    
    clr(result);
    a = tempa, b = tempb;
    A = tempA, B = tempB;

    for (int i=1; i<=n; i++){
        int val = 2*i - 1;  // odd number
        if (a[i] == val) continue;

        if (A.count(val)){
            int pos = A[val];
            while (pos > i){
                swap(a[pos], a[pos-1]);
                result.pb({1, pos-1});
                A[a[pos]] = pos;
                A[a[pos-1]] = pos-1;
                pos--;
            }
            while (pos < i){
                swap(a[pos], a[pos+1]);
                result.pb({1, pos});
                A[a[pos]] = pos;
                A[a[pos+1]] = pos+1;
                pos++;
            }
        } 
        else{
            int pos = B[val];
            while (pos > i){
                swap(b[pos], b[pos-1]);
                result.pb({2, pos-1});
                B[b[pos]] = pos;
                B[b[pos-1]] = pos-1;
                pos--;
            }
            while (pos < i){
                swap(b[pos], b[pos+1]);
                result.pb({2, pos});
                B[b[pos]] = pos;
                B[b[pos+1]] = pos+1;
                pos++;
            }
            // cross swap between a and b
            swap(a[i], b[i]);
            result.pb({3, i});
            // update maps correctly
            A[a[i]] = i;
            B[b[i]] = i;
            A.erase(b[i]);
            B.erase(a[i]);
        }
    }
    
    // b only contains even numbers in some order now 
    for (int i=1; i<=n; i++){
        int val = 2*i;  // even number
        if (b[i] == val) continue;

        int pos = B[val];
        while (pos > i){
            swap(b[pos], b[pos-1]);
            result.pb({2, pos-1});
            B[b[pos]] = pos;
            B[b[pos-1]] = pos-1;
            pos--;
        }
        while (pos < i){
            swap(b[pos], b[pos+1]);
            result.pb({2, pos});
            B[b[pos]] = pos;
            B[b[pos+1]] = pos+1;
            pos++;
        }
    }

    // printVector(a);
    // printVector(b);

    cout << sz(result) << '\n';
    for (int i=0; i<sz(result); i++){
        cout << result[i].F << " " << result[i].S << '\n';
    } 


}

int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    // sieve();
    // precompute_prime_factors(); // modified sieve
    int t;
    cin >> t;
    while (t--) solve();
    // solve();
    return 0;
}
