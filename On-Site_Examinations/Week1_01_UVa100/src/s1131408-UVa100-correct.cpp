#include <bits/stdc++.h>
using namespace std;

int main() {
    int i, j;
    while (cin >> i >> j) {
        cout << i << " " << j << " ";
        
        if (i > j) swap(i, j);
        
        int cycle = 0;
        
        for (int a = i; a <= j; ++a) {
            long long n = a;
            int cnt = 1;
            
            while (n != 1) {
                if (n % 2 != 0) {
                    n = 3 * n + 1;
                } 
                else {
                    n /= 2;
                }
                cnt++;
            }
            
            if (cnt > cycle) {
                cycle = cnt;
            }
        }
        cout << cycle << "\n";
    }
}