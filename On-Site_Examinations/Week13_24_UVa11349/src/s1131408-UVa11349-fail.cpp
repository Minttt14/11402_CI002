#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    int cnt = 1;
    while(t--){
        char dump;
        int n;
        cin >> dump >> dump >> n;
        int arr[n][n];
        bool check = true;

        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                cin >> arr[i][j];
                if(arr[i][j] < 0) check = false;  
            }
        }
        
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){

				if (arr[i][j] != arr[n-1-i][n-1-j]) check = false;
			}
        }
    
        if(check){
            cout << "Test #" << cnt << ": Symmetric.\n"; 
        }
        else{
            cout << "Test #" << cnt << ": Non-symmetric.\n" ;
        }  
        cnt ++;
    }
}