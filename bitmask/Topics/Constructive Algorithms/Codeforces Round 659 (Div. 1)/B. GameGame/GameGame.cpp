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
const int MOD = 998244353;
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

void solve() {
    int n;
    cin >> n;
    
    // Let x be the number of ones and y be the numbers of zeros in the most significant bit 
    // of the numbers

    // if x is even, regardless of the parity of y,
    // both players will end up with the same score in that same bit position
    // so go to the next bit (if it doesn't exist then the game is a draw)
    
    // if x is odd, there will be one player with 1 in their current MSF and 0 for the other
    // player in their current MSF, this causes one of the player to lose.
    // Why? Because of the well known inequality 2^k > summation(i=0 to k-1) (2^i), where k>1 
    // for binary numbers.
    // But which player loses?
    // We know x is odd, so x % 2 == 1
    // => x % 4 == 1 or x % 4 == 3
    
    // if x % 4 == 1
    // the first player will choose 1 and the remaining 1's are a multiple of 4.
    // ie. x--; so now x % 4 == 0.
    // if y % 2 == 0
    // base case: if x % 2 == 0, y % 2 == 0, both players have equal number of 1's and 0's
    // the first player will always win because player 1 and 2 will have to pick
    // an even number of 1's and 0's after the first 1 is chosen by player 1.
    // why? Because player 1 can always choose what player 2 chooses after that to ensure he wins.
    // if y % 2 == 1
    // base case: if x % 2 == 0, y % 2 == 0, both players have equal number of 1's and 0's
    // the first player will still win because player 1 will have an odd number of 1's and 
    // an even number of 0's while player 2 will have an even number of 1's and an odd
    // number 0's 
    // why? Because player 1 can choose 1 first, then follow what player 2 chooses after each
    // round which causes player 2 to always end up with even 1's and odd 0's
    // => player 1 wins regardless

    // IMPORTANT: recall that x^x = 0, x^x^x=x, so odd XOR's of x > even XOR's of x

    // if x % 4 == 3
    // if y % 2 == 0
    // base case: if x % 2 == 0, y % 2 == 0, both players have equal number of 1's and 0's
    // player 1 will end up with even 1's and even 0's while player 2 will have odd 1's and even
    // 0's => player 2 wins
    // why? Because player 2 can always copy the move of player 1 and since player 1 goes first
    // player 1 will end up with an extra 1 such that the number of 1's is even.

    // if y % 2 == 1
    // base case: if x % 2 == 0, y % 2 == 0, both players have equal number of 1's and 0's
    // player 1 can choose an odd number of 1's and even number of 0's because player 1 can pick
    // 0 first, then this case is exactly the case of x % 4 == 3 and y % 2 == 0 but the roles
    // are reversed.
    // player 2 will have to choose an even number of 1's and even number of 0's
    // => player 1 wins


    // Lemma: The second player wins iff x % 4 == 3 and y % 2 == 0 
    // otherwise the first player wins.
    int x = 0;
    vector<int> a(n);
    for (auto &i : a){
        cin >> i;
        x ^= i;
    }

    if (x == 0){
        cout << "DRAW\n";
        return;
    }

    for (int k = 30; k >= 0; --k){
        if (x >> k & 1){
            vector<int> f(2); // {y, x}
            for (auto &i : a) ++f[i >> k & 1];
            
            if (f[1] % 4 == 3 && f[0] % 2 == 0)
                cout << "LOSE\n";
            else
                cout << "WIN\n";
            break;
        }
    }
}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

