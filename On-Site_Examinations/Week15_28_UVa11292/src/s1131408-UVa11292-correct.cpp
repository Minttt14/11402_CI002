#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;

    while (cin >> n >> m && (n != 0 || m != 0)) {
        vector<int> heads(n);
        vector<int> knights(m);

        for (int i = 0; i < n; ++i) {
            cin >> heads[i];
        }
        for (int i = 0; i < m; ++i) {
            cin >> knights[i];
        }

        if (m < n) {
            cout << "Loowater is doomed!\n";
            continue;
        }

        sort(heads.begin(), heads.end());
        sort(knights.begin(), knights.end());

        int cost = 0;    
        int head_idx = 0;   
        int knight_idx = 0; 

        while (head_idx < n && knight_idx < m) {

            if (knights[knight_idx] >= heads[head_idx]) {
                cost += knights[knight_idx]; 
                head_idx++;                  
            }
            knight_idx++; 
        }
        if (head_idx == n) cout << cost << "\n";
        else cout << "Loowater is doomed!\n";
    }
}