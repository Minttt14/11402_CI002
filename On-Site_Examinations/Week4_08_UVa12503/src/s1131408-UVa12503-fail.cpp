#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;

    while(t--){
        int record[] = {0};
        int n;
        int cnt = 0;
        cin >> n;
        string instruction, dump;
        int num;

        for(int i=1; i<=n; ++i){
            cin >> instruction;
            if(instruction[0] == 'R'){
                record[i] = 1;
                cnt ++;
            }
            else if(instruction[0] == 'L'){
                record[i] = -1;
                cnt --;
            }
            else{
                cin >> dump >> num;
                cnt += record[num];
            }
        }
        cout << cnt << "\n";
    }
}