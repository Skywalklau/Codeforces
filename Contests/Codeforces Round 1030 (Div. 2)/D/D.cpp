#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<ll> p(n);
        vector<int> d(n);
        for (int i = 0; i < n; ++i) cin >> p[i];
        for (int i = 0; i < n; ++i) cin >> d[i];

        unordered_map<ll, int> light; // position -> delay
        for (int i = 0; i < n; ++i) {
            light[p[i]] = d[i];
        }

        int q;
        cin >> q;
        vector<ll> a(q);
        for (int i = 0; i < q; ++i) cin >> a[i];

        for (int i = 0; i < q; ++i) {
            ll pos = a[i];
            int dir = 1; // 1 = right, -1 = left
            int time = 0;

            set<tuple<ll, int, int>> visited;
            bool escaped = false;

            while (true) {
                if (pos < 1 || pos > 1e15) {
                    cout << "YES\n";
                    escaped = true;
                    break;
                }
                auto state = make_tuple(pos, dir, time % k);
                if (visited.count(state)) {
                    cout << "NO\n";
                    break;
                }
                visited.insert(state);

                // Check for red light
                if (light.count(pos) && (time % k == light[pos])) {
                    dir *= -1;
                }

                pos += dir;
                time++;
            }
        }
    }

    return 0;
}
