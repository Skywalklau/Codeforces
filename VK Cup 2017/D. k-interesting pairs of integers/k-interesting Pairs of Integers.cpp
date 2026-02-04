#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input the number of integers and the Hamming distance (k)
    int n, k;
    cin >> n >> k;

    // Frequency map to count occurrences of each integer
    map<int, long long> frequency;

    // Read the input integers and populate the frequency map
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        frequency[value]++;
    }

    long long totalPairs = 0;

    // Iterate over all possible pairs of integers within the range [0, 10000]
    // we do not need to construct an array to store each number accordingly/
    // Why? Because XOR is commutative, A ^ B = B ^ A => index does not matter
    // What matters is that for each A, we can reach B once.
    // So if __builtin_popcount(A ^ B) == k and A is at a smaller index position than B
    // Then B does not have to go through A again, saving time.
    // And if we do it like this, we do not even need to loop through the array they gave us
    // in the first place, just loop through the number since its small (10^4^2 == 10^8 ~ 1s)
    // So we can do it in time.
    // But, if the number can go beyond 10^4, like 10^5, then we have to loop the array intuitively
    // first we would have to remove duplicate numbers (store in a freq map/array) in the array 
    // then sort the array and loop the array.
    
    // This is a special case of a meet in the middle problem
    // Rather than splitting the array into 2 parts, we are splitting the number line into
    // two parts for every iteration.
    for (int num1 = 0; num1 <= 10000; num1++) {
        for (int num2 = num1; num2 <= 10000; num2++) {
            // Calculate the Hamming distance using __builtin_popcount
            int hammingDistance = __builtin_popcount(num1 ^ num2);

            // Skip if the Hamming distance is not equal to k
            if (hammingDistance != k) {
                continue;
            }

            // For k = 0, count pairs within the same number
            // [1,1] => (1,1) only
            // totalPairs without /2 == 2 * 1 = 2, which is wrong, since we want combination,
            // not permutation, so must /2
            if (k == 0) {
                totalPairs += frequency[num1] * (frequency[num1] - 1) / 2;
            } 
            // For k > 0, count pairs between different numbers
            else {
                totalPairs += frequency[num1] * frequency[num2];
            }
        }
    }

    // Output the total number of k-interesting pairs
    cout << totalPairs << endl;

    return 0;
}
