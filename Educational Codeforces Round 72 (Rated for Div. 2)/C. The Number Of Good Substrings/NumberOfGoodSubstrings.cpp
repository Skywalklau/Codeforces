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
    string s;
    cin >> s;
    int n = sz(s);

    // new trick learned
    // we can precompute a next array to store the latest 1's appearing at the current index 
    vector<int> next(n + 1, -1);
    for (int i=0; i<n; i++){
        if (s[i] == '1') next[i] = i;
        else next[i] = (i == 0 ? -1 : next[i-1]);
    }

    // Note that the condition asks us to find all f(l,r) == r-l+1
    // there could be the case where f(l,r) > r-l+1, but that does not mean its invalid yet
    // note that we could increase the length of the substring without changing 
    // the value of f(l,r)
    // How? Basically we need to find some nl (if it exists) such that f(nl,r) == f(l,r) AND 
    // f(nl, r) == r-nl+1 => f(l,r) == r-nl+1.
    // Question, when does f(l,r) == r-nl+1 turn true?
    // when nl contains leading zeros. Why? Because 0 does not contribute to the decimal
    // representation of f(nl,r).
    // 000001 is the same as 01.
    // Knowing this property, we can find the largest range of leading 0's for any 
    // substring such that their length, r-nl+1, is maximized.
    // and we can use this maximum length r-nl+1 to check if f(l,r) can "fit" within
    // r-nl+1.
    // lets say f(l,r) == 3 and r-nl+1 == 7 (0000011) 
    // notice that f(nl,r) == f(l,r) == 3, its just that nl to r has a bunch more leading
    // 0's 
    // hence we know that if f(l,r) <= r-nl+1, we can "fit" f(l,r) into r-nl+1
    // But the question now is, how do we find r-nl+1?
    // this is where next array comes in.
    // r-nl+1 = r - (next[l-1]+1) + 1 = r - next[l-1], where nl == next[l-1] + 1
    // Why is nl == next[l-1] + 1?
    // Recall that next[i] is the newest index such that 1 is present in s.
    // so by precomputing the lastest positions of 1's in the next array,
    // we can immediately find the largest r-nl+1 such that we can compare with f(l,r)
    // why +1? Because we do not want to include the current 1 (remember that we only want
    // leading 0's)
    // if we do not add 1 to our next[l-1], we would be including 1, so instead of
    // 0000011 it would be 10000011, which is obviously wrong because 1 contribute to f(nl,r)
    // which makes f(nl,r) > f(l,r), but we want f(nl,r) == f(l,r).

    int result = 0;
    for (int r=0; r<n; r++){
        int sum = 0;
        // Notice that, we only need to loop up to 18 bits
        // Why? Because max(|s|) is 2 * 10^5, meaning the max r-l+1 is 2 * 10^5 only.
        // so if we even want a chance for f(l,r) == r-nl+1
        // then f(l,r) must be < 2 * 10^5 for a chance for f(l,r) <= r-nl+1
        // 2^18 > 2*10^5
        // 18 bits is enough to check whether we have a chance for f(l,r) == r-nl+1 
        // This is necessary as this observation allows us to run in O(N) instead of
        // O(N^2)
        for (int l=r; l >= 0 && r-l<18; l--){
            // this check is necessary because of optimization and to precent duplicate counting.
            // 0110 is the same as 110
            // f(0110) == f(110), but 0110 is longer than 110
            // think greedily, obviously if we can find a valid r-nl+1 for 110
            // then it satisfies 0110 already, in fact it avoids duplicate counting
            // because f(0110) == f(110)
            // also, it is obviously more optimal to use 110 because it is smaller in length
            // making it easier to "fit" in the maximum r-nl+1 we found.
            if (s[l] == '0') continue;
            sum += (1 << (r-l)); // get f(l,r)
            if (sum <= r - (l==0 ? -1 : next[l-1])){ // check if f(l,r) <= maximum r-nl+1
                result++;
            }
        }
    }

    cout << result << '\n';
    // Time complexity : O(18 * N) which is O(N)
    // Space complexity : O(N)

}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}