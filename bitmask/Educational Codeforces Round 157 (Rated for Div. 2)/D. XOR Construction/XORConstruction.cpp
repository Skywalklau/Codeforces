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
const int MAX_BITS = 20;

// Fast Input/Output
void fast_io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

// Trie node structure
struct TrieNode {
    int nxt[2]; // Children for bit 0 and bit 1

    TrieNode() {
        nxt[0] = -1;
        nxt[1] = -1;
    }
};

vector<TrieNode> trie(1); // Trie initialization with root node

void addToTrie(int nodeIndex, int number, int bitPos) {
    if (bitPos < 0) {
        return;
    }

    int currentBit = (number >> bitPos) & 1;

    // If there's no next node for currentBit, create one
    if (trie[nodeIndex].nxt[currentBit] == -1) {
        trie[nodeIndex].nxt[currentBit] = sz(trie);
        trie.pb(TrieNode());
    }

    // Recursively add the next bit to the trie
    addToTrie(trie[nodeIndex].nxt[currentBit], number, bitPos - 1);
}

int dfs(int nodeIndex, int x, int bitPos) {
    if (nodeIndex == -1) return x;

    int currentBit = (x >> bitPos) & 1;
    
    // Try to flip the bit to maximize XOR
    // currentBit == 0 then we want 1 cuz 0^1 = 1
    // curretBit == 1 then we want 0 cuz 1^0 = 1
    if (trie[nodeIndex].nxt[currentBit ^ 1] != -1) {
        currentBit ^= 1;
    }

    // XOR x with the currentBit if we can maximize
    // Otherwise we still XOR x with currentBit to make it 0 for this bit
    // Why still XOR eventhough we cannot maximize?
    // let c be an array of numbers.
    // Since x^c means all bits of x XOR with c
    // eventhough we cannot maximize x^c at some current bit
    // we still HAVE to XOR because x^c means XOR all the bits of x and c
    x ^= currentBit << bitPos;

    return dfs(trie[nodeIndex].nxt[currentBit], x, bitPos - 1);
}

void solve() {
    int n;
    cin >> n;

    // we can always set the array as [0, c1, c2, c3..., c(n-1)], with 0 as first element
    // where 0^c1 = a1, c1^c2=a2, c2^c3=a3...
    // if the resultant array [0, c1, c2, c3, ..., c(n-1)] is invalid
    // we can apply an xor of x to the whole array
    // then the array becomes [0^x, c1^x, c2^x, c3^x, ..., c(n-1)^x]
    // if the maximum of this new array is n-1, it means we found the valid array.
    // => this is a trie problem, where we just want to find the valid x such that
    // we can get n-1 as the maximum value.
    // Time Complexity : (N*log(N))

    vi a(n);
    // Read array and create [0, c1, c2, c3..., c(n-1)]
    for (int i = 1; i < n; ++i) {
        cin >> a[i];
        a[i] ^= a[i - 1];
    }

    for (int x : a) {
        addToTrie(0, x, MAX_BITS - 1);
    }

    for (int x = 0; x < n; ++x) {
        if (dfs(0, x, MAX_BITS - 1) == n - 1) {
            for (int i : a) {
                cout << (x ^ i) << " ";
            }
            cout << "\n";
            return;
        }
    }
}

int main() {
    fast_io();
    solve();
    return 0;
}
