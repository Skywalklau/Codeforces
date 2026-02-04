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

    int i=0;

    // The editorial for this problem is too complex, i will come up with my own way of explaining
    // This is actually just a subset problem, where we just need to find 2  unqiue
    // subsets that have the same sum, if there it exists, we can just return YES
    
    // Here is the proof
    // suppose you have an array a = [-2, 2, 7, 12, 4, 3, 1, 100, 20] of 9 elements
    // Notice that the subsets [7] and [4,3] have the same sum
    // to prove that the other array b will have the same number of elements (9 in this case)
    // we can always make the first element in b to be 0 and bring the other values
    // that are not included in either of the 2 subsets into b
    // in this case, b will be [0,-2,2,12,1,100,20]
    // notice that with 0, we can form all the numbers in a for -2, 2, 12, 1, 100 and 20.
    // currently b has 6+1 = 7 elements, with an extra 0
    // Now, notice that if we take the prefix sums of the 2 subsets
    // [7] = [7]
    // [4,3] = [4, 7]
    // we can actually just cross away the last element in one of the prefix sums
    // and take the rest of the elements in both arrays and append it to a
    // In this case, 7 is removed in either [7] or [4, 7]
    // so what we are left is just 4 and 7, and they are added to a to make
    // a = [0,-2,2,12,1,100,20,4,7], which has 9 elements
    // Notice that now we have 4 and 7, we still have 3 to form from b
    // realise that 7 - 4 = 3. So now we fully formed an array.
    // This is just an example, it work for all cases where n is small (<32).

    int a[n];

    for (int i=0; i<n; i++){
        cin >> a[i];
    }

    map<int,int> graph;
    for (int mask=0; mask<(1<<n); mask++){ 
        int sum = 0;
        for (int j=0; j<n; j++){
            if (mask & (1 << j)) sum += a[j]; 
        }
        graph[sum]++;        
    }

    for (auto &x : graph){
        if (x.S > 1){
            cout << "YES" << '\n';
            return;
        }
    }

    cout << "NO" << '\n';

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

