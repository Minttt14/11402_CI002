#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while(cin >> n && n!=0){
        while(true){
            vector<int> target(n);
            cin >> target[0];
            if(target[0] == 0){
                cout << "\n";
                break;
            }

            for(int i=1; i<n; ++i){
                cin >> target[i];
            }
            stack<int> train;
            int current = 0;

            for(int i=1; i<=n; ++i){
                train.push(i);

                while(!train.empty() && train.top() == target[current]){
                    train.pop();
                    current ++;
                }
            }
            if(train.empty()) cout << "Yes\n";
            else cout << "No\n";
        }
    }
    return 0;
}