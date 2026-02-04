#include <bits/stdc++.h>
using namespace std;

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
 
bool canMake(ll x, ll cb, ll cs, ll cc, ll nb, ll ns, ll nc, ll pbu, ll ps, ll pc, ll r) {
    ll cost = max(0LL, cb * x - nb) * pbu
            + max(0LL, cs * x - ns) * ps
            + max(0LL, cc * x - nc) * pc;

    return cost <= r;
}

void solve() {
    string recipe;
    cin >> recipe;

    ll nb, ns, nc;
    cin >> nb >> ns >> nc;

    ll pbu, ps, pc;
    cin >> pbu >> ps >> pc;

    ll r;
    cin >> r;

    ll cb = 0, cs = 0, cc = 0;

    for (ch& x : recipe){
        if (x == 'B') cb++;
        else if (x == 'S') cs++;
        else cc++;
    }

    ll low = 0, high = 1e15, ans = 0;
    while (low <= high){
        ll mid = low + (high - low) / 2;
        if (canMake(mid, cb, cs, cc, nb, ns, nc, pbu, ps, pc, r)){
            ans = mid;
            low = mid + 1;
        } 
        else{
            high = mid - 1;
        }
    }

    cout << ans << "\n";
}
 
int main() {
    fast_io();
    solve();
    return 0;
}