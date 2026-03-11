#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    int row = 0;
    char arr[101][101];
    int tmp = 0;

    for(int i = 0; i < 101; i++) {
        for(int j = 0; j < 101; j++) {
            arr[i][j] = ' ';
        }
    }

    while(getline(cin, s)){
        if(s.length() > tmp) tmp = s.length(); 
        for(int i=0; i<s.length(); ++i){
            arr[row][i] = s[i];
        }
        row++;
    }
    for(int i=0; i<tmp; ++i){
        for(int j=0; j<row; ++j){
            cout << arr[row -1 -j][i];
        }
        cout << "\n";
    }
}