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
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

// Utility Functions
template <typename T>
void printVector(const vector<T>& vec) {
    for (const auto& el : vec) cout << el << " ";
    cout << "\n";
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
ll nCr(int n, int r, ll mod) {
    if (n < r || r < 0) return 0;
    return (((fact[n] * inv_fact[r]) % mod) * inv_fact[n - r]) % mod;
}

void solve() {
    // Input
    int n, k;
    cin >> n >> k;   

    // let AND == and of whole array
    // let XOR == xor of whole array
    // base case
    // when k==0, there is only 1 array of all zeros since we want numbers < 2^k and k == 0
    // so only choice is 0 of length n, according to the question.
    // so AND == XOR == 0
    // => 1 way to form such array.
    if (k == 0){
        cout << 1 << endl;
        return;
    }

    // Precompute factorials
    precompute_factorials(n, MOD);

    // Precompute the number of ways to choose an even number of indices from n
    // Note, we only compute nC2 + nC4 + nC6 + ... nC2y
    // where 2y <= n-1
    ll binomialConstant = 0;
    for (int i = 0; i <= n-1; i += 2) {
        binomialConstant = (binomialConstant + nCr(n, i, MOD)) % MOD;
    }

    vvll dp(k, vll(2));

    // dp[i][0] = AND == XOR at the ith bit
    // dp[i][1] = AND > XOR at the ith bit

    // Dynamic programming to process each bit from k-1 to 0
    for (int i = 0; i < k; i++){

        if (i == 0){
            //base cases
            // if n is even, then for AND > XOR, the bits for each number 
            // at i==0 must be 1 so that AND == 1 and XOR == 0 at i==0 bit.
            // there is one way of doing this since there is only 1 bit.

            // if n is odd, then AND > XOR is impossible, since for each number
            // for AND == 1 at the 0th bit all the bits must be 1.
            // but since n is odd, XOR == 1
            // Why? because 1 == 1, 1 ^ 1 ^ 1 == 1, 1 ^ 1 ^ 1 ^ 1 ^ 1 == 1
            // hence XOR == 1 and AND == XOR == 1 => 0 ways
            dp[i][1] = (n % 2 == 0 ? 1 : 0);

            // For AND == XOR
            // we have 2 cases, when AND == XOR == 1 or AND == XOR == 0
            // at the 0th bit.

            // subCase 1: AND == XOR == 1
            // this means that all the numbers at the 0th bit must be 1 for AND == 1.
            // Knowing that all the numbers with 0th bit == 1.
            // There are 2 more cases to consider for subCase 1
            // if n is odd: XOR == 1 since 1 ^ 1 ^ 1 == 1, 1 ^ 1 ^ 1 ^ 1 ^ 1 == 1 ...
            // => 1 way
            // if n is even: XOR == 0 since x ^ x == 0, 1 ^ 1 ^ 1 ^ 1 == 0 ...
            // => 0 way
            // Therefore, if n is odd, there is 1 way for which the condition AND == XOR == 1
            // is satisfied => 1 way
            // and if n is even, there is no way for which the condition AND == XOR == 1
            // is satisfied => 0 way

            // subCase 2: AND == XOR == 0
            // this means that at least 1
            // number of bits in the 0th bit has to be == 0 for AND == 0
            // knowing that at least 1 number of bits with 0th bit == 0 causes AND == 0
            // We can now consider XOR
            // for XOR == 0,
            // we know that 1 ^ 1 == 0, 1 ^ 1 ^ 1 ^ 1 == 0 ...
            // This implies that we must have 1's occurring in even counts
            // so we must have 0 bits of 1s || 2 bits of 1s || 4 bits of 1s ... || (n-1) bits of 1s
            // when n is odd
            // 0 bits of 1s || 2 bits of 1s || 4 bits of 1s ... || (n-2) bits of 1s
            // when n is even
            // Why? Because if n is even, then we cannot choose all bits to be 1s, otherwise AND==1
            // Because if n is odd, this is a trivial case, we can never choose all bits to be 1s
            // as we must choose 1s in even counts.


            // So, if n is even, adding both subcases gives
            // 0 + 0 bits of 1s || 2 bits of 1s || 4 bits of 1s ... || (n-2) bits of 1s
            // If n is odd, adding both subcases gives
            // 1 + 0 bits of 1s || 2 bits of 1s || 4 bits of 1s ... || (n-1) bits of 1s

            dp[i][0] = ((n % 2 == 1 ? 1 : 0) + binomialConstant) % MOD;

        }

        else{
            // Handle transition states
            
            // dp[i][1] => AND > XOR
            // following the same principle from the base case, we get
            // dp[i][1] = ((n % 2 == 0 ? 1 : 0)
            // Now, notice that the (i-1) bits of ALL n numbers can be anything
            // since the MSF is 1, no matter what bits you choose before the ith bit, AND > XOR
            // since you must have n numbers and each number behind the ith bit has (i-1) bits
            // total combinations are 2^(n*i)
            // we multiply by i instead of i-1 because of 0-index
            // so the transition is the line below
            ll powerOf2N = mod_exp(2, n, MOD); 
            dp[i][1] = ((n % 2 == 0 ? 1 : 0) * mod_exp(powerOf2N, i, MOD)) % MOD;

            // dp[i][0] => AND == XOR
            // following the same principle from the base case, we get
            // dp[i][0] = ((n % 2 == 1 ? 1 : 0) + binomialConstant) % MOD;
            // Now, notice that the dp[i][0] can be built on top of dp[i-1][0] + dp[i-1][1] (the
            // total number of valid configurations for the lower i-1 bits)
            // so the transition is the line below

            dp[i][0] = 
            ((((n % 2 == 1 ? 1: 0) + binomialConstant) % MOD) * ((dp[i-1][0] % MOD + dp[i-1][1] % MOD) % MOD)) % MOD;
        }

    }

    ll ans = (dp[k-1][0]%MOD + dp[k-1][1]%MOD)%MOD;
    // we need if (ans < 0) ans += MOD; to prevent overflow since 
    // dp[k-1][0]%MOD could be == 2^63-1
    // dp[k-1][1]%MOD could be == 2^63-1
    // so we would not be able to catch overflow.
    if (ans < 0) ans += MOD;
    cout << ans << endl;

}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}


