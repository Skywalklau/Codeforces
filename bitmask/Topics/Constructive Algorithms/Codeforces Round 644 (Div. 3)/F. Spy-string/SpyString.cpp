#include <bits/stdc++.h>
using namespace std;

using str = string;
using ch = char;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vstr = vector<str>;

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

// if there is a valid string that satisfies the condition
// that string will differ by at most on character
// we can just take the first string, change every character in that string from a to z
// and check if all other string satisfies what we want.
// if so then we found a possible answer and just return it.
// brute force in other words.
// time complexity : O(M*26*N*M) == O(N*M^2)
void solve(){
    int n, m;
    cin >> n >> m;
    vstr arr(n); 
    for (int i=0; i<n; i++) cin >> arr[i];

    str ans = arr[0];

    for (int i=0; i<m; i++){
        ch save = ans[i];
        for (ch k = 'a'; k <= 'z'; k++){
            ans[i] = k;
            bool flag = true;
            for (int j=0; j<n; j++){
                int errors = 0;
                for (int z=0; z<m; z++){
                    if (ans[z] != arr[j][z]) errors++;
                    if (errors > 1){
                        flag = false;
                        break;
                    }
                }

                if (!flag) break;
            }

            if (flag){
                cout << ans << '\n';
                return;
            }

        }

        ans[i] = save;
    }

    cout << -1 << '\n';

}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
