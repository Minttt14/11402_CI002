#include <iostream>
using namespace std;

int main() {
    int n;
    while (cin >> n && n != -1) {

        for (int i=0; i<n; ++i) {
            int depth, ball;
            cin >> depth >> ball;
            
            int k = ball;
            int now = 1; 
            for (int j=0; j<depth - 1; ++j) {
                if (k % 2 != 0) {       
                    now = now * 2;
                    k = (k + 1) / 2;    
                }
                else {                
                    now = now * 2 + 1;
                    k = k / 2;       
                }
            }
            cout << now << "\n";
        }
    }
}