//Below is my take, which is wrong
// #include <bits/stdc++.h>
// using namespace std;

// using ll = long long;
// using ull = unsigned long long;
// using ld = long double;
// using vi = vector<int>;
// using vvi = vector<vector<int>>;
// using vll = vector<ll>;
// using vvll = vector<vector<ll>>;
// using pii = pair<int, int>;
// using pll = pair<ll, ll>;

// #define all(v) (v).begin(), (v).end()
// #define sz(x) (int)(x).size()
// #define pb push_back
// #define eb emplace_back
// #define mp make_pair
// #define F first
// #define S second

// // Constants
// const int MOD = 1e9 + 7;
// const int INF = 1e9;
// const ll LINF = 1e18;

// // Utility Functions
// template <typename T>
// void printVector(const vector<T>& vec) {
//     for (const auto& el : vec) cout << el << " ";
//     cout << "\n";
// }

// // Fast Input/Output
// void fast_io() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     cout.tie(nullptr);
// }

// // Global Variables
// vector<ll> fact, inv_fact;

// // Function to calculate modular exponentiation
// ll mod_exp(ll base, ll exp, ll mod) {
//     ll result = 1;
//     while (exp > 0) {
//         if (exp & 1) result = (result * base) % mod;
//         base = (base * base) % mod;
//         exp >>= 1;
//     }
//     return result;
// }

// // Precompute factorials and modular inverses
// void precompute_factorials(int n, ll mod) {
//     fact.resize(n + 1);
//     inv_fact.resize(n + 1);
//     fact[0] = inv_fact[0] = 1;
//     for (int i = 1; i <= n; i++) fact[i] = (fact[i - 1] * i) % mod;
//     for (int i = 0; i <= n; i++) inv_fact[i] = mod_exp(fact[i], mod - 2, mod);
// }

// // Calculate nCr % MOD
// ll nCr(int n, int r, ll mod) {
//     if (n < r || r < 0) return 0;
//     return (((fact[n] * inv_fact[r]) % mod) * inv_fact[n - r]) % mod;
// }

// void solve() {
//     // Input
//     int n, k;
//     cin >> n >> k;   

//     if (k == 0){
//         cout << 1 << endl;
//         return;
//     }
    
//     precompute_factorials(n, MOD);

//     ll binomialConstant = 0;
//     for (int i = 0; i <= n-1; i += 2) {
//         binomialConstant = (binomialConstant%MOD + nCr(n, i, MOD)%MOD) % MOD;
//     }

//     vvll dp(k, vll(2));

//     // dp[i][0] = all bit is 1
//     // dp[i][1] = some bit is 0

//     // Dynamic programming to process each bit from k-1 to 0
//     for (int i = 0; i < k; i++){
//         if (i == 0){
//             dp[i][0] = 1;
//             dp[i][1] = binomialConstant;

//         }
//         else{
//             ll powerOf2N = mod_exp(2, n, MOD); 
//             dp[i][0] = mod_exp(powerOf2N, i, MOD);
//             dp[i][1] = ((binomialConstant % MOD) * ((dp[i-1][0] % MOD + dp[i-1][1] % MOD) % MOD)) % MOD;
//         }

//     }

//     ll ans = (dp[k-1][0]%MOD + dp[k-1][1]%MOD)%MOD;
//     if (ans < 0) ans += MOD;
//     cout << ans << endl;

// }

// int main() {
//     fast_io();
//     int t;
//     cin >> t;
//     while (t--) solve();
//     return 0;
// }
