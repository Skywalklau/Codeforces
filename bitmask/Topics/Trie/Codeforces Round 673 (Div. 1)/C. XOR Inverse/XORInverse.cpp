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
const int LOG = 30; // Max bits for the problem (29 bits for inputs up to 10^9)
 
 
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
 
// Trie node structure
struct TrieNode {
    int nxt[2]; // Children for bit 0 and bit 1
    vi indices; // List of indices of elements passing through this node
 
    TrieNode() {
        nxt[0] = -1;
        nxt[1] = -1;
    }
};
 
vector<TrieNode> trie(1); // Trie initialization with root node
ll dp[2][30];


// Function to add a number into the trie
void addToTrie(int nodeIndex, int number, int index, int bitPos) {
    if (bitPos < 0) {
        trie[nodeIndex].indices.pb(index);
        return;
    }
 
    int currentBit = (number >> bitPos) & 1;
 
    // If there's no next node for currentBit, create one
    if (trie[nodeIndex].nxt[currentBit] == -1) {
        trie[nodeIndex].nxt[currentBit] = sz(trie);
        trie.pb(TrieNode());
    }
 
    // Recursively add the next bit to the trie
    addToTrie(trie[nodeIndex].nxt[currentBit], number, index, bitPos - 1);
    trie[nodeIndex].indices.pb(index); // Add index to current node
}
 
// Recursive function to calculate inversions
void calculateInversions(int nodeIndex, int bitPos) {
    if (nodeIndex == -1 || bitPos < 0) return;
 
    int left = trie[nodeIndex].nxt[0];
    int right = trie[nodeIndex].nxt[1];
    
    // Notice that, the trie indirectly "sorts" our numbers if we traverse it 
    // from leftmost to rightmost.
    // we can go down all the way to the leftmost side of our trie.
    // from there, compare the right side with left side at the bottom level
    // which will just be 2 nodes at first or none if either left or right doesnt exist.
    // we can then use 2 pointers to find from the left side of numbers
    // at that bit level, if the right side of numbers have indexes smaller than our 
    // current number in the left side.
    // Note that I am doing 0 inversion first, which is basically assuming the ith bit
    // of x is currently 0
    // then the 1 inversion is when the ith bit of x is 1, so we need to find the 
    // opposite of the total 1 inversions at this bit, which is left * right - zero inversions
    // the one that is smaller is desired, since its what the question wants.
    // repeat the same process for each component in the same level.
    // then compare the entirety of the level to see whether 0 or 1 inversion is better.
    // once done then go up one level, combining previous children to the parent.
    // repeat the same process until we reach the root node.
    // by maintaining the minimum each level, we guarantee x to be minimum, and inversions
    // to be minimal (it's just dp)
    
    if (left != -1) calculateInversions(left, bitPos - 1);
    if (right != -1) calculateInversions(right, bitPos - 1);
 
    if (left == -1 || right == -1) return;
 
    ll leftCount = sz(trie[left].indices);
    ll rightCount = sz(trie[right].indices);
 
    // Count inversions between the left and right child nodes
    ll crossInversions = 0;
    int ptr = 0;
    for (int x : trie[left].indices){
        while (ptr < sz(trie[right].indices) && trie[right].indices[ptr] < x){
            ptr++;
        }
        crossInversions += ptr;
    }
 
    // printVector(trie[left].indices);
    // printVector(trie[right].indices);
    
    // Add to the DP-like inversion counts
    ll zeroInversions = crossInversions; // without setting the ith bit of x to 1 yet
    ll oneInversions = leftCount * rightCount - crossInversions; // after setting ith bit of x to 1

    // cout << zeroInversions << endl;
    // cout << oneInversions << endl;
    // we need to consider the whole level, thus we need to use dp to store it.
    // I initially thought that we just need to compare one branch, which now 
    // that I think about it made no sense.
    // It is obvious that we should consider the whole level at that bit, not just
    // one small part of a level.
    dp[0][bitPos] += zeroInversions;
	dp[1][bitPos] += oneInversions;
}

void solve() {
    int n;
    cin >> n;
 
    vi a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
        addToTrie(0, a[i], i, LOG); // Insert numbers into the trie
    }
 
 
    ll inversions = 0, result = 0;
    calculateInversions(0, LOG);
 
    for(int i=0; i<LOG; i++){
        // compare the whole level, is 0 or 1 inversion better?
		if(dp[1][i] < dp[0][i]){ // 1 is better
            result += (1 << i);
            inversions += dp[1][i];
        }
        else inversions += dp[0][i]; // 0 is better
	}

    cout << inversions << " " << result << "\n";
}
 
int main() {
    fast_io();
    solve();
    return 0;
}