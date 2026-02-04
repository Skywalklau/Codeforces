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


// how is this bitmasking???
// Anyways, this is a bruteforce solution.
// we bruteforce over all the possible drawing sequences until we are sure to get a pink slip, 
// i.e., until the probability of drawing a pink slip becomes 1
// since v>=0.1, each time we make a draw of the second type, the probability of drawing 
// a pink slip increases by at least 0.05
// It will reach 1 after just 20 such draws. So, there will be at most d=20
// draws before we are sure to get a pink slip.
// this take O(2^d) time which is sufficient.
// time complextiy is O(2^(2/v))
// formula for expected value comes from the law of total expectation
// use the formula but tweak it for recursion the return the anwswer.


// Constants
const long double eps = 1e-9;
const long double scale = 1e+6;

long double expectedRaces(int c, int m, int p, int v) {
    long double ans = p / scale;
    if (c > 0) {
        if (c > v) {
            if (m > 0)
                ans += (c / scale) * (1 + expectedRaces(c - v, m + v / 2, p + v / 2, v));
            else
                ans += (c / scale) * (1 + expectedRaces(c - v, 0, p + v, v));
        } else {
            if (m > 0)
                ans += (c / scale) * (1 + expectedRaces(0, m + c / 2, p + c / 2, v));
            else
                ans += (c / scale) * (1 + expectedRaces(0, 0, p + c, v));
        }
    }
    if (m > 0) {
        if (m > v) {
            if (c > 0)
                ans += (m / scale) * (1 + expectedRaces(c + v / 2, m - v, p + v / 2, v));
            else
                ans += (m / scale) * (1 + expectedRaces(0, m - v, p + v, v));
        } else {
            if (c > 0)
                ans += (m / scale) * (1 + expectedRaces(c + m / 2, 0, p + m / 2, v));
            else
                ans += (m / scale) * (1 + expectedRaces(0, 0, p + m, v));
        }
    }
    return ans;
}

void solve() {
    int t;
    cin >> t;
    while (t--) {
        long double cd, md, pd, vd;
        cin >> cd >> md >> pd >> vd;
        int c = round(cd * scale);
        int m = round(md * scale);
        int p = round(pd * scale);
        int v = round(vd * scale);
        long double ans = expectedRaces(c, m, p, v);
        cout << setprecision(12) << fixed << ans << '\n';
    }
}

int main() {
    fast_io();
    // int t;
    // cin >> t;
    // while (t--) {
    //     solve();
    // }
    solve();
    return 0;
}
