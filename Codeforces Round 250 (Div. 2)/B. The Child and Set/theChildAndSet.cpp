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

void solve() {
    int sum, limit;
    cin >> sum >> limit;

    vector<pair<int, int>> nums; // {lowbit, number}
    for (int i = 1; i <= limit; ++i){
        nums.pb({i & -i, i});
    }

    // Sort by lowbit in descending order
    sort(all(nums), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.F > b.F;
    });

    vi result;
    for (const auto& p : nums){
        if (sum >= p.F){
            result.pb(p.S);
            sum -= p.F;
        }
        if (sum == 0) break;
    }

    if (sum != 0) {
        cout << "-1\n";
    } else {
        cout << sz(result) << "\n";
        printVector(result);
    }
}

int main() {
    fast_io();
    solve();
    return 0;
}
