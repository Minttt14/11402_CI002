#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    int num = 1;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;

        int cnt = 0;
        for(int i=0; i<n; ++i){
            if(s[i] == '.'){
                cnt ++;
                i += 2;
            }
        }

        cout << "Case " << num << ": " << cnt << "\n";
        num ++;
    }
}