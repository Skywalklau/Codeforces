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

void solve() {
    int n, k;
    cin >> n;

    // intuition: if a(i) is large enough, it is always better to use a row operation instead
    // it is true, if a(i) > 4;
    // proof: if a(i) > 4, we need at least 3 squares == 3 moves
    // row i+1 could have more than 6 black cells
    // so it would be better to use row operation on i and i+1 => 2 moves
    // so if a(i) > 4, we definitely use 2 row operation for current row and next row.
    // so now a(i) <= 4
    // if a(i) <= 2, we use the a square for sure
    // proof by counterexample: because if a(i) <= 2, then even if row i+1 has 
    // more than 2 black cells we still use at most 2 moves.
    // otherwise if a(i+1) <=2, then we wouldn't even need to use a move, saving total
    // operations which is ideal.
    // if 2<a(i)<=4
    // we use a row operation on both i and i+1 row
    // proof by counterexample: if a(i) == 3 and a(i+1) == 6
    // then using 2 squares would not be the best solution since this needs 3 moves.
    // using 2 row operations would be the best solution since its 2 moves

    
    // Knowing this, there is one last thing to note
    // when we use a square move when a(i)<=2,
    // if a(i+1) <= 4, then at the i+1 row we still use a square.
    // this is the most optimal move
    // proof by contradiction: let a(i) == 2, a(i+1) == 4, a(i+2) == 4, a(i+3) == 2
    // we first use a square on row i.
    // by contradiction, we use a row operation on row i+1
    // then now on row i+2, we use another row operation
    // then finally we use a square on row i+3
    // => 4 moves.
    // However, if we use a square operation on row i+1
    // then on row i+2, we can use a square
    // so on row i+3, we don't need to use a move
    // => 3 moves. Which is the most optimal move.

    // Conclusion 
    // if a(i) <= 2, we use a square move for sure.
    // if a(i+1) <= 4, and we previously used a square move, 
    // then we still use a square move but on 3rd and 4th column
    // if a(i+2) <= 4, we use a square move again
    // if a(i+3) <= 2, we can skip this, saving a move.

    vi arr(n);

    for (auto &x : arr) cin >> x;

    int result = 0;
    int i=0;
    bool square1 = false, square2 = false;
    for (int i=0; i<n; i++){
        if (!square1 && !square2){
            if (arr[i] == 0) continue;
            if (arr[i] <= 2) square1 = true;
            result++;
        }
        else if (square1){
            square1 = false;
            if (arr[i] <= 2) continue;
            if (arr[i] <= 4) square2 = true;
            result++;
        }
        else{
            square2 = false;
            if (arr[i] == 0) continue;
            if (arr[i] <= 4) square1 = true;
            result++;
        }
        
    }

    cout << result << '\n';

}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
