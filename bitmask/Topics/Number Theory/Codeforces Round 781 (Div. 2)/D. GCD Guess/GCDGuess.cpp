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

int ask(int a, int b) {
    cout << '?' << " " << a << " " << a + b << endl;
    int ans;
    cin >> ans;
    return ans;
}

// this is a very unique problem.
// a new technique, a new trick for me.
// it boils down to using the remainder (what we have)
// to construct the number for the current bit based on the remainder of the previous bits
// for each query, we can ask ask((1 << (i - 1)) - r, (1 << i));, where r is the remainder
// up to the (i-1)th bits so far.
// The query becomes ask((2^(i-1)- r, 2^i+2^(i-1)-r));
// from there the ans for the gcd will return either 2^i or 
// a value less than 2^i
// for a value less than 2^i 
// => the current bit (i-1) is not set for x
// => we dont need to add it to our remainder
// for a value equal to 2^i
// => the current bit (i-1) is set for x
// => we set it, while also using this as our remainder for the next bits to come

void solve() {
    int r = 0;
    for (int i = 1; i <= 30; i++) { // the current bit we are checking is always i-1.
        int ans = ask((1 << (i - 1)) - r, (1 << i));
        if (ans == (1 << i)) r += (1 << (i - 1));
    }
    cout << '!' << " " << r << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    // solve();
    return 0;
}

