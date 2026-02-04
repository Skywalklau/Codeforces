#include <bits/stdc++.h>
using namespace std;

using str = string;
using ch = char;
using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vstr = vector<str>;
using vpii = vector<pair<int, int>>;
using vpstrstr = vector<pair<str, str>>;
using vpvivi = vector<pair<vector<int>,vector<int>>>;
using vvbb = vector<vector<bool>>;
using vb = vector<bool>;
using vvch = vector<vector<char>>;

#define mset multiset
#define mmap multimap
#define uset unordered_set
#define umap unordered_map
#define umset unordered_multiset
#define ummap unordered_multimap
#define pqpriority_queue

#define all(v) (v).begin(), (v).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define clr(x) x.clear()
#define pb push_back
#define rs resize
#define eb emplace_back
#define mp make_pair
#define F first
#define S second

#define pf push_front
#define pb push_back
#define popf pop_front
#define popb pop_back
#define ft front
#define bk back

#define lb lower_bound
#define ub upper_bound
#define bs binary_search

// Utility Functions
template <typename T>
void printVector(const vector<T>& vec){
    for (const auto& el : vec) cout << el << " ";
    cout << "\n";
}

void precision(int x){
	cout.setf(ios::fixed | ios::showpoint);
	cout.precision(x);
	return;
}

bool is_prime(int x){ // Iterate up to the square root of x
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
ll mod_exp(ll base, ll exp, ll mod){
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Precompute factorials and modular inverses
void precompute_factorials(int n, ll mod){
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = (fact[i - 1] * i) % mod;
    for (int i = 0; i <= n; i++) inv_fact[i] = mod_exp(fact[i], mod - 2, mod);
}

// Calculate nCr % MOD
// to use this just call precompute_factorials
ll nCr(int n, int r, ll mod){
    if (n < r || r < 0) return 0;
    return (((fact[n] * inv_fact[r]) % mod) * inv_fact[n - r]) % mod;
}

ll factorial(int a){
	ll ans = 1;
	for (int i = 2; i <= a; i++) {
		ans *= ll(i);
	}
	return ans;
}
 
ll factorial_by_mod(int a, ll mod){
	ll ans = 1;
	for (int i = 2; i <= a; i++) {
		ans *= ll(i);
		ans %= mod;
	}
	return ans;
}

ll binpow(ll a, int b){
	ll ans = 1;
	while (b) {
		if ((b & 1) == 1) {
			ans *= a;
		}
		b >>= 1;
		a *= a;
	}
	return ans;
}
 
ll binpow_by_mod(ll a, ll b, ll mod){
	ll ans = 1;
	while (b) {
		if ((b & 1) == 1) {
			ans *= a;
			ans %= mod;
		}
		b >>= 1;
		a *= a;
		a %= mod;
	}
	return ans;
}

bool is_square(ll a){
	ll b = ll(sqrt(a));
	return (b * b == a);
}
 
bool is_cube(ll a){
	ll b = ll(cbrt(a));
	return (b * b * b == a);
}
 
int digit_sum(ll a){
	int sum = 0;
	while (a) {
		sum += int(a % 10);
		a /= 10;
	}
	return sum;
}

ll gcd(ll a, ll b){
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;}
 
ll lcm(ll a, ll b){
	return a / gcd(a, b) * b;
}


// Constants
const int MAX = int(1e9 + 5);
const ll MAXL = ll(1e18 + 5);
const ll MOD = ll(1e9 + 7);
const ll MOD2 = ll(998244353);

// To be honest, I thought about how to solve this problem.
// But the solution was completely different from what I imagined. 
// Nontheless, this was an amazing problem that taught me new tricks!
// My idea: 2 pointers, think greedily, when we find a number that is in a bit position
// greater than x, we want to remove that bit since it would be > x if we don't.
// the 2nd pointer will go left and right to see if there is a number that can remove it
// if no return -1.
// this is where I got stuck, because if left or right both exists a number that 
// can remove the bit, which do we take?
// there would be too many combinations at that point.
// cuz it could be left right left ...
// or like right right left...
// it would be too much, I thought of dp, but I wouldn't know how to dp this as well.
// So I got stuck, and couldn't solve this problem.

// Solution:
// The trick to this problem, is to check for all the numbers from 0 to x
// and to see for each number, what is the maximum k segments we can form for each
// But how? By looking bit by bit, and using prefix XOR.
// A very intuitive way of doing this, is to check each bit of x.
// if the bit of x is 1, we set it to 0, and the rest of the bits behind x is all 1.
// so if we are given 1 0 1 0 1 1 0 -> 86
// we will do this in logX time.
// we make 4 masks:
// 0 1 1 1 1 1 1 -> handles x: [0, 63]
// 1 0 0 1 1 1 1 -> handles x: [64, 79]
// 1 0 1 0 0 1 1 -> handles x: [80, 83]
// 1 0 1 0 1 0 1 -> handles x: [84, 85]
// By splitting it like this, we can do it in logX time, ensuring we get all the values
// from 0 to x.
// Before proceeding, did you notice that we did not include 86?
// so we should do x++ to include it, because the inequality is <= x not < x.
// Now, before doing this we first construct the prefix XOR of the whole array.
// then whenever we see that a bit of x is set, we will utilize our prefix XOR
// if you didn't notice, the inequality can be written as:
// pref[0] ^ pref[i] | pref[i] ^ pref[j] | pref[j] ^ pref[k] | ... | pref[x] ^ pref[n]
// what does this tell us?
// since pref[0] is just 0 (because XOR itself is 0)
// this means that pref[i] must be a submask of the current mask that we have.
// similarly, since pref[i] is a submask of our current mask, we want pref[j] to be a 
// submask of the current mask as well => pref[j] is a submask of the current mask
// and this continues all the way until pref[n].
// Essentially, we just need to count how many pref[i] is a submask of the current mask
// because a submask ^ submask == submask of the current mask (cool trick right?)
// There is an edge case to note, pref[n] must be a submask of the current mask (because
// it is stated in the problem that r[k] == n so pref[n] which is the last prefix XOR
// must be a submask of the current mask, otherwise we know we can never form the 
// inequality within this range)

// Time complexity: O(logX * N)
// Space complexity: O(N)


void solve() {
	int n, k, m, x;
    cin >> n >> x;

    vi pref(n+1);
    for(int i=1;i<=n;i++){
        int cur;
        cin>>cur;
        pref[i]=pref[i-1]^cur;
    }
 
    auto getMaxLen=[&](const int mask){
        if((pref[n]&mask)!=pref[n])
            return -1;
        int count = 0;
        for(int i=1;i<=n;i++){
            if((pref[i]&mask)==pref[i]) // if pref[i] is a submask of current mask
                count++;
        }
        return count;
    };
 
    const int logN = 31;
    int ans = -1;
    x++;
    for(int j=logN;j>=0;j--){
        int currentBit = 1<<j;
        if(x&(1<<j)){
            int curOR = (x^currentBit)|(currentBit-1);
            ans=max(ans,getMaxLen(curOR));
        }
    }

    cout << ans << '\n';
    
}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
