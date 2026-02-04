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
using vpll = vector<pair<long long, long long>>;
using vvpii = vector<vector<pair<int, int>>>;
using vpstrstr = vector<pair<str, str>>;
using vpvivi = vector<pair<vector<int>,vector<int>>>;
using vvb = vector<vector<bool>>;
using vb = vector<bool>;
using vch = vector<char>;
using vvch = vector<vector<char>>;
using vvstr = vector<vector<str>>;
using vd = vector<double>;

#define mset multiset
#define mmap multimap
#define uset unordered_set
#define umap unordered_map
#define umset unordered_multiset
#define ummap unordered_multimap
#define pq priority_queue

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
#define mxe max_element
#define mne min_element

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
    if (x == 1) return false;
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

const ll K = 6e6+5; // change according to your needs
vll mn(K, 0); // Smallest prime factor of each number
vvll fcv(K); // Prime factorization for each number (only returns each distinct factor once)


void precompute_prime_factors() { // Modified Sieve
    mn[1] = 1; // Base case: 1 has no prime factors
    for (ll i = 2; i < K; i++) {
        if (!mn[i]) { // If i has no prime factor recorded yet, it is a prime number.
            for (ll j = 1; j * i < K; ++j) {
                if (!mn[i * j])
                    mn[i * j] = i; // Mark i as the smallest prime factor for all multiples of i.
            }
        }
    }

    // Generate prime factor lists for every number up to N
    for (int i = 1; i < K; i++) {
        int u = i;
        while (u != 1) {
            int v = mn[u]; // Smallest prime factor of u
            fcv[i].push_back(v); // Add it to the factorization of i
            while (u % v == 0) u /= v; // Remove all occurrences of v from u, we only
            // want to add it once since we want DISTINCT prime factors
        }
    }
}

void sieve() {
    mn[1] = 1; // 1 is not prime
    for (ll i = 2; i < K; i++) {
        if (mn[i] == 0) { // i is prime
            mn[i] = i;
            for (ll j = i * i; j < K; j += i) {
                if (mn[j] == 0) {
                    mn[j] = i; // smallest prime factor of j
                }
            }
        }
    }
}

vi get_primes_up_to_K() {
    vi primes;
    for (ll i = 2; i < K; i++) {
        if (mn[i] == i) primes.pb(i);
    }
    return primes;
}

// get all factors up to n
vvi factors(K);

