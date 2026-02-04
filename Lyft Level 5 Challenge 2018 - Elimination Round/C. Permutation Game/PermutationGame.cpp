#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int a[100005];
int position[100005];
int result[100005]; 

int main() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        position[a[i]] = i;
    }   

    for (int value = n; value > 0; value--) {
        int currentIndex = position[value];
        result[currentIndex] = 0; // Assume Bob wins from this cell initially

        for (int j = currentIndex + value; j <= n; j += value) {
            if (result[j] == 0 && a[j] > value) {
                result[currentIndex] = 1;
                break;
            }
        }

        for (int j = currentIndex - value; j > 0; j -= value) {
            if (result[j] == 0 && a[j] > value) {
                result[currentIndex] = 1;
                break;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << (result[i] == 1 ? 'A' : 'B');
    }
    cout << endl;

    return 0;
}
