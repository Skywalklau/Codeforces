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
    // subCase 1: x ^ y is divisible by x
    // let p = x ^ y where p is the largest multiple that is divisible by x
    // => y = p ^ x
    // we know that 1 <= y <= m, => 1 <= p^x <= m
    // Observation: p ^ x <= p + x since XOR is addition without carry

    // sub subCase 1: when p+x <= m
    // p <= m - x
    // => we can find the largest p such that p <= m-x;
    // largest p = m - (m % x)
    // this gives us the largest multiple of x such that p <= m
    // => the number of valid multiples of x is p/x for p <= m
    // FYI, the count does not include 0x it starts from x, 2x, 3x ... kx

    // sub subCase 2: when p+x > m
    // what is the upper limit of p for p ^ x <= m?
    // Notice that p = x, 2x, 3x ... kx for some p <= m-x, p is an int
    // Observation : if p >= x, p ^ x >= p - x since XOR is subtracton without borrowing
    // since p ^ x <= m,
    // => p - x <= p ^ x <= m
    // => p-x <= m
    // => the smallest value of p^x must be at least p - x
    // => the smallest value of p^x, which is p-x, is <= m
    // Observation : so if p - x > m, then p^x >= p-x > m => p ^ x > m => y > m which is false 
    // therefore no values of p work when p > m + x

    // extra info.
    // if p == x, p ^ x = x ^ x = 0, but 1 <= p ^ x <= m, so p == x is impossible.
    // => p must be > x => p is at least 2x

    // we know all values from p <= m - x and p > m + x
    // what about (m-x, m+x] ? 
    // we still haven't solved for p + x > m
    // Observation : (m-x, m+x] can have at most 2 valid value after p
    // since we computed p = largest multiple of x such that p <= m-x
    // if p == m-x, we can have 2 valid values, ie. m-x+x = m and m+x.
    // Note that we calculated subCase 1 with p <= m - x
    // which means p can be == m - x
    // if p == m - x, there will be 2 more values if 1 <= p ^ x <= m
    // so p += x, and we check the condition 1 <= p^x <= m
    // if valid, then take it
    // repeat again, if valid then take it.
    // if m-2x < p < m-x, then there can be at most 2 more values if the 
    // condition 1 <= p^x <=m is true 
    // so we can just manually check the 2 values


    int x; ll m; cin >> x >> m;

    // divisible by x
    ll p = m - m % x; // largest multiple of x such that p <= m
    // p could include a value in (m-x, m+x]
    // we want to consider that separately
    // how do we know when it is the case?
    // we know p <= m, if m > x then (m-x, m+x] exists
    // so m must be greater than x for (m-x, m+x] to exist
    // we know right now that p <= m, and m > x
    // p is a multiple of x, so p is at least x.
    // so x <= p <= m
    // if x == p, then p ^ x == y == 0, but 1 <= y <= m
    // so x != p
    // hence p > x, we write it as x < p.
    // if x < p, then we need to exlude it because p will be in (m-x,m+x]
    // and we need to check that separately.
    // hence the external check - (x < p)
    // if m<x, then p == 0 => no multiple of x => (m-x,m+x] does not exist.
    // hence ans = 0 currently.
    ll ans = p / x - (x < p); // get current count up to p<m-x, it adjusts the count 
    // to exclude p if p == m as p == m is checked separately in (m-x, m+x]
    if ((x ^ p) >= 1 and (x ^ p) <= m) ++ans; // if 1<= p^x <= m
    p += x;
    if ((x ^ p) >= 1 and (x ^ p) <= m) ++ans; // if 1<= p^x <= m

    // subCase 2: divisible by y
    // let z = x ^ y, where z = 0, y, 2y, 3y, ... ky
    // from our previous observation, we know that z = x ^ y <= x + y
    // because x ^ y is just addition without carry

    // subCase 1
    // if x < y
    // x ^ y <= x + y < y + y = 2y
    // => x ^ y < 2y
    // so z = x ^ y = 0 || y
    // for x ^ y = y
    // => x = 0 but x >= 1 so its impossible
    // for x ^ y = 0
    // x = y but x < y so its impossible

    // subCase 2
    // if x >= y
    // we can iterate from y = x to y = 1
    // check if z = x ^ y can divide y
    // since 1 <= x <= 10^6 this is viable
    
    for (int y = 1; y <= min(1LL * x, m); y++) {
        ll cur = x ^ y;
        if (cur % y == 0) ++ans;
    }


    // subCase 3: divisible by both 
    // let k = x ^ y
    // => k must be divisible by LCM(x,y)
    // => k >= LCM(x,y)
    // Observation: LCM(x,y) >= max(x,y)
    // Another observation : x ^ y < 2 * max(x,y)
    // proof : since the max of x ^ y is only 2^k bits (remember its addition wihout carry)
    // 2 * max(x,y) is always bigger than x ^ y because its 2^(k+1) bits.
    // so we have max(x,y) <= LCM(x,y) <= x ^ y < 2 * max(x,y)
    // if x != y
    // for k = x ^ y to be divisible by LCM(x,y)
    // x ^ y < 2 * max(x,y)

    // hence only x == y satisfies the condition

    // since we want either y or x and y
    // if x <= m then y can be equal to x
    // so x ^ y will be divisible by y and (x and y) when x == y
    // since x == y satisfies 2 conditions, it is wrong since we 
    // only want to satisfy EITHER x, y or (x and y).
    // so --ans to remove the case for x == y.
    if (x <= m) {
        --ans;
    }

    cout << ans << '\n';

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

