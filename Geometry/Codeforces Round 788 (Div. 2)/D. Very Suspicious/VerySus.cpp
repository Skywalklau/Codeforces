#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define all(v) (v).begin(), (v).end()
#define sz(x) (int)(x).size()
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define F first
#define S second

// Constants
const int MOD = 1000000007;
const int INF = 1e9;
const ll LINF = 1e18;

// Utility Functions
template <typename T>
void printVector(const vector<T>& vec) {
    for (const auto& el : vec) cout << el << " ";
    cout << "\n";
}

bool is_prime(int x) { // Iterate up to the square root of x
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

// Global Variables
vector<ll> fact, inv_fact;

// Function to calculate modular exponentiation
ll mod_exp(ll base, ll exp, ll mod) {
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Precompute factorials and modular inverses
void precompute_factorials(int n, ll mod) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = (fact[i - 1] * i) % mod;
    for (int i = 0; i <= n; i++) inv_fact[i] = mod_exp(fact[i], mod - 2, mod);
}

// Calculate nCr % MOD
// to use this just call precompute_factorials
ll nCr(int n, int r, ll mod) {
    if (n < r || r < 0) return 0;
    return (((fact[n] * inv_fact[r]) % mod) * inv_fact[n - r]) % mod;
}

// global variables
vll memo(38729);

// most optimal line arrangement in terms of gradients comes in a cylce: [1,0,-1] in any order
// every 3 lines drawn must have the gradients [1,0,-1] in any order for most triangles to form
// no. of lines  :    [2, 3,  4,  5,  6,  7,  8,  9, 10, 11, 12]
// no. of triangles : [2, 6, 10, 16, 24, 32, 42, 54, 66, 80, 96...]
// pattern found :    [2, 4, 4,  6,  8,  8,  10, 12, 12, 14, 16...]
// so just precompute the pattern and binary search.

void preCompute(){
    memo[0] = 2;
    ll x = 2, diff= 4;
    int count = 0;
    ll term = 1;

    while (x <= 1000000009){
        if (count == 2){
            count = 0;
            diff += 2;
            x += diff;
            diff += 2;
        }
        else{
            x += diff;
            count++;
        }
        memo[term] = x;
        term++;
    }
}

void solve() {
    int n;
    cin >> n;
    
    int low = 0, high = 38728;
    int mid = 0;
    int ans = -1;

    while (low <= high){
        mid = low + (high - low) / 2;
        
        if (memo[mid] == n){
            ans = mid;
            break;
        }
        else if (memo[mid] < n) {
            low = mid + 1;
        } else {
            ans = mid;
            high = mid - 1;
        }
    }

    cout << ans + 2 << endl;
}

int main() {
    fast_io();
    int t;
    preCompute();
    cin >> t;
    while (t--) solve();
    return 0;
}