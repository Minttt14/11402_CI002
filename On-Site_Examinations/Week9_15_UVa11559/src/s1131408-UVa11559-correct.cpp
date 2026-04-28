#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, B, H, W;
    
    while (cin >> N >> B >> H >> W) {
        int minCost = B + 1;

        for (int i = 0; i < H; ++i) {
            int price;
            cin >> price;
            
            bool stay = false;
            for (int j = 0; j < W; ++j) {
                int bed;
                cin >> bed;
                if (bed >= N) {
                    stay = true;
                }
            }

            if (stay) {
                int total = N * price;
                if (total <= B) {
                    minCost = min(minCost, total);
                }
            }
        }

        if (minCost <= B) {
            cout << minCost << endl;
        } else {
            cout << "stay home" << endl;
        }
    }
    return 0;
}