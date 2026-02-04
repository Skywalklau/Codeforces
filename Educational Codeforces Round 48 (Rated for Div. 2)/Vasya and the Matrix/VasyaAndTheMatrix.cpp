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

void fast_io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

void solve() {
    int n, m;
    cin >> n >> m;

    vll a(n), b(m);
    for (ll &x : a) cin >> x;
    for (ll &x : b) cin >> x;

    ll row_xor = 0, col_xor = 0;
    for (ll x : a) row_xor ^= x;
    for (ll x : b) col_xor ^= x;


    // a1 ^ a2 ^ ... ^ an == b1 ^ b2 ^ ... ^b3 to form a valid matrix.
    if (row_xor != col_xor){
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    vvll C(n, vll(m, 0));

    for (int j = 1; j < m; ++j) C[0][j] = b[j];
    for (int i = 1; i < n; ++i) C[i][0] = a[i];

    // top left : a[0] = C[0][0] ^ C[0][1] ^ C[0][2] ^ ... ^ C[0][m-1]
    // since we want 0th row to satisfy a[0]
    // and we know C[0][1] = b[1], C[0][2] = b[2] ... C[0][m-1] = b[m-1]
    // => C[0][0] = a[0] ^ b[1] ^ b[2] ^ ... ^ b[m-1]
    // XOR of the whole 0th row = a[0]

    // or top left : b[0] = C[0][0] ^ C[1][0] ^ C[2][0] ^ ... ^ C[n-1][0]
    // since we want 0th column to satisfy b[0]
    // and we know C[1][0] = a[1], C[2][0] = a[2] ... C[n-1][0] = a[n-1]
    // => C[0][0] = b[0] ^ a[1] ^ a[2] ^ ... ^ a[n-1]
    // XOR of the whole 0th column = b[0]

    C[0][0] = a[0] ^ (accumulate(b.begin() + 1, b.end(), 0LL, bit_xor<ll>()));

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cout << C[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    fast_io();
    solve();
    return 0;
}
