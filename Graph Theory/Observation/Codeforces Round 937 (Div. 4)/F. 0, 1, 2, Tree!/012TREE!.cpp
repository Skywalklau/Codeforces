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
const int MOD = 1000000007;
const int INF = 1e9;
const ll LINF = 1e18;

// Utility Functions
template <typename T>
void printVector(const vector<T>& vec) {
    for (const auto& el : vec) cout << el << " ";
    cout << "\n";
}

bool is_prime(int x) { // Iterate up to the square root of x
    for (int i = 2; i * i <= x; i++) { // If x is divisible by i, it's not prime
        if (x % i == 0) return false;
    }
    return true; // If no divisors are found, x is prime
}

// Fast Input/Output
void fast_io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

// Global Variables
vector<ll> fact, inv_fact;

// Function to calculate modular exponentiation
ll mod_exp(ll base, ll exp, ll mod) {
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Precompute factorials and modular inverses
void precompute_factorials(int n, ll mod) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = (fact[i - 1] * i) % mod;
    for (int i = 0; i <= n; i++) inv_fact[i] = mod_exp(fact[i], mod - 2, mod);
}

// Calculate nCr % MOD
ll nCr(int n, int r, ll mod) {
    if (n < r || r < 0) return 0;
    return (((fact[n] * inv_fact[r]) % mod) * inv_fact[n - r]) % mod;
}


void solve() {
    int a, b, c;
    cin >> a >> b >> c;

    // The first question is, how do we know whether we can form a valid tree
    // given the a, b and c nodes?
    // Notice that, the number of a's decide the number of c nodes that can 
    // be placed underneath it.
    // since c nodes cannot have children.
    // and b nodes can only have 1 children.
    // in order for the tree to be filled properly
    // the number of b nodes does not matter because b nodes connect to c 
    // nodes directly, which is just b -> c, this does not expand the tree
    // to increase the available slots to put in a c node 
    // notice that, for each a node, our available slots for c nodes increases
    // by 1, hence the equality a+1 == c must hold for ALL the nodes to be used.

    if (a + 1 != c){
        cout << -1 << '\n';
        return;
    }

    int h = 0;

    // we know its a valid tree.
    // so how should we place the nodes?
    // Greedy, lets fill in all the a's first then b's then c
    // Why? Because the to minimize the height we want to expand the tree
    // as much as possible, so we MUST use node a's to expand as much as 
    // we can in the beginning.
    // then we have to connect with b nodes because using c nodes 
    // just causes a dead end for that path which does not minimize our height.
    
    // So, we know the order of nodes.
    // how do we calculate the height?
    // Simulate it. This is possible, since a + b + c < 10^5 over ALL testcases
    // so we can do this linearly.
    // but actually, doing it logarithmicly is better.
    // but how? Simulate it, with bit manipulation.
    // Notice that, using a nodes, we can form each layer increasingly
    // by 2^n nodes
    //             a      2^0
    //           a   a    2^1
    //         a  a a  a  2^2
    //         ...        2^n
    // so while we have enough a nodes to form a layer
    // we keep doing it until we run out of a nodes.
    // after that, we either have remaning a nodes that cannot form a full layer
    // or 0 a nodes, meaning we used up all the a nodes.
    // if our a == 0, and b == 0 => our height is found, just return h.
    // otherwise, we check whether a + b >= 2^n, where n is the current layer
    // where we could not fill entirely with a nodes.
    // if we can fill with a + b nodes
    // => b -= (2^n - remaining a nodes)
    // => h++
    // go to next layer.
    // if a + b < 2^n
    // => our highest number of nodes available is just the current height + 1.
    // Why? Because now we have to use c nodes to fill that layer
    // and with the current layer having some a and b nodes, we fill the 
    // next layer with c nodes which increases the height by 1.

    // Final: after filling the current layer with a and b nodes if a+b>=2^n
    // we just keep filling the remaining layers with b, and then c
    // and the number of nodes for each layer will be fixed after the nth layer
    // because b does not expand the slots of the tree, nor does c.
    // so knowing this we know the remaining height will just be ceil(b/c).
    // lets call it k.
    // then the total height is h+k.
    // Why ceil(b/c) and not just b/c?
    // because there can be a layer with both b and c nodes => b/c might be
    // a decimal number, but b/c is integer floor division so we neglected it
    // if there is a layer with both b and c nodes,
    // => there is another layer under that b node, hence ceil(b/c) to +1 for 
    // the height.
    // we can do ceil with (b+c-1)/c instead of ceil(b/c).
    // (b+c-1)/c is much better, it prevents overhead for extremely small/large 
    // numbers.
    // conclusion: always use (b+c-1)/c rather than ceil(b/c).

    while (a >= (1 << h)){
        a -= (1<<h);
        h++;
    }

    if (a == 0 && b == 0){
        cout << h << '\n';
        return;
    }

    if (a + b >= (1 << h)){
        b -= (1<<h) - a;
        h++;
    }
    else{
        cout << h+1 << '\n';
        return;
    }

    int k = (b + c - 1) / c;

    cout << h + k << '\n';    

}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
