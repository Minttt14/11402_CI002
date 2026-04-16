#include<bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    while (cin >> n && n != 0) {
        string b = "";
        int cnt = 0;
        
        while (n > 0) {
            if (n % 2 == 0) {
                b += '0';
            } else {
                b += '1';
                cnt ++;
            }
            n /= 2;
        }

        reverse(b.begin(), b.end());   
        cout << "The parity of " << b << " is " << cnt << " (mod 2).\n";
    }
    return 0;
}