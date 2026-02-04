#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

double firstDigitIsOneProbability(long long L, long long R) {
    long long count = 0;
    for (unsigned long long start = 1; start <= R; start *= 10) {
        long long end = start * 2 - 1;
        if (start > R) break;
        count += max(0LL, min(R, end) - max(L, (long long) start) + 1);
    }
    return static_cast<double>(count) / (R - L + 1);
}

void solve() {
    int N;
    cin >> N;

    vector<pair<long long, long long>> intervals(N);
    for (int i = 0; i < N; ++i) {
        long long L, R;
        cin >> L >> R;
        intervals[i] = {L, R};
    }

    int K;
    cin >> K; 

    int required_count = (K * N + 99) / 100;

    vector<double> probabilities(N);
    for (int i = 0; i < N; ++i) {
        probabilities[i] = firstDigitIsOneProbability(intervals[i].first, intervals[i].second);
    }

    vector<double> dp(N + 1, 0.0);
    dp[0] = 1.0;

    for (double p : probabilities){
        vector<double> new_dp(N + 1, 0.0);
        for (int x = 0; x < N; ++x){
            new_dp[x + 1] += dp[x] * p;
            new_dp[x] += dp[x] * (1 - p);
        }
        dp = new_dp;
    }

    double result = 0.0;
    for (int i = required_count; i <= N; ++i){
        result += dp[i];
    }

    cout << fixed << setprecision(9) << result << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
