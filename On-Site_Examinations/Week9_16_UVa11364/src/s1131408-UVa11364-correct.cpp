#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        
        int minPos = 100;
        int maxPos = -1;
        
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            if (x < minPos) minPos = x;
            if (x > maxPos) maxPos = x;
        }
        cout << (maxPos - minPos) * 2 << "\n";
    }
    return 0;
}