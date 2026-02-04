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
// to use this just call precompute_factorials
ll nCr(int n, int r, ll mod) {
    if (n < r || r < 0) return 0;
    return (((fact[n] * inv_fact[r]) % mod) * inv_fact[n - r]) % mod;
}

void solve() {
    int n;
    cin >> n;
    vll a(n);

    for(int i=0;i<n;i++) cin >> a[i];

    // The first thing to notice for this problem is that if a[i] > a[i+1],
    // it is always beneficial for us to perform an operation on i
    // (from here we can kinda use an intution of monotonic increasing stack)
    // as such we know that the final result will always be a non-decreasing array
    // because performing an operation on a non-decreasing array only widens the gap
    // between the minimum and maximum value, which does not give the minimal difference.
    // note that the result is just difference from the last and first element of the 
    // final non-decreasing array.

    // The question now is, how do we make the non-decreasing array
    // and to also optimally assign values such that we can get the minimal difference
    // The answer is using a monotonic stack + greedy approach.
    // speifically using a monotonic increasing stack + greedy approach.
    

    // we know that, when we perform an operation on an index i, a[i]--, and a[i+1]++;
    // from this, we can think greedily, if we can somehow make the elements in the
    // array as close as possible to each other,
    // this would allow us to get the minimum difference.
    // Now the question is, how do we do that?
    // By using the power of monotonic increasing stack, and average.
    // we will contruct the non-decreasing array via our stack.
    // meaning the first element will be the lowest element in our stack
    // and the last element will be the highest element in our stack
    // then we just take the difference.
    
    // So, what is left now is how do we contruct the non-decreasing array optimally
    // via our stack?
    // The answer is to use average.
    // Notice that, if we can constantly make a the subarray of the original array
    // as close to the average of the current subarray as possible
    // we essentially greedily achieve a non-decreasing array every iteration.
    // To visualize this,
    // lets say you have an array nums = [4,2,3,1]
    // we start at [4] => subarray = [4]
    // the current sum, curSum = 4 and cnt = 1
    // since there is not elements to compare to with our monotonic increasing stack
    // we just add it to the stack, so stack = [(4,1)]
    // then at [2] => subarray = [4,2]
    // how do we make the subarray as evenly distributed as possible and non-decreasing?
    // well greedily we want to make it as close to the average as possible!
    // the average of this subarray is 3
    // which means we can make all elements to 3 => [3,3]
    // but what if the array is [2,4]?
    // this does not mean we can take average because applying an operation on a[0]==2
    // and a[1]==4 is not optimal!
    // this is where monotonic increasing stack comes in.
    // in order to maintain non-decreasing property, we introduce this data structure
    // such that when we encounter an element that is ONLY smaller than the previous
    // element will be considered.
    // hence if its [2,4] we simply move on while adding (4,1) to the stack
    // which implicity maintains non-decreasing property.
    // Now, back to [4,2]
    // we know that, since 2 < 4, our monotonic stack triggers
    // we need to perform some operation
    // Essentially, we will "merge" these 2 elements together will making them as close
    // to their average as possible.
    // in this case, the average is 3, which is a whole number, hence both elements can 
    // be 3,
    // so we pop the current element in the stack = [(4,1)] to []
    // and we append (3,2) to our stack, so now stack = [(3,2)] 
    // meaning we have 2 elements with value of 3 => subarray currently = [3,3]
    // moving on, we reach [3]
    // notice that, since [3] is the same as the value at the top of our stack
    // this triggers an operation on our stack because we can "merge" [3] with [3,3]
    // to make (3,3), and append it to our stack, of course, we need to delete the
    // top most element from our stack which is (3,2), and add (3,3) to our stack.
    // so now stack = [(3,3)]
    // last element, [1], stack = [(3,3)], subarray = [3,3,3], new element = [1]
    // well, 3 > 1, so this triggers an operation on our stack.
    // we need to "merge" [1] to [3,3,3] while maintaing the non-decreasing property.
    // so the average of all these values is (3+3+3+1)/4 = 2.5
    // Notice that the average is 2.5, which means some values will be 2, and some values
    // will be 3.
    // The question is, how do we know how many will be 2, and how many will be 3?
    // this is where the power of remainder comes in.
    // we know the total sum currently is 10, and we have 4 elements.
    // Notice that, sum % cnt == 2, what does this tell us?
    // this means that sum % cnt == 2 elements will have a value of sum/cnt (floor average)
    // and cnt - sum % cnt == 4 - 2 == 2 elements will have a value of 
    // (sum + cnt-1)/cnt (ceil average)
    // Great! Now we now the number of elements with 2 and 3
    // or more formally, the numbe of elements with floor average, and ceil average
    // which is what we are constanly finding every iteration if stack.top().first >= sum / cnt
    // now that we know x amount are floor average values, and y element are ceil average
    // values.
    // To maintain the non-decreasing property of our monotonic increasing stack
    // we MUST push the the x floor average values first, then the y ceil average values
    // after.
    // so now, our stack will be stack = [(2,2), (3,2)]
    // => final array = [2,2,3,3] (minimized non-decreasing array)
    // then we just take the top, and bottom of the stack's difference.


    // Time complexity: O(N)
    // Why? Because at each iteration, at most 2 elements are added to the stack.
    // And each element is removed at most once.
    // Here is the proof.
    // Note that, we intuitively "merging" the elements together into groups
    // So when find an element that can be "merged", we will pop the stack
    // until we can "merge" the current element with the required group
    // Note that this operation is always bounded by N.
    // Why? Think of it like this.
    // We have 3 oranges in a group current, and we meet an apple now.
    // prior to meeting the apple, we had to go through 3 oranges.
    // so essentially we had to pop our stack for each element here,
    // and "merge" these oranges together. 
    // => each orange is popped once in the stack to "merge" them together
    // so now that we meet an apple, the same thing happens again (if the "merged" oranges
    // >= apple, otherwise we continue to the next element after the apple)
    // if so then we will pop the "merged" oranges, and "merge" apple with the oranges.
    // Notice that for every move, we at most only pop each element only once.
    // hence pop operation is linear, N.
    // For push operation, it is the same, we only push the new group once (if the average
    // has no remainder) or twice (if the average has a remainder)
    // but regardless, the total elements up to this point is still N.
    // because we are essentially just "merging" the elements into a pair<ll, int>
    // into our stack.
    // hence the total operation is O(loop: N + pop : N + push: 2N) = O(4N) = O(N).
    
    stack<pair<ll, int>> s;
    for(int i=0; i<n; i++){
        ll sum = a[i], cnt = 1;
        while(s.size() && s.top().F >= sum / cnt){
            sum += s.top().F * s.top().S;
            cnt += s.top().S;
            s.pop();
        }
        s.push({sum / cnt, cnt - sum % cnt});
        if(sum % cnt != 0){
            s.push({sum / cnt + 1, sum % cnt});
        }
    }
    ll mx = s.top().F;
    while(s.size() > 1){
        s.pop();
    }

    cout << mx - s.top().F << '\n';
}


int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) solve();
    //solve();
    return 0;
}
