#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    int cnt = 0;
    while(t--){
        cnt ++;
        int a, b;
        cin >> a >> b;
        int n = 0;
        if(a%2 == 0 && b%2 != 0){
            n = ((b-a)/2) +1;
            a++;
        }
        else if(a%2 == 0 && b%2 == 0){
            n = ((b-a)/2);
            a++;
        }
        else{
            n = ((b-a)/2) +1;
        }
        cout << "Case " << cnt << ": " << (n*(2*a +(n-1)*2))/2 << "\n";
    }
}