#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, cnt = 1;
    while (cin >> n) {
        vector<int> a(n);
        bool B2 = true;
        int exist[20001] = {0};

        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            if (a[i] < 1 || (i > 0 && a[i] <= a[i - 1])) {
                B2 = false;
            }
        }

        if (B2) {
            for (int i = 0; i < n; i++) {
                for (int j = i; j < n; j++) {
                    int sum = a[i] + a[j];
                    if (exist[sum] == 1) {
                        B2 = false;
                        break;
                    }
                    else exist[sum] = 1;
                }
                if (!B2) break;
            }
        }

        if (B2) cout << "Case #" << cnt << ": It is a B2-Sequence.\n";
        else cout << "Case #" << cnt << ": It is not a B2-Sequence.\n";
        cout << "\n";
        cnt ++;
    }
    return 0;
}