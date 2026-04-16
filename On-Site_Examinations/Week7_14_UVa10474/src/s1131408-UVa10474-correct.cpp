#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, q;
    int cnt = 1;
    while(cin >> n >> q && (n !=0 || q !=0)){
        vector<int> marble(n);

        for(int i=0; i<n; ++i){
            cin >> marble[i];
        }

        sort(marble.begin(), marble.end());

        cout << "CASE# " << cnt << ":" << "\n";
        cnt++;

        while(q--){
            int target;
            cin >> target;

            auto it = lower_bound(marble.begin(), marble.end(), target);

            if(it != marble.end() && *it == target){
                int idx = distance(marble.begin(), it) + 1;
                cout << target << " found at " << idx << "\n";
            }
            else{
                cout << target << " not found\n";
            }
        }
    }
}