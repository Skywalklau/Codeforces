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

    vector<vector<int>> adjList(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // max f will be n-1 if no leaf nodes share the same parent node.
    // otherwise maxRes-- each time we see a leaf node sharing the same parent node.
    // minRes is either 1 || 3
    // 3 if bfs between one leaf node to any leaf node is odd length of edges.
    // else 1
    int maxRes = n-1;
    int minRes = 1;
    vector<int> depth(n, -1);
    queue<int> q;

    
    // Identify leaf nodes
    vector<int> leaves;
    unordered_set<int> parentNode;
    for (int i = 0; i < n; i++) {
        if (sz(adjList[i]) == 1) { // Leaf nodes have only one neighbor
            leaves.push_back(i);
            if (q.empty()){
                q.push(i);
                depth[i] = 0;
            }
            if (parentNode.find(adjList[i][0]) != parentNode.end()) maxRes--;
            else parentNode.insert(adjList[i][0]);
        }
    }

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int neighbor : adjList[cur]) {
            if (depth[neighbor] == -1) { // Not visited
                depth[neighbor] = depth[cur] + 1;
                q.push(neighbor);
            }
        }
    }

    for (int leaf : leaves) {
        if (depth[leaf] % 2 == 1) {
            minRes = 3; // Odd-length leaf-to-leaf path found
            break;
        }
    }

    cout << minRes << " " << maxRes << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}

