#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;
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
const int MOD = 1e9 + 7;
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

// Global Variables
vi arr, subTreeXOR;
vvi adjList;
int x = 0; // XOR sum of the whole tree, very important variable, remember it.
bool isSubTree = false;

// DFS to compute subtree XORs
void dfs1(int curNode, int parentNode) {
    subTreeXOR[curNode] = arr[curNode];

    for (int nextNode : adjList[curNode]) {
        if (nextNode != parentNode) {
            dfs1(nextNode, curNode);
            subTreeXOR[curNode] ^= subTreeXOR[nextNode];
        }
    }
}

// we need to find a way to remove 2 edges resulting in 3 components
// each with the same XOR which is EQUAL to x
// removing an edge (curNode, parent[curNode]) means creating 2 components
// a component with subtree rooted at curNode
// and a 2nd component consisting of root's subtree excluding curNode's subtree
// now to check whether there is a subtree in this new tree
// with a XOR == x
// Therefore, there are 2 ways for this to happen

// 1: there is some ANCESTOR of curNode with subtree XOR == 0
// 2: there is some other DISJOINT subtree with XOR == x


// Case 1, why subTree[someAncestorNode] == 0?
// Since curNode lies in the tree of the AncestorNode
// and subTree[curNode] == x
// the XOR of subTree[someAncestorNode] is 
// subTree[someAncestorNode] ^ subTree[curNode]
// because we removed an edge between the curNode subtree
// from the AncestorNode subTree, so we gotta take the difference.
// Notice that, subTree[somAncestorNode] ^ subTree[curNode] == x
// because from the base case, if a tree has XOR of 0, then no matter what
// edge you delete you always end up with 2 components with equal XOR
// Therefore, this implies that subTree[someAncestorNode] == 0
// Which makes sense, because subTree[somAncestorNode] ^ subTree[curNode] = 0 ^ x == x

// Also, 
// Once we find 2 components with x
// We explicitly handled the 3rd component with x
// so we don't have to find the 3rd component.
// Why? Because when we are taking a subTree[someNode]
// we are essentially "cutting off" the branch above it
// resulting in one extra component
// And that extra component, which is the 3rd component, will be x as well
// because x ^ x ^ x = x ie. we found two components with x on left side, and we know
// the XOR of the whole tree is x, so the remaining "unknown" XOR the last component
// MUST be x.
// Case 2, why find some disjoint subtree such that its XOR is x?
// pretty straightforward for this one
// if we can find some disjoint tree with XOR of x, and we already
// have found another subTreeXOR[curNode] == x, then because x ^ x ^ x = x
// we explicitly found another component with XOR of x
// because we "cut off" the branch above that disjoint subtree and the
// branch of the curNode. Hence we end up with 3 components with XOR of x
// because x ^ x ^ x = x ie. we found two components with x on left side, and we know
// the XOR of the whole tree is x, so the remaining "unknown" XOR the last component
// MUST be x.

bool dfs2(int curNode, int parentNode, bool isThereAncestor) {
    if (isThereAncestor && subTreeXOR[curNode] == x) return true; // Ancestor case
    if (isSubTree && subTreeXOR[curNode] == x) return true;       // Disjoint subtree case

    // Update ancestor flag
    if (subTreeXOR[curNode] == 0) isThereAncestor = true;

    for (int nextNode : adjList[curNode]) {
        if (nextNode != parentNode) {
            if (dfs2(nextNode, curNode, isThereAncestor)) return true;
        }
    }

    // update disjoint flag later only after we dfs all the children of a subtree
    // Why? Because its dfs, and dfs goes all the way to the bottom first
    // Let's make it simple,
    //    1
    //  2   3
    // if we dfs, we go to 2 and 3 (the deepest layer in the tree)
    // 2 is a disjoint tree to 3, 3 is a disjoint tree to 2
    // notice how we can only achieve this after reaching the deepest level

    // Another example,
    //         1
    //      2     3
    //    4   5  6  7
    // via dfs, we go start at the deepest level (4 5 6 7)
    // guess what? They are all disjoint to each other.
    // ok, next level after first dfs, go to (2, 3)
    // guess what? They are all disjoint to each other.
    // So this is why we to this line at the very end
    if (subTreeXOR[curNode] == x) isSubTree = true;

    return false;
}

void solve() {
    // Input
    int n, k;
    cin >> n >> k;

    arr = vi(n);
    adjList = vvi(n);
    subTreeXOR = vi(n);
    x = 0; // XOR SUM of the whole tree, remember this variable, very important.
    isSubTree = false; // global variable, as soon as we find a disjoint set, we can return true

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        x ^= arr[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int node1, node2;
        cin >> node1 >> node2;
        --node1, --node2; // Convert to 0-based indexing
        adjList[node1].pb(node2);
        adjList[node2].pb(node1);
    }

    // Special case, but also a very important case.
    if (x == 0){
        // we can remove any 1 edge resulting in 2 components
        // with equal XOR
        cout << "YES" << endl;
        return;
    }

    if (k == 2){ // impossible to remove only 1 edge
        // Why? Because x != x ^ x
        // However, x = x ^ x ^ x
        // So we must find 3 components => delete 2 edges
        cout << "NO" << endl;
        return;
    }

    // FYI, there is no need to have more than 3 components,
    // Because lets say you have 4 components,
    // if they all have x, then you can just combine 3 of them to make 1 component,
    // so total 2 components is enough
    // if you have 5 components of x, then you can just combine 3 of them to make 1 component,
    // so total 3 components.
    // if you have 6 components of x, go back to 4 components, then 2 components.
    // if you have 7 components of x, go back to 5 components, then 3 components.
    // Therefore, you always end up with 2/3 components.
    // => deleting 1 or 2 edges.
    // But, if you only delete one edge and the 2 components have equal XOR
    // then you end up getting y ^ y = 0
    // notice that y ^ y == x.
    // The only case where y ^ y == x is when x == 0, which is the special case.
    // Otherwise, it is always impossible to make 2 components of equal XOR such that it is equal to x

    // Compute subtree XORs
    dfs1(0, -1);
    if (dfs2(0, -1, false)) cout << "YES" << endl;
    else cout << "NO" << endl;
}

// Main Function
int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
