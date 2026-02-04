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
    ll n, m;
    cin >> n >> m;

//  How can we check if k
//  is present in the sequence n⊕0,n⊕1,...,n⊕m?

//  If k
//  is present in the sequence, then there must be some x
//  such that 0≤x≤m
//  and n⊕x=k right?

// Did you know that n⊕k=x
// is equivalent to n⊕x=k?

// So we can just check if n⊕k≤m
// or not! Pretty simple!

// So the modified problem is to find the smallest non-negative integer k
// such that n⊕k≥m+1. Can you solve it now?

// Think using bits.

//  Let p=m+1
//  and ti
//  be the i-th bit of t. We will find the smallest k
//  such that n⊕k≥p.

// Let's build k
// greedily from the highest bit to the lowest bit. Let's say we will find the i-th bit of k
// and the higher bits have already been generated. Obviously, we will try to make this bit off if possible. 
// When will it be impossible? Think.

// If ni=pi, we can set ki=0
// as ni⊕0=ni≥pi
// If ni=1 and pi=0
// we can break here by setting the remaining bits of k
// off as no matter what the remaining bits of n are, n⊕k will always be greater than p
// Finally, if ni=0 and pi=1, we must set ki=1
// as we have no other options.

// Time Complexity: O(log(n))
// per test case.

    // By setting n^k = m+1, we are explicity setting the smallest k such that 
    // n^k>=m+1
    // if we don't set p to m+1, say p == m instead
    // then there could be a chance that n ^ k == m, which does not satisfy the 
    // inequality we want which is n^k>=m+1.

    ll p = m + 1;
    ll x = 0;

    for (int bit = 31; bit >= 0; --bit){
        ll bit_n = (n >> bit) & 1;  // Bit value of n at position 'bit'
        ll bit_p = (p >> bit) & 1;  // Bit value of p at position 'bit'

        if (bit_p == 1 && bit_n == 0){
            // If p's bit is 1 and n's bit is 0, we must turn this bit of k to 1
            x |= (1LL << bit);
        } else if (bit_p == 0 && bit_n == 1){
            // If p's bit is 0 and n's bit is 1, break early as we are already >= p
            break;
        }
        // If p's bit == n's bit, keep k's bit as 0 (no need to adjust this bit)
    }

    cout << x << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--){
        solve();
    }
    return 0;
}

