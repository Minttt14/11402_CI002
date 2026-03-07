#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n1, n2;
    
    while (cin >> n1 >> n2 && (n1 != 0 || n2 != 0)){
        int carry = 0;  
        int cnt = 0;
        
        while (n1 > 0 || n2 > 0){
            int sum = (n1 % 10) + (n2 % 10) + carry;
            
            if(sum >= 10){
                carry = 1;
                cnt++; 
            } 
            else
            {
                carry = 0;
            }
            n1 /= 10;
            n2 /= 10;
        }
        
        if(cnt == 0){
            cout << "No carry operation." << endl;
        } 
        else if(cnt == 1){
            cout << "1 carry operation." << endl;
        }
        else{
            cout << cnt << " carry operations." << endl;
        }
    }
}