#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

// Useful typedefs
typedef long long ll;
typedef pair<int, int> pt;

// Constants
const int INF = int(1e9);
const int N = 3e5 + 10; // Maximum size of input array
const int M = 20;       // Maximum bit position for binary representation

int n, m;       // n = number of elements in array a, m = number of XOR queries
int a[N];       // Input array

// Trie node structure to hold binary representations
struct TrieNode{
    int nxt[2]; // Pointers to next nodes (0 or 1)
    int count;  // Count of elements passing through this node

    TrieNode() {
        nxt[0] = -1;
        nxt[1] = -1;
        count = 0;
    }
};

// Trie to store binary representations of numbers
TrieNode trie[N * M];
int nodeCount = 1;  // To track the next available node index

// Reads input values for n, m, and array a
bool readInput() {
    cin >> n >> m;
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    return true;
}

// Adds the binary representation of a number to the trie
void addToTrie(int nodeIndex, int number, int bitPos){
    if (bitPos < 0){
        trie[nodeIndex].count = 1;
        return;
    }

    int currentBit = (number >> bitPos) & 1;
    
    // If there's no next node for currentBit, create one
    if (trie[nodeIndex].nxt[currentBit] == -1){
        trie[nodeIndex].nxt[currentBit] = nodeCount++;
    }

    // Recursively add the next bit to the trie
    addToTrie(trie[nodeIndex].nxt[currentBit], number, bitPos - 1);

    // Update count of current node based on its children
    trie[nodeIndex].count = 0;
    if (trie[nodeIndex].nxt[0] != -1) {
        trie[nodeIndex].count += trie[trie[nodeIndex].nxt[0]].count;
    }
    if (trie[nodeIndex].nxt[1] != -1) {
        trie[nodeIndex].count += trie[trie[nodeIndex].nxt[1]].count;
    }
}

// Finds the maximum XOR with cumulative XOR using values in the trie
void findMaxXor(int nodeIndex, int cumulativeXor, int bitPos, int &maxXorResult){
    if (nodeIndex == -1) return;

    int currentBit = (cumulativeXor >> bitPos) & 1;
    

    // why only check currentBit instead of both 0 and 1?
    // because 0 ^ 0 = 0, 1 ^ 1 = 0.
    // if currentBit is 1, we want to match it with numbers that have bit = 1 at the current
    // bit position to make 1 ^ 1 = 0
    // if currentBit is 0, we want to match it with number that have bit = 0 at the current
    // bit posistion to make 0 ^ 0 = 0
    // Why check if the child node of the currentBit is = 2^bitPos?
    // if the subtree is completely filled, that means there is no way we can find a gap within
    // this subtree for a MEX
    // Ex. 1xyz..., 1 is the bit we are checking, if all possible combinations of xyz... is filled
    // => trie[childNode with currentBit].count == 2^bitPos.
    // => no possible MEX in this subtree/path => flip the bit to check the other branch ONE LEVEL below
    // maxXorResult = 1axyz
    // Note that if we don't flip the bit when count == 2^k.
    // maxXorResult = 1111... since we are going in a subtree that is completely filled already.
    
    if (trie[trie[nodeIndex].nxt[currentBit]].count == (1 << bitPos)){
        maxXorResult |= (1 << bitPos);
        currentBit = 1 - currentBit;
    }

    // Move to the next bit
    findMaxXor(trie[nodeIndex].nxt[currentBit], cumulativeXor, bitPos - 1, maxXorResult);

}

void solve() {
    // Insert all numbers into the trie
    for (int i = 0; i < n; i++) {
        addToTrie(0, a[i], M - 1);
    }

    int cumulativeXor = 0;

    // Process each XOR query
    for (int i = 0; i < m; i++) {
        int query;
        cin >> query;
        
        // Update cumulative XOR with the new query
        cumulativeXor ^= query;
        
        int maxXorResult = 0;
        findMaxXor(0, cumulativeXor, M - 1, maxXorResult);
        
        cout << maxXorResult << endl;
    }
}

int main() {
    readInput();
    solve();

    return 0;
}
