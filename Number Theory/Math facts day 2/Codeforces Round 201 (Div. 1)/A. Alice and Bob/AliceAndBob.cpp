#include <bits/stdc++.h>
using namespace std;

using ch= char;
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

// solve time ~ can't solve.
// This is such a good problem.
// First, notice that if we took the gcd of the whole set S, we end
// up with a multiple of lets say g.
// then, we can represent each number in S currently in the form a*g for
// some integer a.
// Since we are taking the difference of 2 numbers in S, the result 
// will still be a multiple of g.
// In fact, lets say we have [2g,5g,9g,100g] initially, what does this 
// tell us?
// Since we can take the diff as long as the number is not in S yet,
// in the end we can actually get all numbers from g to 100g.
// So, the number of elements we can add will just be 100g / g - n.
// Or more formally, max(all(a)) / gcd(all(a)) - n.
// So, if the number of numbers we can add is odd, Alice wins.
// Else, Bob wins.

void solve() {
    int n;
    cin >> n;
    vi a(n);
    for (int &x : a) cin >> x;

    int g = a[0];
    for (int i = 1; i < n; ++i) {
        g = gcd(g, a[i]);
    }

    int max_a = *max_element(all(a));

    // no. of turns, not rounds, because 1 round has 2 turns
    int turns = max_a / g - n;

    cout << (turns % 2 == 1 ? "Alice" : "Bob") << "\n";
}

int main() {
    fast_io();
    solve();
    return 0;
}
