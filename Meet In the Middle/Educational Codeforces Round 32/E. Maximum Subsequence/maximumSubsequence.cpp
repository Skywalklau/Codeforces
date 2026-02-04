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

void getSums(vll& nums, int start, int end, vll& sums, int m){
        int n = end - start;
        for (int mask = 0; mask < (1 << n); ++mask){
            ll sum = 0;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) sum += nums[start + i];
            }
            sums.push_back(sum % m);
        }
}

void solve() {
    int n, m;
    cin >> n >> m;

    vll a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vll leftSums;
    vll rightSums;

    getSums(a, 0, n / 2, leftSums, m);
    getSums(a, n / 2, n, rightSums, m);   

    sort(all(rightSums));

    ll result = 0;

    for (ll sum : leftSums){
            ll remaining = m - 1 - sum;

            auto it = lower_bound(all(rightSums), remaining);

            if (it != rightSums.end()) {
                result = max(result, (sum + *it) % m);
            }
            if (it != rightSums.begin()) {
                result = max(result, (sum + *(it - 1)) % m);
            }
    }

    cout << result << endl;
    
}

int main() {
    fast_io();
    solve();
    return 0;
}
