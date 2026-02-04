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

// Global variables
int mask[72];         // prime masks for numbers 1 to 70
// Frequency arrays for even/odd occurrences that stores the number of ways
// that we can form even/odd number of subsets of numbers according to their count
ll f[2][72];      
ll dp[2][1 << 20];    // DP table for bitmask states (19 prime numbers from 1 to 70)


// Precompute prime masks for numbers 1 to 70
void init() {
    // initialize base case, the freq of even count is 1
    // why? Because there is one way to form an empty subset (which is even) for each number
    for (int i = 0; i < 72; i++) f[0][i] = 1; 
    // now we precompute the prime masks for each number
    // we do prime factorization, keeping track of the parity of each prime for each number
    // i.e. 12 : prime_mask = ... 0 0 1 0
    //                        ... 7 5 3 2  
    // since 2 divides 12 four times => parity is even so bit is set to 0
    // since 3 divides 12 one time => parity is odd so bit is set to 1
    int prime_index = 0;
    for (int i = 2; i < 72; i++) {
        if (!is_prime(i)) continue;
        for (int j = 1; j < 72; j++) { // check if the prime number is a factor for each number
            int x = j;
            while (x % i == 0) { // keep dividing to find the parity of the prime factor
                x /= i;
                mask[j] ^= (1 << prime_index);
            }
        }
        prime_index++;
    }
}

void solve() {
    int n;
    cin >> n;

    // Initialize the prime masks
    init();

    // Update frequencies for input values
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        f[0][x] = f[1][x] = (f[0][x] + f[1][x]) % MOD;
        // intuition : consider empty set {} (no occurences of x)
        // f[0][x] = {} => 1 way => hence the base case
        // f[1][x] = none => 0 ways
        
        // consider {x} (1 occurences of x)
        // f[0][x] = {} => 1 way
        // f[1][x] = {x} => 1 way

        // consider {x,x} (2 occurences of x)
        // f[0][x] = {}, {x,x} => 2 ways
        // f[1][x] = {x}, {x} => 2 ways

        // consider {x,x,x} (3 occurences of x)
        // f[0][x] = {}, {x,x}, {x,x}, {x,x} => 4 ways
        // f[1][x] = {x}, {x}, {x}, {x,x,x} => 4 ways

        // hence the formula f[0][x] = f[1][x] = (f[0][x] + f[1][x]) % MOD;
        // MOD to prevent overflow
    }

    // first of all, we use dp
    // what does the dp do?
    // the dp counts the subsets of elements whose product results in a square.
    // dp[cur][mask] == number of ways to choose a subset of elements such that 
    // the parity of the prime factors matches the bitmask mask


    // Base case for DP
    // Why? There is exactly one way to to create an empty subset (no elements chosen)
    // and its product is 0 (which is a perfect square).
    dp[0][0] = 1; // Base case: one way to have a product with no elements

    int cur = 0, prev = 1;
    for (int i = 0; i <= 70; i++){ // for each number
        cur ^= 1;
        prev ^= 1;

        // Reset the `cur` DP state
        for (int msk = 0; msk < (1 << 20); msk++){
            dp[cur][msk] = 0;
        }

        // Update transitions
        for (int msk = 0; msk < (1 << 20); msk++){
            // Include the current number (flip its prime factors in the mask)
            // i contributes an odd number of times to the subset.
            // This changes the msk to msk ^ mask[i] (because odd counts flip the parity
            // of the prime factors encoded in the mask)
            // hence we * f[1][i] to get all the odd counts of subsets of i
             
            dp[cur][msk ^ mask[i]] = (dp[cur][msk ^ mask[i]] + dp[prev][msk] * f[1][i]) % MOD;
                 
            // Exclude the current number (keep the mask unchanged)
            // i contributes an even number of times to the subset
            // x ^ x = 0, so nothing changes
            // hence we * f[0][i] to get all the even counts of subsets of i
            dp[cur][msk] = (dp[cur][msk] + dp[prev][msk] * f[0][i]) % MOD;
        }
    }

    // Output the result (exclude the empty subset, whose product is 0^2)
    // we return dp[cur][0] because we want all the products of subsets that are square
    // integers => parity mask must be 0 (even parity) since square integers can always
    // be factorised into prime factors of even exponents
    cout << (dp[cur][0] - 1 + MOD) % MOD << '\n';

}

int main() {
    fast_io();
    solve();
    return 0;
}
