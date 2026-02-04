#include <bits/stdc++.h>
using namespace std;

using ch = char;
using str = string;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vpii =vector<pair<int, int>>;

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

void build1(str& result, ch symbol, int base, int height){
    for (int i=0; i<height; i++){
        for (int j=0; j<base; j++){
            result += symbol;
        }
        result += '\n';
    }
}

void build2(str& result, ch symbol1, ch symbol2, int base1, int base2, int height){
    for (int i=0; i<height; i++){
        for (int j=0; j<base1; j++){
            result += symbol1;
        }
        for (int j=0; j<base2; j++){
            result += symbol2;
        }
        result += '\n';
    }
}

void solve() {
    vector<pii> rect(3); // Store rectangles as pairs (length, width)
    map<int, char> memo = {{0, 'A'}, {1, 'B'}, {2, 'C'}};

    // Input rectangle dimensions
    for (int i = 0; i < 3; i++) {
        cin >> rect[i].F >> rect[i].S;
    }

    int maxBase = 0;
    int index = -1;

    for (int i = 0; i < 3; i++) {
        if (rect[i].F > maxBase) {
            maxBase = rect[i].F;
            index = i;
        }

        if (rect[i].S > maxBase) {
            maxBase = rect[i].S;
            index = i;
        }
    }

    // check if square is type 1 (all stack on top of each other)
    int heightRemain = abs(rect[index].F - rect[index].S);
    bool found = false;
    str result = "";

    for (int i=0; i<3; i++){
        if (i == index) continue;
        for (int j=i+1; j<3; j++){
            if (j == index) continue;
            if (rect[i].F + rect[j].F == heightRemain){
                if (rect[i].S == maxBase && rect[j].S == maxBase){ // valid square
                    build1(result, memo[index], maxBase, maxBase-heightRemain);
                    build1(result, memo[i], maxBase, heightRemain-rect[j].F);
                    build1(result, memo[j], maxBase, heightRemain-rect[i].F);
                    found = true;
                }
            }
            else if (rect[i].F + rect[j].S == heightRemain){
                if (rect[i].S == maxBase && rect[j].F == maxBase){
                    build1(result, memo[index], maxBase, maxBase-heightRemain);
                    build1(result, memo[i], maxBase, heightRemain-rect[j].S);
                    build1(result, memo[j], maxBase, heightRemain-rect[i].F);
                    found = true;
                }
            }
            else if (rect[i].S + rect[j].F == heightRemain){
                if (rect[i].F == maxBase && rect[j].S == maxBase){
                    build1(result, memo[index], maxBase, maxBase-heightRemain);
                    build1(result, memo[i], maxBase, heightRemain-rect[j].F);
                    build1(result, memo[j], maxBase, heightRemain-rect[i].S);
                    found = true;
                }
            }
            else if (rect[i].S + rect[j].S == heightRemain){
                if (rect[i].F == maxBase && rect[j].F == maxBase){
                    build1(result, memo[index], maxBase, maxBase-heightRemain);
                    build1(result, memo[i], maxBase, heightRemain-rect[j].S);
                    build1(result, memo[j], maxBase, heightRemain-rect[i].S);
                    found = true;
                }
            } 
        }
    }

    // check if square is type 2 (one base, 1 rect left and 1 rect right on top of base)
    if (!found){
        for (int i=0; i<3; i++){
            if (i == index) continue;
            for (int j=i+1; j<3; j++){
                if (j == index) continue;
                if (rect[i].F + rect[j].F == maxBase && rect[i].S == heightRemain && rect[j].S == heightRemain){
                    build1(result, memo[index], maxBase, maxBase-heightRemain);
                    build2(result, memo[i], memo[j], rect[i].F,
                    rect[j].F, heightRemain);
                    found = true;
                }
                else if (rect[i].S + rect[j].S == maxBase && rect[i].F == heightRemain && rect[j].F == heightRemain){
                    build1(result, memo[index], maxBase, maxBase-heightRemain);
                    build2(result, memo[i], memo[j], rect[i].S,
                    rect[j].S, heightRemain);
                    found = true;
                }
                else if (rect[i].F + rect[j].S == maxBase && rect[i].S == heightRemain && rect[j].F == heightRemain){
                    build1(result, memo[index], maxBase, maxBase-heightRemain);
                    build2(result, memo[i], memo[j], rect[i].F,
                    rect[j].S, heightRemain);
                    found = true;
                }
                else if (rect[i].S + rect[j].F == maxBase && rect[i].F == heightRemain && rect[j].S == heightRemain){
                    build1(result, memo[index], maxBase, maxBase-heightRemain);
                    build2(result, memo[i], memo[j], rect[i].S,
                    rect[j].F, heightRemain);
                    found = true;
                }
            }
        }
    }

    if (!found){
        cout << -1 << '\n';
    }

    else{
        cout << maxBase << '\n';
        cout << result << '\n';
    }

}

int main() {
    fast_io();
    int t;
    //cin >> t;
    //while (t--) solve();
    solve();
    return 0;
}
