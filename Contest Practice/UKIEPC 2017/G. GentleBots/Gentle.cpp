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


void solve() {
	int x1, y1, z1, nx1, ny1, nz1;
    int x2, y2, z2, nx2, ny2, nz2;  

    cin >> x1 >> y1 >> z1 >> nx1 >> ny1 >> nz1;
    cin >> x2 >> y2 >> z2 >> nx2 >> ny2 >> nz2;

    array<int,3> Apos = {x1, y1, z1};
    array<int,3> Aend = {nx1, ny1, nz1};
    array<int,3> Bpos = {x2, y2, z2};
    array<int,3> Bend = {nx2, ny2, nz2};

    // random engine
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0.0, 1.0);

    
    cout << "(" << Apos[0] << " " << Apos[1] << " " << Apos[2] << ") ("
         << Bpos[0] << " " << Bpos[1] << " " << Bpos[2] << ")\n";\

    auto clamp = [&](int v){
        return max(-1000, min(1000, v));
    };

    auto sign_step = [&](int diff){
        if (diff > 0) return 1;
        if (diff < 0) return -1;
        return 0;
    };

    while (Apos != Aend || Bpos != Bend){
        array<int,3> Atar = Apos;
        array<int,3> Btar = Bpos;

        // A's priority: x (0) then y (1) then z (2)
        if (Apos[0] != Aend[0]){
            Atar[0] += sign_step(Aend[0] - Apos[0]);
        } 
        else if (Apos[1] != Aend[1]){
            Atar[1] += sign_step(Aend[1] - Apos[1]);
        } 
        else if (Apos[2] != Aend[2]){
            Atar[2] += sign_step(Aend[2] - Apos[2]);
        }

        // B's priority: y (1) then z (2) then x (0)
        if (Bpos[1] != Bend[1]){
            Btar[1] += sign_step(Bend[1] - Bpos[1]);
        } 
        else if (Bpos[2] != Bend[2]){
            Btar[2] += sign_step(Bend[2] - Bpos[2]);
        } 
        else if (Bpos[0] != Bend[0]){
            Btar[0] += sign_step(Bend[0] - Bpos[0]);
        }

        int retries = 0;
        // either meet at same pos, or swap pos
        while ((Atar == Btar) || (Atar == Bpos && Btar == Apos)){
            if (retries++ > 10){
                // force B to stay put to avoid infinite loop
                Btar = Bpos;
                break;
            }

            if (Atar == Btar){
                Btar = Bpos; // reset Btar to current Bpos
            }

            if (Atar == Bpos && Btar == Apos){
                double rnd = dist(gen);
                Atar = Apos;
                Btar = Bpos;
                if (rnd < 0.33){
                    Atar[0] = clamp(Atar[0] + 1);
                    Btar[0] = clamp(Btar[0] - 1);
                } 
                else if (rnd > 0.66){
                    Atar[1] = clamp(Atar[1] + 1);
                    Btar[1] = clamp(Btar[1] - 1);
                } 
                else{
                    Atar[2] = clamp(Atar[2] + 1);
                    Btar[2] = clamp(Btar[2] - 1);
                }
            }
        }

        Apos = Atar;
        Bpos = Btar;

        cout << "(" << Apos[0] << " " << Apos[1] << " " << Apos[2] << ") ("
             << Bpos[0] << " " << Bpos[1] << " " << Bpos[2] << ")\n";
    }
}

int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    // sieve();
    // precompute_prime_factors(); // modified sieve
    // int t;
    // cin >> t;
    // while (t--) solve();
    solve();
    return 0;
}
