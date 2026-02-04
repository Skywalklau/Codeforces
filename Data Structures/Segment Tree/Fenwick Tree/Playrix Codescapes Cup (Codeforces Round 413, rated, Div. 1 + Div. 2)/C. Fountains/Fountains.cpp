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
using vld= vector<ld>;
using vvdl = vector<vector<ld>>;
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
#define rv reverse
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

const int N = 1e6 + 5; // change according to your needs
vi mn(N, 0); // Smallest prime factor of each number
vvi fcv(N); // Prime factorization for each number (only returns each distinct factor once)


void precompute_prime_factors() { // Modified Sieve
    mn[1] = 1; // Base case: 1 has no prime factors
    for (int i = 2; i < N; i++) {
        if (!mn[i]) { // If i has no prime factor recorded yet, it is a prime number.
            for (int j = 1; j * i < N; ++j) {
                if (!mn[i * j])
                    mn[i * j] = i; // Mark i as the smallest prime factor for all multiples of i.
            }
        }
    }

    // Generate prime factor lists for every number up to N
    for (int i = 1; i < N; i++) {
        int u = i;
        while (u != 1) {
            int v = mn[u]; // Smallest prime factor of u
            fcv[i].push_back(v); // Add it to the factorization of i
            while (u % v == 0) u /= v; // Remove all occurrences of v from u, we only
            // want to add it once since we want DISTINCT prime factors
        }
    }
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

const int LOGN = 20; // sparse table
const int MAXN = 1e5+5; // fenwick

// Introduction to fenwick max queries
// Instead of the typical how many numbers <= a[i]
// this one is out of all the numbers so far, which is the maximum
// at a particular cost.
// Since this was my first time being exposed to maximum fenwick,
// I did not manage to come up with this idea myself,
// but then when I got a hint from a solution
// I managed to implement it myself from just knowing that we can do 
// something like this, bravo!

// The key to solving this problem is to understand that there are only
// 3 states, CC, DD, or CD/DC.
// so we can just use fenwick tree to solve this problem on the fly
// every fountain we get, we pick it, then we compare up to this fountain
// so far, what is the maximum beauty fountain I can pick including this
// fountain.
// If I pick a C fountain, I can either pick a C fountain again or pick a
// D fountain.
// then from these 2 fountains I choose the maximum beauty from the 2
// and compare this value + beauty of this current fountain with my 
// maximum ans so far.
// We keep repeating, and updating on the fly...

int fenC[MAXN], fenD[MAXN]; // actually its MAXP because the idx is cost

void update(int i, int val, int n, int fen[]){
    while (i <= n){
        fen[i] = max(fen[i], val);
        i += i & -i;
    }
}

int query(int i, int fen[]){
    int ans = 0;
    while (i > 0){
        ans = max(ans, fen[i]);
        i -= i & -i;
    }
    return ans;
}

void solve() {
	int n, k, m, c, d;
    cin >> n >> c >> d;

    int ans = 0;
    for (int i=0; i<n; i++){
        int bi, pi;
        ch z;
        cin >> bi >> pi >> z;
        
        if (z == 'C'){
            if (c < pi) continue;
            // I pick this C fountain, so my leftover money for c is c-pi
            int val = max(query(d, fenD), query(c-pi, fenC));
            // val == 0 => we can only buy this ith fountain so far...
            // val != 0 => we have at least 2 items that are possible to buy
            if (val != 0) ans = max(ans, val+bi); 
            update(pi, bi, MAXN, fenC);
        }
        else{
            if (d < pi) continue;
            // I pick this D fountain, so my leftover money for d is d-pi
            int val = max(query(d-pi, fenD), query(c, fenC));
            // val == 0 => we can only buy this ith fountain so far...
            // val != 0 => we have at least 2 items that are possible to buy
            if (val != 0) ans = max(ans, val+bi); 
            update(pi, bi, MAXN, fenD);
        }
    }

    cout << ans << '\n';

}

int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    // int t;
    // cin >> t;
    // while (t--) solve();
    solve();
    return 0;
}

// #include<bits/stdc++.h>
// #define N 100010
// using namespace std;
// int C[N],D[N],n,c,d,ans=0,b,p,ret;
// char s[5];
// void add(int C[],int x,int d){for(;x<=100000;x+=x&-x)C[x]=max(C[x],d);}
// int query(int C[],int x){int y=-1e9;for(;x;x-=x&-x)y=max(y,C[x]);return y;}
// int main()
// {
// 	scanf("%d%d%d",&n,&c,&d);
// 	memset(C,128,sizeof(C));
// 	memset(D,128,sizeof(D));
// 	for (int i=0;i<n;i++){
// 		scanf("%d%d%s",&b,&p,s);
// 		if (s[0]=='C'){
// 			if(p>c)continue;
// 			ret=max(query(C,c-p),query(D,d));
// 			add(C,p,b);
// 		}else{
// 			if(p>d)continue;
// 			ret=max(query(C,c),query(D,d-p));
// 			add(D,p,b);
// 		}
// 		ans=max(ans,ret+b);
// 	}
// 	printf("%d",ans);
// }