void getAllFactors(){
    for (int i = 1; i <= K; i++) {
        for (int j = i; j <= K; j += i) {
            factors[j].push_back(i); // i is a divisor of j
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

// Calculate nCr
// don't need to call precompute_factorials for this.
ll nCr_no_mod(int n, int r){
    if (r < 0 || r > n) return 0;
    ll res = 1;
    for (int i=1; i<=r; i++){
        res *= (n - i + 1);
        res /= i;
    }
    return res;
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

const int LOGN = 20; // sparse table interval
const int MAXN = 6e5+5; // fenwick = N, trie  = N * number of bits

// solve time ~ can't solve.
// This was such a good problem. Actually took me 3 hrs to understand.
// But it was worth it.
// Apparently this is a standard problem that you can find in 
// cses and Geeks for Geeks?
// Tbh, I can kinda see why, looks quite standard.
// Anyways, now I know how to solve this problem.
// We need to make some observations.
// We can solve this through grouping numbers in terms of digit cnt.
// Eg. 1-9, 10-99, 100-999, ...
// Why? Because observe that in each group, the digit cnt increase by 1
// and the number of numbers in the group increases by 10 times.
// Eg. 1-9 has 9 numbers, each of 1 digit.
// 10-99 has 90 numbers, each of 2 digits.
// 100-999 has 900 numbers, each of 3 digits.
// So, we can scale it like this and keep minusing this from k to find
// how many digits this number in which k belongs to.
// I noticed this as well, and I had the idea to do this.
// Now, the tricky part, eventually, we will end up some num_digits 
// and numbers_in_block (some 9*10^i).
// So, we know our last number will be of size num_digits.
// How do we know what the last number is?
// the answer is:
// number = numbers_in_block / 9 + (k - 1) / num_digits;
// Why? 
// numbers_in_block / 9 is used to repsent the size of our number
// starting at 10^i for some i.
// then since we know we have k digits left (after constantly subtracting
// the increasing groups of digits), we can find the actual number
// just by dividing k-1 with num_digits to get the padding to add
// to form the actual number.
// Eg. We are in groups of 2 digits, ie. 10-99.
// we have k=5 left.
// so our number will be 10 + (5-1)/2 = 12.
// We need to do k-1 instead of k because of 0 indexing (our numbers
// start from 0 not 1), we counted 1-9 instead of 0-9. 
// Great, now we got the actual number.
// 2nd observation: k can end at some point in this number.
// So, we need to find the actual index of this number where our sum
// ends.
// Eg. our final number could be 3217413, but we only sum until 321.
// To figure out the index to stop, we can simply do:
// int prefix_length = (k - 1) % num_digits + 1;
// this is the final index we should exclude
// k-1 is because again, we counted from 1 but we should count from 0.
// the +1 is just for me so that we can loop < prefix_length instead
// of <= prefix_length.
// But essentially (k - 1) % num_digits gives the final point (inclusive)
// that we should loop until in our final number.
// NOTE:
// if we counted from 0 instead of 1 then no need -1 from k.


// Ok, so now we got the idx of the final number to sum to. 
// Now, we can just for loop the number up until that index and get 
// the digit sum.

// Now for the most interesting part that took me 10000 yrs to understand.
// We know our final number is some x. Now, we wanna sum all the digits
// from 0 to x-1.
// So, how do we solve this?
// The idea is combinatorics + prefix sums. Super genius solution I tell u.
// The trick to solving this, is to split the sum into 2 parts.
// Lemme explain the idea.
// Ok, we know our final number is x, lets say x = 52854567
// Then, for each digit of this number x, we can find the contribution of
// numbers < x.
// We fix the prefix of x.
// lets say, our current digit is 8 (3rd digit from the left)
// Then, we can fix the prefix, which is 52.
// Then for this first part of the sum, we find all the sum of digits
// for numbers < 528xxxx
// Namely, we will find the contribution of each prefix digit on the left
// which is:
// 527xxxx
// 526xxxx
// 525xxxx
// ...
// 520xxxx
// Also, we will find the contribution of each digit on the suffix of  
// 527xxxx
// 526xxxx
// 525xxxx
// ...
// 520xxxx
// This is why we need to split into 2 parts for the sum.
// 1st part: prefix sum of digits up to the ith digit.
// How do we calculate the sum of prefix digits up to this ith digit?
// Its actually quite simple, its just combinatorics.
// First of all, our prefix is fixed as 52ixxxx, i is our current digit
// we are on right now.
// Now, what can i be? In this case, i is 8, so that means we can put
// all the numbers i=0 to 7, so there are exactly i numbers in total for
// this ith position that we can put to be < x.
// And for each of these digit at this ith position, our prefix sum of
// digit is 5 + 2 = 7, because our prefix of x so far is 52.
// hence, what is the contribution so far?
// Since we can put from i=0 to 7, the summation of this is just
// i * (i-1)/2, which is 0+1+2...+7.
// Hence, the contribution of prefix sums available up to this ith point
// is (prefix sum of digit up to i-1)*current_digit + (current_digit*(current_digit-1))/2.
// Now, since we have xxxx space remaining, or 4 spaces remaining, each
// of these numbers can be anything between 0 to 9, so there are exactly
// 10^4 ways we can assign a digit to xxxx in each x slot.
// Hence, the total left contribution is just:
// (prefix_sum * current_digit + (current_digit * (current_digit - 1)) / 2) * pow(10, remaining_digits - 1);
// Now, for the 2nd part of the sum, our goal is to find the contribution
// of the suffix of this current number 528xxxx
// Namely, its the sum of the contribution of xxxx.
// So, how do we solve this part?
// Well, again its combinatorics.
// Note that each x slot can be any number from 0 to 9.
// So, what is the contribution?
// Notice that for each slot, I can fix an x to some digit 0 to 9.
// say I do 1xxx
// then, what can xxx be? Its 10^3 obviously, because we can put any digit
// from 0 to 9 on these xxx slots.
// Now, extrapolate this, we can do this for all digits from 0 to 9.
// Eg. 0xxx, 1xxx, 2xxx, x1xxx, xxx3, xx9x
// Because again, we can put any digits from 0 to 9 in any slot x.
// So, what does this mean?
// That means for each slot x, the sum of digits of this one x slot will
// be 45 (because the digit sum from 0 to 9 is 45).
// then, with 3 more extra slots, there are exactly 45 * 10^3 total sum
// for one x slot.
// But since we have 4 extra slots, we need to multiply by 4. Hence,
// the sum is actually 4 * 45 * 10^3.
// Also, note that we can do this scenario for:
// 527xxxx
// 526xxxx
// 525xxxx
// ...
// 520xxxx
// which has another 8 more ways to do so,
// Hence, the total contribution is actually:
// 4 * 45 * 8 * 10^3.
// In other words, the formula is:
// (remaining_digits - 1) * 45ll * current_digit * pow(10, remaining_digits - 2);
// in our case, remaning_digits = 5 (because its inclusive of 8).
// and thats the idea, so now as we go further down the index of the final
// number, we just decrement the remaining_digits and also don't forget
// to update the prefix sums of digits.
// You might also be wondering, but what if remaining_digits = 1?
// won't pow(10, remaining_digits-2) give a fraction?
// Yes, but also note that we did * (remaining_digits-1), which is 0.
// So, if the remaining_digits = 1, then the suffix contribution is 0.


void solve() {
	ll n, k, m;
    cin >> k;

    // Step 1: Find the number of digits of the number containing the k-th digit
    ll num_digits = 1;
    ll numbers_in_block = 9;
    while (k - num_digits * numbers_in_block > 0){
        k -= num_digits * numbers_in_block;
        numbers_in_block *= 10;
        num_digits++;
    }

    // Step 2: Find the actual number
    ll number = numbers_in_block / 9 + (k - 1) / num_digits;
    str number_str = to_string(number);

    // Step 3: Add the prefix of the number needed to reach k digits
    // Eg. number = 32642, k ends at the 3rd position (inclusive), so our sum
    // is 3+2+6=11 for this final number.
    int prefix_length = (k - 1) % num_digits + 1;
    ll digit_sum = 0;
    for (int i=0; i<prefix_length; i++){
        digit_sum += number_str[i] - '0';
    }

    // Step 4: Add sum of digits of all numbers less than `number`
    ll prefix_sum = 0; // sum of digits fixed so far
    ll remaining_digits = num_digits;
    for (int i=0; i<sz(number_str); i++){
        int current_digit = number_str[i] - '0';
        
        // Contribution from prefix digits and smaller digits at this position
        digit_sum += (prefix_sum * current_digit + (current_digit * (current_digit - 1)) / 2) * pow(10, remaining_digits - 1);

        // Contribution from all right digits (0..9 cycles)
        digit_sum += (remaining_digits - 1) * 45ll * current_digit * pow(10, remaining_digits - 2);

        remaining_digits--;
        prefix_sum += current_digit;
    }

    cout << digit_sum << '\n';

}

int main() {
    fast_io();
    // precompute_factorials(MAXN, MOD);
    // sieve();
    // precompute_prime_factors(); // modified sieve
    int t;
    cin >> t;
    while (t--) solve();
    // solve();
    return 0;
}
