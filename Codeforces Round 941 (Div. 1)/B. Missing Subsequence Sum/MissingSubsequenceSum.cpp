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
    int n, k;
    cin >> n >> k;

    // Let i be the largest integer such that 2^i<=k. We will use this array (of size 22):
    // a=[k−2^i,k+1,k+1+2^i,1,2,4,...2^(i−1),2^(i+1),...2^19] is the answer
    // to prove that no subsequence adds up to k
    // notice that the subseq. of a [k−2^i,1,2,4,...2^i−1] sums up to k-1
    // therefore it will not sum to k
    // To prove that for all 1≤v≤n where v≠k, there is a subsequence adding up to v,
    // we consider several cases:

    // v < 2^i
    // this is trivial, as the subseq. [1,2,4,...2^i-1] guarantees it v to be a sum up to 2^i-1


    // 2^i<=v<k
    // we have [k−2^i,1,2,4,...2^i−1]
    // notice that k-1 is the maximum sum for v in this case
    // all we need to do now is to remove a sum from k-1 for 2^i<=v<k
    // so it will be k-1-v for some v in [k−2^i,1,2,4,...2^i−1]
    // we know we have all the numbers from 1 to 2^i-1 from the v < 2^i case
    // which means the biggest value of v so far is 2^i-1
    // hence for the biggest value of v so far, k-1-v = k-1-(2^i-1) = k-2^i
    // Also, notice that 2^i<=k<2^(i+1).
    // so this means k is at most 2^(i+1)-1
    // hence we can write k-2^i = 2^(i+1)-1 - 2^i = 2(2^i)-1 - 2^i = 2^i-1
    // since after taking the most extreme boundaries, k-1-v = 2^i-1 < 2^i
    // => k-1-v < 2^i
    // => there is always going a binary representation for k-1-v in [k−2^i,1,2,4,...2^(i−1)]
    // from 1 to k-1, hence 2^i<=v<k is guaranteed


    // v > k
    // If v>k, we can take k+1 along with the binary representation of v−k−1. 
    // The one edge case is when the 2^i bit is set in v−k−1. In this case, we replace k+1
    // with k+1+2^i
    // this way we can handle both cases with and without 2^i in the remainder v-k-1.

    int i=0;
    while ((1 << (i+1)) <= k){
        i++;
    }

    vector<int> ans = {k - (1 << i), k + 1, k + 1 + (1 << i)};

    for (int j=0; j<20; j++){
        if (j != i) ans.pb(1 << j);
    }

    cout << sz(ans) << '\n';
    printVector(ans);

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

